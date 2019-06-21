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

            for (char val : line)
                level.set_char(val, i, j++);
        }

        // Stores level into the vector
        levels.push_back(level);
    }

    cout << " Levels loaded: " << levels.size() << " | Snake lives: 5 | Apples to eat: 10" << endl;
    cout << "     Clear all levels to win the game. Good luck!" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << ">>> Press <ENTER> to start the game!" << endl;
    
    return true;
}