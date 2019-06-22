#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <vector>

#include "./util.hpp"
#include "./snake.hpp"

class Level {
    private:
    int r;                                  //!< Height of the level
    int c;                                  //!< Width of the level
    std::vector<std::vector<char>> grid;    //!< Level data
    Coordinate spawn;                       //!< Spawn point of the snake
    Coordinate fruit;                       //!< Location of the fruit

    public:
    /// Default constructor
    Level (int rows, int cols) : r{rows}, c{cols} {
        // Allocates the matrix that stores all level data
        grid.resize(r);

        for (int i = 0; i < rows; i++)
            grid[i].resize(c);
    }

    /// Default destructor
    ~Level () { }

    /// Output operator
    friend std::ostream& operator<< (std::ostream &out, const Level& lvl);

    /// Sets a char to specific position of the level
    void set_char(char value, int row, int col) {
        grid[row][col] = value;
    }
};

/// Output operator
inline std::ostream& operator<< (std::ostream &out, const Level& lvl) {
    for (int i = 0; i < lvl.r; i++) {
        for (int j = 0; j < lvl.c; j++) {
            out << lvl.grid[i][j];
        }
        
        if (i != lvl.r - 1)
            out << std::endl;
    }

    return out;
}

#endif