# Snaze Simulation
## Summary
[1. The Game](#1-The-Game)

[2. Rules](#2-Rules)

[3. Compiling](#3-Compiling)

[4. Game Interface](#4-Game-Interface)

[5. Input File](#5-Input-File)

[6. Authorship](#6-Authorship)

## 1. The Game
Snake is the common name for a video game concept where the player maneuvers a line which grows in length,with the line itself being a primary obstacle. The concept originated in the 1976 arcade game Blockade, and the ease of implementing Snake has led to hundreds of versions for many platforms. **Snaze** is a simulation of this classic game, but this time the scenario is a maze.

*Source: [Wikipedia](https://en.wikipedia.org/wiki/Snake_(video_game_genre))*

## 2. Rules

The rules in this implementation are:

1. The snake has 5 lives;
2. The snake moves by extending its head 1 step in the direction it’s moving and pulling its tail in;
3. If the snake eats a piece of food, its length grows by one and a new food pellet is randomly placed in a location the snake can get to;
4. There might be one or more levels, depending on the input file;
5. Everytime the snake crashes into itself or into a wall it looses one life; The snake loses the game simulation when all 5 lives are spent;
6. The snake wins the game simulation if it eats all the food pellets in all levels.

## 3. Compiling

This project may be compiled with [CMake](https://cmake.org).
CMake is an open-source, cross-platform family of tools designed to build, test and package software.
Basically, cmake reads a script (`CMakeLists.txt`) with meta-information on the project and **creates a Makefile automatically**, tailored to your system configuration.
After that, you may run the `make` command, as usual.

To compile the game you should follow these steps into the root folder:

1. `cmake -G "Unix Makefiles" ..`: asks cmake to create the Makefile based on the script found in `CMakeLists.txt`.
2. `make`: compiles the codes of the game and generate an executable into `./bin` folder.

## 4. Game Interface

In order to run the game executable, you have to pass an input file by command line argument. The command to run the executable is as following:

`./bin/snaze <input_file>`

## 5. Input File

Input files may contain as many levels as wanted, for each one of them you must follow this structure:

    <Number of rows> <Number of columns>
    <Data line 1 of length equals to [Number of columns]>
    <Data line 2 of length equals to [Number of columns]>
    <Data line 3 of length equals to [Number of columns]>
    ...
    <Data line [Number of rows] of length equals to [Number of columns]>

The characters meaning are as follows:

1. `#`: Maze wall
2. `*`: Snake's spawn location
3. `.`: Invisible wall

Levels with no spawn point are discarded. The maximum amount of rows or columns is 100.

## 6. Authorship

The authors of this project are **Carlos Eduardo Alves Sarmento** _< cealvesarmento@gmail.com >_ and **Victor Raphaell Vieira Rodrigues** _< victorvieira89@gmail.com >_.