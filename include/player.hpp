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

    void clear_path () {
        while(!path.empty()) {
            path.pop();
        }
    }

    /// Returns a vector with all possible one step moves as Snapshots
    std::stack<Snake> check_neighbors (Snake snk, std::vector<Coordinate> v = std::vector<Coordinate>()) {
        std::stack<Snake> possib;
        Coordinate head = snk.body[0];


        /** Check all possible one step moves in two steps, i.e., find wich possibilities satisfy:
         * 1. Next position isn't a wall
         * Simulates snake after moving
         * 2. Snake wouldn't bite itself
         * 3. Possible snake hasn't been tested yet
        */
       //std::cout << "UP BLOCK: " << level[head.row - 1][head.col] << std::endl;

       //std::cout << "[ ";
        if ((level[head.row - 1][head.col] == ' ' || level[head.row - 1][head.col] == '*')) {
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
                if (!bite && std::find(v.begin(), v.end(), hyp_snake.body[0]) == v.end()) {
                    possib.push(hyp_snake); 
                    //std::cout << hyp_snake.body[0] << " ";
                }
        }

        if ((level[head.row][head.col + 1] == ' ' || level[head.row][head.col + 1] == '*')) {
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
                if (!bite && std::find(v.begin(), v.end(), hyp_snake.body[0]) == v.end()){
                    possib.push(hyp_snake); 
                    //std::cout << hyp_snake.body[0] << " ";
                }
        }

        if ((level[head.row + 1][head.col] == ' ' || level[head.row + 1][head.col] == '*')) {
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
                if (!bite && std::find(v.begin(), v.end(), hyp_snake.body[0]) == v.end()){
                    possib.push(hyp_snake); 
                    //std::cout << hyp_snake.body[0] << " ";
                }
        }
        
        if ((level[head.row][head.col - 1] == ' ' || level[head.row][head.col - 1] == '*')) {
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
                if (!bite && std::find(v.begin(), v.end(), hyp_snake.body[0]) == v.end()) {
                    possib.push(hyp_snake); 

                    //std::cout << hyp_snake.body[0] << " ";
                }
        }
        //std::cout << "]" << std::endl;
        // Order possible moves so the ones that leads the snake closer to the target are tested first
        std::vector<Snake> closer, further;

        size_t i_count = possib.size();
        for (size_t i = 0; i < i_count; i++) {
            Snake e = possib.top();
            if (leads_closer(snk.body[0], e.body[0]))
                closer.push_back(e);
            else
                further.push_back(e);

            possib.pop();
        }

        for (Snake far : further)
            possib.push(far);

        for (Snake close : closer)
            possib.push(close);
        
        //std::cout << possib.size() << " possible moves from " << snk.body[0] << "!" << std::endl;

        return possib;
    }

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

    void print_state(std::stack<std::stack<Snake>> in);
};

#endif