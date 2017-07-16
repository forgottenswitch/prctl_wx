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
