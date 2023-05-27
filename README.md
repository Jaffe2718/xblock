# Block Transform Game (Python Version)

## Project Description

### Project Structure

```
.
|   .gitignore          # git ignore file
|   compile.cmd         # compile script
|   LICENSE             # license file
|   README.md           # readme file
|   setup.cmd           # setup script
|
\---block_trans         # project root
    |   game_ui.py      # game ui module
    |   graph.py        # unidirectional graph module
    |   main.py         # main program
    |
    \---assets          # static assets directory
            xnftj.mp3   # background music
```

### Project Dependencies
| Dependency | Version | Description            |
|:-----------|:--------|:-----------------------|
| git        | -       | Version control system |
| Anaconda   | -       | Python distribution    |

### How to setup
run `setup.cmd` to setup the project, or run the following commands in the project root directory:
```bash
conda create -n xblock python=3.11
conda activate xblock
pip install pyinstaller
pip install pygame
```

### How to compile
run `compile.cmd` to compile the project, or run the following commands in the project root directory:
```bash
pyinstaller --upx-dir "path/to/upx" --add-data "path/to/assets;assets" -Fw "path/to/main.py" -i "path/to/your.ico"
```

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