# Feasibility Analysis

|              proposer               |              reviewer               |              approver               |
|:-----------------------------------:|:-----------------------------------:|:-----------------------------------:|
| [李昌哲](https://github.com/Jaffe2718) | [李昌哲](https://github.com/Jaffe2718) | [李昌哲](https://github.com/Jaffe2718) |

## Change History

| id  |    date    | version | description | reason | proposer | reviewer | approver |
|:---:|:----------:|:-------:|:-----------:|:------:|:--------:|:--------:|:--------:|
| 001 | 2024-04-01 |   1.0   | First Draft |        |   李昌哲    |   李昌哲    |   李昌哲    |

> **Note:** The reason for the change is mainly divided into:
> 1. Establish the first draft
> 2. Content revision
> 3. Official release

## Catalog

1. [Document Overview](#document-overview)
    1. [Purpose](#purpose)
    2. [Scope](#scope)
    3. [Readership](#readership)
    4. [Reference Documents](#reference-documents)
2. [Project Introduction](#project-introduction)
    1. [Overview](#overview)
    2. [Background](#background)
    3. [Objectives](#objectives)
    4. [Range of Application](#range-of-application)
    5. [Assumptions and Dependencies](#assumptions-and-dependencies)
3. [Status Quo and User Requirements](#status-quo-and-user-requirements)
    1. [User Analysis](#user-analysis)
        1. [User Characteristics](#user-characteristics)
        2. [User Needs](#user-needs)
    2. [User Environments](#user-environments)

## Document Overview

### Purpose

Develop a mini-game with a structured programming approach named `Block Transform`.
The game is a simple 2D game with UI and game logic.

### Scope

1. The game is a 2D game.
2. The game has a simple UI.
3. Several game modes with different levels of difficulty.
4. Ability to record the time it takes for a player to achieve victory.

### Readership

1. Developers
2. Players

### Reference Documents

| Document Name |                   Document Location                    |
|:-------------:|:------------------------------------------------------:|
|     SFML      | [https://www.sfml-dev.org/](https://www.sfml-dev.org/) |

## Project Introduction

### Overview

This project is a simple 2D game with a structured programming approach.
The game is named `Block Transform` and is a simple game with UI and game logic.
We use the SFML library to develop the game.

This game requires players to arrange the disordered number blocks in ascending order from left to right and from top to
bottom.
In each game, the rules for exchanging numbers for each block are determined and players need to explore them
themselves.

### Background

Curriculum design project for a software engineering course.

### Objectives

1. A user-friendly UI.
2. `3x3`, `4x4`, and `5x5` game modes.
3. Ability to record the time it takes for a player to achieve victory.
4. A background music.

### Range of Application

This project is a game with UI for windows operating system.

### Assumptions and Dependencies

1. For the development of the game, we use the SFML library.
2. For playing the game, the player should just extract the game and run the `.exe` file.

## Status Quo and User Requirements

### User Analysis

The primary users of the `Block Transform` game are individuals who enjoy puzzle games and are looking for a new
challenge. These users are likely to have some experience with similar games and are comfortable with using a computer
to play games. They may range in age from children to adults, as the game's simple interface and rules make it
accessible to a wide audience.

The secondary users of the game are developers who are interested in the game's code and may want to modify it or learn
from it. These users are expected to have a good understanding of C++ and the SFML library.

#### User Characteristics

1. **Primary Users (Players):**
    - Enjoy puzzle games and are looking for a new challenge.
    - Comfortable with using a computer to play games.
    - Range in age from children to adults.
    - May not have any programming knowledge.

2. **Secondary Users (Developers):**
    - Interested in the game's code.
    - May want to modify the game or learn from it.
    - Have a good understanding of C++ and the SFML library.

#### User Needs

1. **Primary Users (Players):**
    - Need a simple and user-friendly interface.
    - Need clear instructions on how to play the game.
    - Need different levels of difficulty to keep the game challenging and interesting.

2. **Secondary Users (Developers):**
    - Need clear and well-documented code.
    - Need a good understanding of the game's structure and logic.

### User Environments

The game is designed to be played on a Windows operating system. Players will need a computer with the following
minimum specifications:
- Windows 7 or later.
- 2 GB of RAM.
- 1 GB of free disk space.
