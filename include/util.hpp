#ifndef UTIL_H
#define UTIL_H

#include <iostream>

struct Coordinate
{
    int row;    //!< Row index
    int col;    //!< Column index

    /// Default constructor
    Coordinate () : row{-1}, col{-1} { }

    /// Constructor with initialization
    Coordinate (int r, int c) : row{r}, col{c} { }

    /// Equality comparison operator
    bool operator== (const Coordinate& other) {
        return row == other.row && col == other.col;
    }

    /// Inequality comparison operator
    bool operator!= (const Coordinate& other) {
        return row != other.row || col != other.col;
    }

    /// Output operator
    friend std::ostream& operator<< (std::ostream &out, const Coordinate& cood);
};

/// Output operator
inline std::ostream& operator<< (std::ostream &out, const Coordinate& cood) {
    out << "(" << cood.row << ", " << cood.col << ")";
    return out;
}

/// Absolute directions
enum Direction {
    Up,
    Right,
    Down,
    Left
};

#endif