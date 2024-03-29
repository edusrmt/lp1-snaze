#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <vector>
#include <cstdlib>

#include "./util.hpp"
#include "./snake.hpp"

/// Char matrixes are called frames
typedef std::vector<std::vector<char>> Frame;

class Level {
    private:
    int r;                                  //!< Height of the level
    int c;                                  //!< Width of the level
    Frame grid;                             //!< Level data
    Coordinate spawn;                       //!< Spawn point of the snake
    Coordinate fruit;                       //!< Location of the fruit   

    friend class SnazeGame;                 //!< SnazeGame hass access to this class

    public:
    Snake snake;                            //!< Snake of the level

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
        if (value == '*')
            spawn = Coordinate(row, col);

        grid[row][col] = value;
    }

};

/// Output operator
inline std::ostream& operator<< (std::ostream &out, const Level& lvl) {
    /// Display starts with level grid
    Frame display = lvl.grid;

    /// Draws fruit on the display
    if (lvl.fruit.row != -1 && lvl.fruit.col != -1)
        display[lvl.fruit.row][lvl.fruit.col] = 'o';

    /// Draws spawn point only before starting the level
    if (lvl.snake.alive || lvl.fruit.row != -1 || lvl.fruit.col != -1)
        display[lvl.spawn.row][lvl.spawn.col] = ' ';        


    /// Draws snake on the display, starting by the head
    if (lvl.snake.alive) {
        Coordinate head = lvl.snake.body[0];
        char head_char = ' ';

        switch (lvl.snake.facing) {
            case Direction::Up:
            head_char = 'v';
            break;

            case Direction::Right:
            head_char = '<';
            break;

            case Direction::Down:
            head_char = '^';
            break;

            case Direction::Left:
            head_char = '>';
            break;
        }

        display[head.row][head.col] = head_char;

        /// Draws body
        for (size_t i = 1; i < lvl.snake.body.size(); i++) {
            display[lvl.snake.body[i].row][lvl.snake.body[i].col] = '0';
        }
    } else {
        if (lvl.fruit.row != -1 || lvl.fruit.col != -1)
            display[lvl.snake.body[0].row][lvl.snake.body[0].col] = 'X';

        for (size_t i = 1; i < lvl.snake.body.size(); i++) {
            display[lvl.snake.body[i].row][lvl.snake.body[i].col] = 'x';
        }
    }
    

    /// Sends final display to output, applying unicode style
    for (int i = 0; i < lvl.r; i++) {
        for (int j = 0; j < lvl.c; j++) {
            switch (display[i][j])
            {
                case '.':
                out << ' ';
                break;

                case '#':
                out << "\u2588";
                break;

                case '0':
                out << "\uFFEE";
                break;

                case 'X':
                out << "\uFFED";
                break;

                case 'x':
                out << "\u2B1D";
                break;
            
                default:
                out << display[i][j];  
                break;
            }
        }
        
        if (i != lvl.r - 1)
            out << std::endl;
    }

    return out;
}

#endif