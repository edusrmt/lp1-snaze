#ifndef SNAZE_GAME_H
#define SNAZE_GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <chrono>
#include <thread>

#include "../include/level.hpp"
#include "../include/snake.hpp"
#include "../include/player.hpp"

class SnazeGame {
    private:
    std::deque<Level> levels;       //!< Deque that stores all levels
    bool paused = false;            //!< Should wait for user input?
    int level_amt;                  //!< Amount of levels loaded
    int lives = 5;                  //!< Amount of lives the snake has
    int score = 0;                  //!< Current score of the game
    int food = 0;                   //!< Amount of food eaten in the current level
    std::string msg = "";           //!< Message to be displayed on the top of the screen
    Player* ai;                     //!< Snake's AI

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

    /// Wait some time or user input
    void wait ();

    /// Render final screen
    void end_game();

    /// Spawns a snake at spawn point, reference it's AI
    void spawn_snake ();

    /// Spawns fruit at random position
    void spawn_fruit ();
};

#endif