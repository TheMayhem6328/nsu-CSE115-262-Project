# CSE115 PROJECT

## Requirements

- `clang`
- GNU `make`

## Build Instructions

### Windows (MSYS2 Only)

> As of present, MSVC’s Clang toolchain is not supported.
> Please use MSYS2 or MINGW instead.

- Install [MSYS2](https://msys2.org)
- Launch MSYS2 CLANG64
- Run `pacman -Syu`
- If prompted, restart and reopen MSYS2 CLANG64
- Run `pacman -S mingw-w64-clang-x86_64-clang make`
- `cd` to project directory
- Run `make`
- Run `./build/program.exe`

### macOS

> Note: This is untested, as I do not have access to a macOS device,
> and therefore may be inaccurate. Please refer to Google in case of
> any discrepancies.

- Install *macOS Xcode Command Line Tools* if not already installed
  - Run `xcode-select --install`
  - This provides `clang` and `make`
- `cd` to project directory
- Run `make`
- Run `./build/program`

### Linux

- Install prerequisites as per the guidelines of your particular distribution
- `cd` to project directory
- Run `make`
- Run `./build/program`
