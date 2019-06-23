#include "../include/snake.hpp"

bool Snake::is_at (Coordinate pos) {
    //std::cout << "Ough! Have to check al those " << body.size() << " pieces!" << std::endl;
    for (size_t i = 0; i < body.size(); i++) {
        //std::cout << "Is " << body[i] << " the position ? ";

        if(body[i] == pos) {
            //std::cout << "I'm here at" << pos << "!" << std::endl;
            return true;
        }

        //std::cout << "Nope" << std::endl;
    }

    //std::cout << "I'm not there at" << pos << "!" << std::endl;
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