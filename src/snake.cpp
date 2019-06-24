#include "../include/snake.hpp"

bool Snake::is_at (Coordinate pos) {
    for (size_t i = 0; i < body.size(); i++) {
        if(body[i] == pos) {
            return true;
        }
    }

    return false;
}

void Snake::move (Direction dir) {
    facing = dir;

    // If it will grow, don't remove the tail
    if (!grow)
        body.pop_back();
    else
        grow = false;

    Coordinate head(body[0]);        

    switch (dir) {
        case Direction::Up:
        head.row--;
        break;

        case Direction::Right:
        head.col++;
        break;

        case Direction::Down:
        head.row++;
        break;

        case Direction::Left:
        head.col--;
        break;
    }

    body.push_front(head);
}