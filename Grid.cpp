// Copyright 2021 <eovertoo>

#include "Grid.hpp"

Grid::Grid(){}

Grid::Grid(Grid const & src){
    *this = src;
}

Grid::~Grid(){}

Grid &  Grid::operator=(Grid const & src){
    _f = src.getF();
    _g = src.getG();
    _h = src.getH();

    _parent = src.getParent();
    _puzzle = src.getPuzzle();
}