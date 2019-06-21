#ifndef SNAZE_GAME_H
#define SNAZE_GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../include/level.hpp"

class SnazeGame {
    private:
    std::vector<Level> levels;      //!< Vector that stores all levels

    public:
    /// Default constructor
    SnazeGame () { }

    /// Initializes a game instance
    bool initialize_game (int argc, char* argv[]);
};

#endif