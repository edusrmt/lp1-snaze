#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "./util.hpp"

class Snake {
    
    public:
    std::deque<Coordinate> body;        //!< Storage of all body pieces from head to tail
    Direction facing = Direction::Up;   //!< Direction that the snake is looking to
    bool alive;                         //!< Is the snake alive?
    bool grow = false;                  //!< Is the snake able to grow?

    /// Default constructor
    Snake () : alive{false} { }

    /// Initialization constructor 
    Snake (Coordinate head) : alive{true} {
        body.push_front(head);
    }

    /// Moves the snake to the given direction
    void move (Direction dir);

    /// Checks if any body piece is located at given coordinate
    bool is_at (Coordinate pos);

    // Two snakes are equal if all body parts are in the same positions
    bool operator== (const Snake& other) {
        if (body.size() == other.body.size()) {
            for (size_t i = 0; i < body.size(); i++) {
                if (body[i] != other.body[i])
                    return false;
            }

            return true;
        }

        return false;
    }
};

#endif