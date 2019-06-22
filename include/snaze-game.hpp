#ifndef SNAZE_GAME_H
#define SNAZE_GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../include/level.hpp"
#include "../include/snake.hpp"

class SnazeGame {
    private:
    std::vector<Level> levels;      //!< Vector that stores all levels
    int lives = 5;                  //!< Amount of lives the snake has
    int score = 0;                  //!< Current score of the game
    int food = 0;                   //!< Amount of food eaten in the current level

    public:
    /// Default constructor
    SnazeGame () { }

    /// Initializes a game instance
    bool initialize_game (int argc, char* argv[]);

    /// Returns wether game is over or not
    bool game_over ();

    /// Renders current state of the game
    void render ();

    /// Runs all game logic
    void update ();
};

#endif