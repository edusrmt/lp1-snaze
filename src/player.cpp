#include "../include/player.hpp"

using namespace std;

bool Player::find_solution () {
    std::cout << "Trying to find a path!" << std::endl;

    stack<stack<Snake>> possible;       // Stack of stack of possible snakes
    vector<Snake> tested;               // Vector of all rejected snakes

    // Starts with current possibility
    stack<Snake> init = check_neighbors(snake, tested); 

    // If we don't start with a dead end, try to find a path
    if (init.size() != 0) {
        std::cout << "Here we go!" << std::endl;
        possible.push(init);
        stack<Snake> cur_stack = possible.top();
        Snake cur_snake = cur_stack.top();

        // Repeat until the path is found or ran out of possibilities
        for (int i = 0; i < 6; i++) {
        //while (cur_snake.body[0] != target && !possible.empty()) {
            std::cout << "Thinking..." << std::endl;
            std::cout << "If I was at (" << cur_snake.body[0].row << ", " << cur_snake.body[0].col << ")..." << std::endl;
            // Gets all possible moves from current position
            stack<Snake> neighs = check_neighbors(cur_snake, tested);

            if (neighs.size() == 0) {
                // If we reach a dead end, try another possibility in this stack
                tested.push_back(cur_stack.top());
                cur_stack.pop();

                // If there is no possibility in this stack, go to previous stack
                if (cur_stack.size() == 0) {
                    possible.pop();                 // Removes stack
                    cur_stack = possible.top();     // Updates current stack
                    cur_snake = cur_stack.top();    // Updates current snake
                    std::cout << "Should return to think about (" << cur_snake.body[0].row << ", " << cur_snake.body[0].col << ")" << std::endl;
                }

                cur_snake = cur_stack.top();        // Updates current snake
            } else {
                // Adds new stack to possibilities
                possible.push(neighs);

                // Update current tests
                cur_stack = possible.top();
                cur_snake = cur_stack.top();
            }

            //std::cout << "Thinking about (" << cur_snake.body[0].row << ", " << cur_snake.body[0].col << ")" << std::endl;
        }

        std::cout << "JUST A MOMENT!" << std::endl;
        std::cout << "(" << cur_snake.body[0].row << ", " << cur_snake.body[0].col << ") == " << "(" << target.row << ", " << target.col << ")?" << std::endl;

        // If we've found a path to the fruit, save it
        if (cur_snake.body[0] == target) {
            std::cout << "GOT IT!" << std::endl;
            for(size_t i = 0; i < possible.size(); i++) {
                // Stack the first possibility of each stack to mount the path
                path.push(possible.top().top().facing);
                possible.pop();
            }

            std::cout << "Found a new path with " << path.size() << " steps!" << std::endl;

            stack<Direction> spy;
            size_t count = path.size();
            for (size_t i = 0; i < count; i++) {
                spy.push(path.top());
                std::cout << i + 1 << "º go " << spy.top() << std::endl;
                path.pop();
            }

            for (size_t i = 0; i < spy.size(); i++) {
                path.push(spy.top());
                spy.pop();
            }

            return true;
        }
    }
    
    std::cout << "Couldn't find a path!" << std::endl;
    return false;    
}

Direction Player::next_move () {
    Direction next = snake.facing;  
    std::cout << "I need to walk " << path.size() << " steps!" << std::endl;
    if (path.size() > 0 || find_solution()) {
        // If there is a path to be followed, return the next step
        std::cout << "Haha, I know what to do!" << std::endl;
        next = path.top();
        std::cout << "I should go " << next << "!" << std::endl;
        path.pop();
    } /* else if (find_solution()) {
        // If there is no path to be followed, go to a possible step
        vector<Snake> tested;
        stack<Snake> neighs = check_neighbors(snake);

        if(neighs.size() > 0)
            next = neighs.top().facing;
    }*/

    return next;
}