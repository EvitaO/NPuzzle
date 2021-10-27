// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"

Puzzle::Puzzle() {}

Puzzle::Puzzle(int s) {_size = s;}

Puzzle::Puzzle(Puzzle const & src) {*this = src;}

Puzzle::~Puzzle() {}

Puzzle &    Puzzle::operator=(Puzzle const & src) {
    _size = src._size;
    _openlist = src._openlist;
    _closedlist = src._closedlist;
    return *this;
}

std::set<Node, ComparePuzzle>&    Puzzle::getClosedList() {
    return _closedlist;
}

std::priority_queue<Node, std::vector<Node>, CompareF >&     Puzzle::getOpenList() {
    return _openlist;
}
