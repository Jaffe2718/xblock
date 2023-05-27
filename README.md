# Block Transform Game (GitHub Pages)

## Project Description
This is a game which is rewritten from the python version.

### Project Structure

```
.
|   .gitignore      // git ignore file
|   index.html      // html file
|   LICENSE         // license file: GPL-3.0
|   README.md       // readme file
|
\---js              // js files
        main.js     // main js file
```

## URL


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