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

        // Stores level into the vector
        levels.push_back(level);
    }

    // Prints start message
    cout << " Levels loaded: " << levels.size() << " | Snake lives: 5 | Apples to eat: 10" << endl;
    cout << "     Clear all levels to win the game. Good luck!" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << ">>> Press <ENTER> to start the game!" << endl;
    render();

    input.close();
    return true;
}

bool SnazeGame::game_over () {
    return levels.size() == 0;
}

void SnazeGame::render () {
    // Prints header
    string msg;
    cout << msg << endl;
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

    if(cur.fruit.row == -1 || cur.fruit.col == -1)
        spawn_fruit();

    if (!cur.snake.alive)
        spawn_snake();
    else {
        cur.snake.move(ai->next_move());
    }
}

void SnazeGame::wait () {
    this_thread::sleep_for(chrono::milliseconds((500)));
}

void SnazeGame::spawn_snake () {
    Snake newSnake(levels[0].spawn);
    levels[0].snake = newSnake;
    ai = new Player(levels[0].grid, levels[0].snake, levels[0].fruit);
}

void SnazeGame::spawn_fruit () {    
    int f_row = rand() % levels[0].r, f_col = rand() % levels[0].c;

    while(levels[0].grid[f_row][f_col] != ' ' && !levels[0].snake.is_at(Coordinate(f_row, f_col))) {
        f_row = rand() % levels[0].r;
        f_col = rand() % levels[0].c;
    }

    levels[0].fruit = Coordinate(f_row, f_col);    
}

bool SnazeGame::level_complete () {
    return false;
}