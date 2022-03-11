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
- libfmt:8.1.1-1
- premake-5.0.0-beta1

#### Linux and MacOS
Linux and MacOS is the only officially supported platforms, though in theory, the code *should* work on Windows.
After you installed all dependencies, simply run `./build.sh` to build the project.

This will generate an executable in `bin/debug/lmc`.
To build in release mode, simply pass `release` to the build script:
```bash
./build.sh release
```

### Contribute
Generally, I don't have any problem with voluntary contributions. Please read [this](contribute.md) document about contributing.
Please also stick to the [styleguide](styleguide.md).
