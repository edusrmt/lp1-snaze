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

    /// Returns a vector with all possible one step moves as Snapshots
    std::stack<Snake> check_neighbors (Snake snk, std::vector<Snake> v = std::vector<Snake>()) {
        std::cout << "Wait, I'm looking around (" << snk.body[0].row << ", " << snk.body[0].col << ")" << std::endl;
        std::stack<Snake> possib;
        Coordinate head = snk.body[0];
        Direction backwards;

        // We don't want moving backwards to be a possible move
        switch (snk.facing) {
            case Direction::Up:
            backwards = Direction::Down;
            break;

            case Direction::Right:
            backwards = Direction::Left;
            break;

            case Direction::Down:
            backwards = Direction::Up;
            break;

            case Direction::Left:
            backwards = Direction::Right;
            break;
        
            default:
            break;
        }

        /** Check all possible one step moves in two steps, i.e., find wich possibilities satisfy:
         * 1. Direction is not backwards 
         * 2. Next position isn't a wall
         * Simulates snake after moving
         * 3. Snake wouldn't bite itself
         * 4. Possible snake hasn't been tested yet
        */

        if (backwards != Direction::Up &&
            (level[head.row - 1][head.col] == ' ' || level[head.row - 1][head.col] == '*')) {
                Snake hyp_snake = snk;
                hyp_snake.move(Direction::Up);

                // Is the head colliding with another body part?
                bool bite = false;
                for (size_t i = 1; i < hyp_snake.body.size(); i++) {
                    if(hyp_snake.body[0] == hyp_snake.body[i]) {
                        bite = true;
                        break;
                    }
                }

                // If it didn't bite and this hypothetical snake hasn't been tested yet
                if (!bite && std::find(v.begin(), v.end(), hyp_snake) == v.end())
                    possib.push(hyp_snake); 
        }

        if (backwards != Direction::Right &&
            (level[head.row][head.col + 1] == ' ' || level[head.row][head.col + 1] == '*')) {
                Snake hyp_snake = snk;
                hyp_snake.move(Direction::Right);

                // Is the head colliding with another body part?
                bool bite = false;
                for (size_t i = 1; i < hyp_snake.body.size(); i++) {
                    if(hyp_snake.body[0] == hyp_snake.body[i]) {
                        bite = true;
                        break;
                    }
                }

                // If it didn't bite and this hypothetical snake hasn't been tested yet
                if (!bite && std::find(v.begin(), v.end(), hyp_snake) == v.end())
                    possib.push(hyp_snake); 
        }

        if (backwards != Direction::Down &&
            (level[head.row + 1][head.col] == ' ' || level[head.row + 1][head.col] == '*')) {
                Snake hyp_snake = snk;
                hyp_snake.move(Direction::Down);

                // Is the head colliding with another body part?
                bool bite = false;
                for (size_t i = 1; i < hyp_snake.body.size(); i++) {
                    if(hyp_snake.body[0] == hyp_snake.body[i]) {
                        bite = true;
                        break;
                    }
                }

                // If it didn't bite and this hypothetical snake hasn't been tested yet
                if (!bite && std::find(v.begin(), v.end(), hyp_snake) == v.end())
                    possib.push(hyp_snake); 
        }
        
        if (backwards != Direction::Left &&
            (level[head.row][head.col - 1] == ' ' || level[head.row][head.col - 1] == '*')) {
                Snake hyp_snake = snk;
                hyp_snake.move(Direction::Left);

                // Is the head colliding with another body part?
                bool bite = false;
                for (size_t i = 1; i < hyp_snake.body.size(); i++) {
                    if(hyp_snake.body[0] == hyp_snake.body[i]) {
                        bite = true;
                        break;
                    }
                }

                // If it didn't bite and this hypothetical snake hasn't been tested yet
                if (!bite && std::find(v.begin(), v.end(), hyp_snake) == v.end())
                    possib.push(hyp_snake); 
        }


        std::cout << "I can go in " << possib.size() << " directions!" << std::endl;
        return possib;
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
};

#endif