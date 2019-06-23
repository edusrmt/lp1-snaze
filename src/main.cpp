#include "../include/snaze-game.hpp"

int main (int argc, char* argv[]) {
    // Creates a new instance of Snaze
    SnazeGame game;

    // Tries to initialize game from given input
    if(!game.initialize_game(argc, argv))
        return 1;

    for (int i = 0; i < 30; i++) {      
        game.wait();
        game.update();
        game.render();
    }

    return 0;
}