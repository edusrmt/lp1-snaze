#include "../include/snake.hpp"

bool Snake::is_at (Coordinate pos) {
    for (Coordinate cood : body) {
        if (pos == cood)
            return true;
    }

    return false;
}

void Snake::move (Direction dir) {
    facing = dir;
    body.pop_back();
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