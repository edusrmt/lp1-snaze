#include "../include/snake.hpp"

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