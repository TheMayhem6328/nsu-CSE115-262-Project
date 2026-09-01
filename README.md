# CSE115 PROJECT

## Rant
- I so wish OOP and namespaces were a thing here, but alas

## Requirements

- `clang`
- GNU `make`
- C99 support

## Build Instructions

### Windows (MSYS2 Only)

> As of present, MSVC’s Clang toolchain is not supported.
> Please use MSYS2 instead.

- Install [MSYS2](https://msys2.org) if not already installed
- Launch MSYS2 CLANG64
- Install prerequisites
  - Run `pacman -Syu` to update packages and database
    - If prompted, restart and reopen MSYS2 CLANG64
  - Run `pacman -S mingw-w64-clang-x86_64-clang make`
  - Build and run the program
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
- Build and run the program
  - `cd` to project directory
  - Run `make`
  - Run `./build/program`

### Linux

- Install prerequisites as per the guidelines of your particular distribution
- Build and run the program
  - `cd` to project directory
  - Run `make`
  - Run `./build/program`

## Data File Format

I am deliberately not directly writing struct to file since there is
no guarantee of format portability across various devices if I do so,
therefore am making my own defined file format to handle this.

All integers are to be stored as big-endian for consistency

File extension: CS115FB

|   Offset | Size (B) |                     Type | Purpose                             |
| -------: | :------: | -----------------------: | :---------------------------------- |
|   `0x00` |    8     |                `char[8]` | File Identifier, `'CS115_FB'`       |
|   `0x08` |    1     |                `uint8_t` | Revision of data file (presently 0) |
|   `0x09` |    8     |               `uint64_t` | Team array start offset             |
|   `0x11` |    8     |               `uint64_t` | Manager array start offset          |
|   `0x19` |    8     |               `uint64_t` | Player array start offset           |
|   `0x21` | Variable |   Serialized admin array | Admin array start                   |
| Variable | Variable |    Serialized team array | Team array start                    |
| Variable | Variable | Serialized manager array | Manager array start                 |
| Variable | Variable |  Serialized player array | Player array start                  |
