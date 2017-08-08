project('prctl_wx', 'c',
    version: '1.0',
    meson_version: '>= 0.40.0'
)

add_global_arguments(
    '-Wall', '-Wextra',
    language: 'c',
)

deps = [
]

srcs = [
    'lib.c',
]

prctl_wx = shared_library(
    'prctl_wx',
    srcs,
    install: true,
    dependencies: deps,
)

prctl_x = shared_library(
    'prctl_x',
    srcs,
    install: true,
    dependencies: deps,
    c_args: [
        '-DDISABLE_EXEC_PAGES=1',
    ],
)

prctl_wxd = shared_library(
    'prctl_wxd',
    srcs,
    install: true,
    dependencies: deps,
    c_args: [
        '-DALLOW_FETCH_FAULTS=1',
    ],
)

