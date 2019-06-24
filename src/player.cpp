#include "../include/player.hpp"

using namespace std;

void Player::print_state(std::stack<std::stack<Snake>> in) {
    cout << endl << "CURRENT STATE:" << endl;

    size_t i_count = in.size();
    for(size_t i = 0; i < i_count; i++) {
        cout << "| ";

        size_t j_count = in.top().size();
        for(size_t j = 0; j < j_count; j++) {
            cout << in.top().top().body[0] << " ";
            in.top().pop();
        }
        cout << endl;
        in.pop();
    }    
}

bool Player::find_solution () {
    clear_path();
    cout << "find_solution() " << endl;
    stack<stack<Snake>> possible;       // Stack of stack of possible snakes
    vector<Coordinate> tested;          // Vector of all rejected snakes

    // Starts with current possibility
    stack<Snake> init = check_neighbors(snake, tested); 

    // If we don't start with a dead end, try to find a path
    if (init.size() != 0) {
        possible.push(init);
        stack<Snake> *cur_stack = &possible.top();
        Snake cur_snake = cur_stack->top();

        // Repeat until the path is found or ran out of possibilities
        while (cur_snake.body[0] != target && !possible.empty()) {
            //print_state(possible);
            // Gets all possible moves from current position
            stack<Snake> neighs = check_neighbors(cur_snake, tested);

            tested.push_back(cur_stack->top().body[0]);

            if (neighs.size() == 0) {
                // If we reach a dead end, try another possibility in this stack  
                cur_stack->pop();                 
            
                // If there is no possibility in this stack, go to previous stack
                if (cur_stack->empty())                 
                    possible.pop();                     // Removes stack

                // If there is any possibility left to test
                if (!possible.empty()) {
                    cur_stack = &(possible.top());      // Updates current stack                
                    cur_snake = cur_stack->top();       // Updates current snake
                }                             
            } else {
                // Adds new stack to possibilities
                possible.push(neighs);

                // Update current tests
                cur_stack = &(possible.top());
                cur_snake = cur_stack->top();
            }
        }

        // If we've found a path to the fruit, save it
        if (cur_snake.body[0] == target) {
            size_t i_count = possible.size();
            for(size_t i = 0; i < i_count; i++) {
                // Stack the first possibility of each stack to mount the path
                path.push(possible.top().top().facing);
                possible.pop();
            }
            
            /* PRINT PATH
            cout << "PATH:" << endl;
            stack<Direction> spy = path;
            i_count = path.size();
            for(size_t i = 0; i < i_count; i++) {
                // Stack the first possibility of each stack to mount the path
                cout << spy.top() << " ";
                spy.pop();
            }

            cout << endl;*/
            

            return true;
        }
    }

    return false;    
}

Direction Player::next_move () {
    Direction next = snake.facing;
    if (path.size() > 0 || find_solution()) {
        // If there is a path to be followed, return the next step
        next = path.top();
        path.pop();
    } else {
        // If there is no path to be followed, go to a possible step
        stack<Snake> neighs = check_neighbors(snake);

        if(neighs.size() > 0)
            next = neighs.top().facing;
    }

    return next;
}