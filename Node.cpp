// Copyright 2021 <eovertoo>

#include "Node.hpp"

Node::Node() {}

Node::Node(int s) {
    _size = s;
    _g = 0;
    _h = 0;
    _puzzle.resize(_size, std::vector<int>(_size, 0));
    _parent = NULL;    
}

Node::Node(Node const & src) {
    *this = src;
}

Node::~Node() {
}

Node &  Node::operator=(Node const & src) {
    //_f = src.getF();
    _g = src.getG();
    _h = src.getH();
    _size = src.getSize();
    // std::cout << &src << std::endl;
    
    _puzzle.resize(_size, std::vector<int>(_size, 0));    
    _parent = src.getParent();
    // std::cout << &_parent << std::endl;
    _puzzle = src.getPuzzle();
    return *this;
}

int     Node::getF() const {return (_g + _h);}

int     Node::getG() const {return _g;}

int     Node::getH() const {return _h;}

int     Node::getSize() const {return _size;}

Node*   Node::getParent() const {return _parent;}

std::vector<std::vector<int> >   Node::getPuzzle() const {return _puzzle;}

xy      Node::getEmptyPiece() const {
    return _coordinates;
}

void   Node::getChild(Node & src, int swapx, int swapy) {
    // std::vector<std::vector<int> > arr(_size, std::vector<int>(_size, 0));
    
    xy coordinates = src.getEmptyPiece();
    _puzzle = src.getPuzzle();
    _puzzle[coordinates.y][coordinates.x] = _puzzle[swapy][swapx];
    _puzzle[swapy][swapx] = 0;
    _coordinates.x = swapx;
    _coordinates.y = swapy;
    // return arr;
}

void    Node::setPuzzle(std::vector<std::vector<int> > arr) {
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++){
            _puzzle[i][j] = arr[i][j];
            if (_puzzle[i][j] == 0) {_coordinates.x = j; _coordinates.y = i;}
        }
    }
}

void    Node::setH(int h) {_h = h;}

void    Node::setParent(Node &parent){
    _parent = &parent;
    _g = parent.getG() + 1;
}

void    Node::print() {
    for (int i = 0; i < _size ; i++) {
        for (int j = 0; j < _size; j++)
            std::cout << _puzzle[i][j] << " ";
        std::cout << std::endl;
    }
}
