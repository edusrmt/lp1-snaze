#ifndef UTIL_H
#define UTIL_H

struct Coordinate
{
    int row;
    int col;

    /// Constructor with initialization
    //Coordinate (int row, int col) : row{row}, col{col} { }

    /// Default constructor
    Coordinate () : row{-1}, col{-1} { }

    Coordinate (int r, int c) : row{r}, col{c} { }

    /// Equality comparison operator
    bool operator== (const Coordinate& other) {
        return row == other.row && col == other.col;
    }

    /// Inequality comparison operator
    bool operator!= (const Coordinate& other) {
        return row != other.row || col != other.col;
    }
};

enum Direction {
    Up,
    Right,
    Down,
    Left
};

#endif