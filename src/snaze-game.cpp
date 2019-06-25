#include "../include/snaze-game.hpp"

using namespace std;

bool SnazeGame::initialize_game (int argc, char* argv[]) {
    // Prints greetings message
    cout << "      ---> Welcome to the classic Snake Game <---" << endl;
    cout << "             Developed by Eduardo & Victor" << endl;
    cout << "-------------------------------------------------------" << endl;

    // Validates input
    if (argc == 1) {
        cout << ">>> No input file was given!" << endl;
        return false;
    }

    // Trying to open filepath given by the user
    ifstream input;
    input.open(argv[1]);

    // Check wether input file was succesfully opened
    if(!input.is_open()) {
        cout << ">>> Failed to open input file!" << endl;
        return false;
    }  

    // Reads informations from input file
    int rows, cols;
    while (input >> rows >> cols) {
        // Checks for minimum value of dimensions
        if (rows < 1 || cols < 1) {
            cout << ">>> Failed to load level: dimension can't be lower than 1!" << endl;
            return false;
        }

        // Checks for maximum value of dimensions
        if (rows > 100 || cols > 100) {
            cout << ">>> Failed to load level: dimension can't be greater than 100!" << endl;
            return false;
        }

        /// Creates a new level with given dimensions
        Level level(rows, cols);

        // Initialize level with input data
        string line;
        getline(input, line);

        for (int i = 0; i < rows; i++) {
            getline(input, line);
            int j = 0;

            for (char val : line) {                
                level.set_char(val, i, j++);
            }
        }

        // Stores level into the vector, if it has a spawn point
        if(level.spawn != Coordinate())
            levels.push_back(level);
    }

    ai = new Player(levels[0].grid, levels[0].snake, levels[0].fruit);
    level_amt = levels.size();

    // Prints start message
    cout << " Levels loaded: " << level_amt << " | Snake lives: 5 | Apples to eat: 10" << endl;
    cout << "     Clear all levels to win the game. Good luck!" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << ">>> Press <ENTER> to start the game!" << endl;
    render();
    paused = true;
    input.close();
    return true;
}

bool SnazeGame::game_over () {
    return levels.size() == 0 || lives == 0;
}

void SnazeGame::render () {
    if (paused)
        return;

    // Can't render a level that doesn't exist
    if (levels.size() == 0) {
        cout << "GAME OVER" << endl;
        return;
    }

    // Prints header
    cout << msg << endl;

    if (msg != "") {
        msg = "";
        cout << ">>> Press <ENTER> to continue!" << endl;
        paused = true;
    }

    cout << "Lives: ";

    // Prints lives display
    for (int i = 0; i < 5; i++) {
        if (i < lives)
            cout << "\u2665";
        else
            cout << ".";
    }

    cout << " | Score: " << score << " | Food eaten: " << food << " of 10" << endl;
    cout << "-------------------------------------------------------" << endl;

    // Prints level
    cout << levels[0] << endl;
    cout << "-------------------------------------------------------" << endl;
}

void SnazeGame::update () {
    // Current levels is always at index 0
    Level& cur = levels[0];   

    // At the beginning of the level, spawn a fruit and a snake
    bool begin = cur.fruit.row == -1 || cur.fruit.col == -1;
    if(begin) {
        spawn_fruit(); 
        spawn_snake(); 
    }   

    if (!cur.snake.alive && !paused)
        spawn_snake();
    
    // Move the snake
    if(!begin && food < 10) {
        Snake last_snake = cur.snake;
        cur.snake.move(ai->next_move());

        // If the snakes crashes after moving
        if (cur.grid[cur.snake.body[0].row][cur.snake.body[0].col] == '#') {
            msg = "Oh no! Anaconda crashed while trying to go to the fruit!";
            cur.snake = last_snake;
            cur.snake.alive = false;
            render();
            lives--;    
            paused = true;                    
        }
    }
    
    // Ate the fruit
    if (levels[0].snake.body[0] == levels[0].fruit) {
        score += cur.snake.body.size();
        food++;
        cur.snake.grow = true;
        
        if (food < 10)
            spawn_fruit();        
    }
    
    // Won the level
    if (food == 10) {
        msg = ">>> Completed level " + to_string(level_amt - levels.size() + 1) + " (of " + to_string(level_amt) + ") successfully!";
        render();
        levels.pop_front();
        food = 0;

        if(levels.size() > 0)
            ai->set_level(levels[0].grid);

        paused = true;
    }
}

void SnazeGame::wait () {
    if (paused) {
        cin.ignore();
        paused = false;
    } else {
        this_thread::sleep_for(chrono::milliseconds((100)));
    }
}

void SnazeGame::spawn_snake () {     
        levels[0].snake = Snake(levels[0].spawn);
        ai->set_snake(levels[0].snake);    
}

void SnazeGame::spawn_fruit () {    
    int f_row = rand() % levels[0].r, f_col = rand() % levels[0].c;

    // While the target place is not a space or a star, or the snake is at it
    while ((levels[0].grid[f_row][f_col] != ' ' && levels[0].grid[f_row][f_col] != '*')
         || levels[0].snake.is_at(Coordinate(f_row, f_col))) {          
        f_row = rand() % levels[0].r;
        f_col = rand() % levels[0].c;
    }
      
    levels[0].fruit = Coordinate(f_row, f_col);    
    ai->set_snake(levels[0].snake);
    ai->set_target(levels[0].fruit);
}

void SnazeGame::end_game () {
    if (lives > 0) {
        cout << "+--------------------------------------+" << endl;
        cout << "|  CONGRATULATIONS, you won the game!  |" << endl;  
        cout << "|         Thanks for playing!          |" << endl;
        cout << "+--------------------------------------+" << endl;
    } else {
        cout << "+--------------------------------+" << endl;
        cout << "|  SORRY, you couldn't make it!  |" << endl;  
        cout << "|           Try again!           |" << endl;
        cout << "+--------------------------------+" << endl;
    }
}