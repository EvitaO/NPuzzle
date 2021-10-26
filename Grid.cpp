// Copyright 2021 <eovertoo>

#include "Grid.hpp"

Grid::Grid() {}

Grid::Grid(int s) {
    _size = s;
    _puzzle = new int*[_size];
    for (int i = 0; i < 3; i++)
        _puzzle[i] = new int[_size];
}

Grid::Grid(Grid const & src) {
    *this = src;
}

Grid::~Grid() {}

Grid &  Grid::operator=(Grid const & src) {
    _f = src.getF();
    _g = src.getG();
    _h = src.getH();
    _size = src.getSize();

    _puzzle = new int*[_size];
    for (int i = 0; i < 3; i++)
        _puzzle[i] = new int[_size];

    _parent = src.getParent();
    _puzzle = src.getPuzzle();
    //setPuzzle(src.getPuzzle());
    return *this;
}

int     Grid::getF() const {return _f;}

int     Grid::getG() const {return _g;}

int     Grid::getH() const {return _h;}

int     Grid::getSize() const {return _size;}

Grid*   Grid::getParent() const {return _parent;}

int**   Grid::getPuzzle() const {return _puzzle;}

xy      Grid::getEmptyPiece() const {
    xy cordinates;
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            if (_puzzle[i][j] == 0) {
                cordinates.x = j;
                cordinates.y = i;
            }
        }
    }
    return cordinates;
}

int**   Grid::getChild(int x, int y, int swapx, int swapy) {
    int **arr;

    arr = new int*[_size];
    for (int i = 0; i < 3; i++)
        arr[i] = new int[_size];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            arr[i][j] = _puzzle[i][j];
    }
    if (swapx >= 0 && swapx < _size && swapy >= 0 && swapy < _size) {
        arr[y][x] = arr[swapy][swapx];
        arr[swapy][swapx] = 0;
        return arr;
    }
    return NULL;
}

void    Grid::setPuzzle(int** arr) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            _puzzle[i][j] = arr[i][j];
    }
}


