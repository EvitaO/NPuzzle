// Copyright 2021 <eovertoo>

#include "Node.hpp"

Node::Node() {}

Node::Node(int s) {
    _size = s;
    _g = 0;
    _h = 0;
    _puzzle.resize(_size, 0);
    _parent = NULL;  
    _hash = 0;  
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
    
    _puzzle.resize(_size, 0);    
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

std::vector<int>   Node::getPuzzle() const {return _puzzle;}

xy&      Node::getEmptyPiece() {
    return _coordinates;
}

void   Node::getChild(Node & src, int swapi) {
    xy coordinates = src.getEmptyPiece();
    _puzzle = src.getPuzzle();
    _puzzle[coordinates.i] = _puzzle[swapi];
    _puzzle[swapi] = 0;
    _coordinates.x = swapi % static_cast<int>(sqrt(_size));
    _coordinates.y = swapi / static_cast<int>(sqrt(_size));
    _coordinates.i = swapi;
    setHash(_puzzle);
}

uint64_t    Node::getHash() const{
    return _hash;
}

void    Node::setPuzzle(std::vector<int> &arr) {
    _puzzle = arr;
    for (int i = 0; i < _size; i++) {
        if (_puzzle[i] == 0) {
            _coordinates.x = i % static_cast<int>(sqrt(_size));
            _coordinates.y = i / static_cast<int>(sqrt(_size));
            _coordinates.i = i;
        }
    }
    setHash(_puzzle);
}

void    Node::setH(int h) {_h = h;}

void    Node::setParent(Node &parent){
    _parent = &parent;
    _g = parent.getG() + 1;
}

void    Node::setHash(std::vector<int> src){
    size_t         s = src.size();
    // for(int i = 0; i < s; i++){
    //     if (src[i] != 0) {
    //         _hash += (i + src[i]) % s;
    //         std::cout << "bb    " << _hash << std::endl;
    //     }
    // }
    // std::cout << "cc    " << _hash << std::endl;

    for(auto& i : src) {
        s ^= i + 0x9e3779b9 + (s << 6) + (s >> 2);
    }
    _hash = s;
    // std::cout << _hash << "     t \n";
}

void    Node::print() {
    for (int i = 0; i < _size ; i++) {
        if (i % static_cast<int>(sqrt(_size)) == 0 && i != 0)
            std::cout << std::endl;
        std::cout << _puzzle[i] << " ";
    }
    std::cout << std::endl;
}
