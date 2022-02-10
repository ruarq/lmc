# lmc
lmc - The official compiler for the Lumin programming language.

## What is Lumin
Fast. Simple. Beautiful. (pun intended)

## The compiler
### Build
#### Dependencies
- clang++:13.0.1
- clang-format:13.0.1
- make:4.3

#### Linux
Linux is the only officially supported platform, though in theory, the code *should* work on Windows or even MacOS.
To build, simply run:
```bash
./build.sh
```

This will generate an executable in `bin/debug/lmc`.
To build in release mode, simply pass `release` to the build script:
```bash
./build.sh release
```

### Contribute
Generally, I don't have any problem with voluntary contributions. Before creating a pull request, run the build script in release mode and check that your changes work.
Please also stick to the [styleguide](styleguide.md).
