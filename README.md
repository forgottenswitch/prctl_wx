A userspace support library for a (custom) PaX patch (tells the kernel to
activate the restrictions/protections).

This is only a temporary workaround; the proper solution is to patch loader and
the compiler that performs the linking (to handle dynamically and statically
linked binaries, respectively).  Requires dynamic loader that understands
`LD_PRELOAD` (as glibc does).

# Installation
```
meson build
ninja -C build

# then either:
DESTDIR=/tmp/staged-install ninja -C build install
# (copy+chown /tmp/staged-install to /)

# or:
sudo ninja -C build install
```

In `~/.profile`, or `~/.bashrc`, or `/etc/profile`, or ...:
```
export LD_PRELOAD='/$LIB/libprctl_wx.so'
```

And then you need to run applications that could need WX pages (Qemu 2.9, Wine,
etc.) with an empty `LD_PRELOAD`.

## Debuggers
The `libprctl_wx` makes instruction fetch faults fatal, which breaks debuggers'
ability to call debugee's functions. To allow the faults while still
disallowing WX pages, use `libprctl_wxd`.
Example:
```
gdb_wxd() {
  # the nested shell is for LD_PRELOAD change not to persist
  (
    export LD_PRELOAD='/$LIB/libprctl_wxd.so'
    exec gdb "$@"
  )
}

gdb_wxd /usr/bin/id
```

## Stricter mode
For a mode that disallows `dlopen`, use `/$LIB/libprctl_x.so` instead.

However, even libc routines load on-demand (in glibc at least). The solution is
then to preload the libraries:
```
strace id 2>&1 | grep '^openat' | sed -e 's/^[^"]*"//; s/".*//;' | sort | uniq | grep --color=no '[.]so'
```
should give
```
/etc/ld.so.cache
/lib64/libc.so.6
/lib64/libnsl.so.1
/lib64/libnss_compat.so.2
/lib64/libnss_files.so.2
/lib64/libnss_nis.so.2
```

Which then could be used as
```
export LD_PRELOAD='/$LIB/libprctl_x.so'
LD_PRELOAD="$LD_PRELOAD"':/$LIB/libnss_compat.so.2'
```
(with the rest of libraries also possibly in `LD_PRELOAD`).
