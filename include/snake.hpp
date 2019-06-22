#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "./util.hpp"

class Snake {
    
    public:
    std::deque<Coordinate> body;        //!< Storage of all body pieces from head to tail
    Direction facing = Direction::Up;   //!< Direction that the snake is looking to
    bool alive;                         //!< Is the snake alive?

    /// Default constructor
    Snake () : alive{false} { }

    /// Initialization constructor 
    Snake (Coordinate head) : alive{true} {
        body.push_front(head);
    }

    /// Moves the snake to the given direction
    void move (Direction dir);
};

#endif