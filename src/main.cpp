#include "../include/snaze-game.hpp"

int main (int argc, char* argv[]) {
    // Creates a new instance of Snaze
    SnazeGame game;

    // Tries to initialize game from given input
    if(!game.initialize_game(argc, argv))
        return 1;

    while (not game.game_over()) {   
        game.wait();
        game.update();
        game.render();
    }
    
    game.end_game();

    return 0;
}