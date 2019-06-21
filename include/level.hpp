#ifndef LEVEL_H
#define LEVEL_H

class Level {
    private:
    int r;          //!< Height of the level
    int c;          //!< Width of the level
    char** level;   //!< Level data

    public:
    /// Default constructor of a level
    Level (int rows, int cols) : r{rows}, c{cols} {
        // Allocates the matrix that stores all level data
        level = new char*[r];

        for(int i = 0; i < r; i++)
            level[i] = new char[c];
    }

    /// Default destructor
    ~Level () {
        for (int i  = 0; i < r; i++)
            delete [] level[i];

        delete [] level;
    }

    /// Sets a char to specific position of the level
    void set_char(char value, int row, int col) {
        level[row][col] = value;
    }
};

#endif