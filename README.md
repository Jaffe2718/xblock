# Block Transform

![Stars](https://img.shields.io/github/stars/Jaffe2718/xblock?style=flat-square)
![Forks](https://img.shields.io/github/forks/Jaffe2718/xblock?style=flat-square)
![Issues](https://img.shields.io/github/issues/Jaffe2718/xblock?style=flat-square)
![License](https://img.shields.io/github/license/Jaffe2718/xblock?style=flat-square)

## Play Online

[Jaffe2718|Block Transform](https://jaffe2718.github.io/xblock/)

## Project Description (for Developers)

### Project Structure

```
.
|   CMakeLists.txt            # CMake configuration file
|   LICENSE                   # GPL-3.0 License
|   main.cpp                  # Main entry of the project & core logic module
|   README.md                 # Project README file
|
+---res                       # Resource files
|       arial.ttf             # Font file
|       arialbd.ttf           # Font file
|       res.rc                # Resource configuration file
|       xblock.ico            # Icon file to compile
|       xblock.png            # Icon file
|       xnftj.mp3             # Background music file
|
\---units
        event_handling.cpp
        event_handling.h      # Event handling module
        resources.cpp
        resources.h           # Resource loading module
        topology.cpp
        topology.h            # Data structure module
        ui.cpp
        ui.h                  # UI rendering module
```

### Project Dependencies

| Dependency | Version | Description                                                                                                                                                                                                                   |
|:-----------|:--------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| git        | -       | Version control system                                                                                                                                                                                                        |
| MinGW      | 13.1.0  | Mingw-w64 GCC for Windows, [WinLibs MSVCRT 13.1.0 (64-bit)](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.7z) |
| CMake      | \>=3.28 | Cross-platform build system                                                                                                                                                                                                    |
| SFML       | 2.6.1   | Simple and Fast Multimedia Library, 64-bit version, [Download](https://www.sfml-dev.org/download/sfml/2.6.1/)                                                                                                                 |

### How to setup
1. Install `git` & `CMake` & `MinGW` & `SFML`, add them to the system environment variables.
2. Clone the project to your local directory.
3. Edit the `CMakeLists.txt` file to specify the path of the SFML library.
4. Build & run the project.

```shell
git clone -b cxx_sfml https://github.com/Jaffe2718/xblock.git
cd xblock
cmake -S . -B build
cmake --build build
```

### How to compile

```shell
cd xblock
cmake -S . -B build
cmake --build build
mingw32-make -C build -j 8
```

### Reference

- [FeasibilityAnalysis](doc/Feasibility_Analysis.md)
- [Flowchart](doc/Flowchart.md)
- [LICENSE](LICENSE)

## How to play

There are 3 modes in this game: `3x3`, `4x4` and `5x5`.
You can choose the mode by clicking the corresponding button.
For each mode, all the numbers are randomly shuffled.
And in each round, if you click a block, the block will exchange it's number with the specified block.
The rules of exchange are fixed and cannot be changed in a round.
The goal of the game is to make all the numbers in order:

```
3x3:

1   2   3
4   5   6
7   8   9


4x4:

1   2   3   4
5   6   7   8
9   10  11  12
13  14  15  16


5x5:

1   2   3   4   5
6   7   8   9   10
11  12  13  14  15
16  17  18  19  20
21  22  23  24  25
```