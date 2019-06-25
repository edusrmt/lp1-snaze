#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <stack>

#include <algorithm>

#include "./level.hpp"
#include "./snake.hpp"
#include "./util.hpp"

class Player {
    private:
    std::vector<std::vector<char>> level;   //!< Sctructure of a level
    Snake snake;                            //!< The snake this AI is simulating
    Coordinate target;                      //!< Target fruit

    std::stack<Direction> path;             //!< Path to the fruit

    /// Clears the path stack
    void clear_path () {
        while(!path.empty()) {
            path.pop();
        }
    }

    /// Returns a vector with all possible one step moves as Snapshots
    std::stack<Snake> check_neighbors (Snake snk, std::vector<Coordinate> v);

    /// Checks if going to new_pos will lead the snaker closer to the target
    bool leads_closer (Coordinate old_pos, Coordinate new_pos) {
        int old_dis = target.row - old_pos.row + target.col - old_pos.col;
        old_dis *= old_dis;
        int new_dis = target.row - new_pos.row + target.col - new_pos.col;
        new_dis *= new_dis;

        return new_dis < old_dis;
    }

    /// Looks for the best path to the fruit
    bool find_solution ();

    public:
    /// Default constructor
    Player () { }

    /// Initialization constructor
    Player (std::vector<std::vector<char>> lvl, Snake &snk, Coordinate &tgt) : level{lvl}, snake{snk}, target{tgt} { }

    /// Returns the next direction the snake should go
    Direction next_move();

    /// Set a new target
    void set_target (Coordinate tgt) { 
        clear_path();
        target = tgt; 
    }

    /// Set a new snake
    void set_snake (Snake& snk) {
        clear_path();
        snake = snk; 
    }

    /// Set a new level grid
    void set_level (std::vector<std::vector<char>> lvl) { 
        clear_path();
        level = lvl; 
    }

    /// Print the current state of AI's stacks. Used for debugging.
    void print_state(std::stack<std::stack<Snake>> in);
};

#endif