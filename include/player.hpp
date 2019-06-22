#ifndef PLAYER_H
#define PLAYER_H

#include "./snake.hpp"
#include "./util.hpp"

class Player {
    private:
    Snake snake;        //!< The snake this AI is simulating

    /// Looks for the best path to the fruit
    bool find_solution ();

    public:
    /// Returns the next direction the snake should go
    Direction next_move();
};

#endif