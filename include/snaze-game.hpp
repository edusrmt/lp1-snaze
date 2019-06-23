#ifndef SNAZE_GAME_H
#define SNAZE_GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "../include/level.hpp"
#include "../include/snake.hpp"
#include "../include/player.hpp"

class SnazeGame {
    private:
    std::vector<Level> levels;      //!< Vector that stores all levels
    int lives = 5;                  //!< Amount of lives the snake has
    int score = 0;                  //!< Current score of the game
    int food = 0;                   //!< Amount of food eaten in the current level
    Player* ai;

    public:
    /// Default constructor
    SnazeGame () { }

    /// Destructor
    ~SnazeGame () {
        delete ai;
    }

    /// Initializes a game instance
    bool initialize_game (int argc, char* argv[]);

    /// Returns wether game is over or not
    bool game_over ();

    /// Renders current state of the game
    void render ();

    /// Runs all game logic
    void update ();

    /// Wait some time
    void wait ();

    /// Spawns a snake at spawn point, reference it's AI
    void spawn_snake ();

    /// Spawns fruit at random position
    void spawn_fruit ();

    /// Checks if current round has been completed
    bool round_complete();

    /// Checks if current level has been completed
    bool level_complete();
};

#endif