#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "./util.hpp"

class Snake {
    private:
    std::deque<Coordinate> body;    //!< Storage of all body pieces from head to tail

    public:
    Direction facing;               //!< Direction that the snake is looking to

    /// Default constructor
    Snake () { }

    /// Initialization constructor 
    Snake (Coordinate head) {
        body.push_front(head);
    }

    /// Checks if any piece of the snake is at given position
    bool is_at (Coordinate pos);

    /// Checks if the snake's head is at this position
    bool is_head (Coordinate pos) {
        return body[0] == pos;
    }

    /// Moves the snake to the given direction
    void move (Direction dir);
};

#endif