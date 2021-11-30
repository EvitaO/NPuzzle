#include "Node.hpp"

Node::Node() {}

Node::Node(int s) {
    _size = s;
    _g = 0;
    _h = 0;
    _puzzle.resize(_size*_size, 0);
    _parent = NULL;  
    _hash = 0;
    _direc = '0';
    _coordinates.x = 0;
    _coordinates.y = 0;
    _coordinates.i = 0;
}

Node::Node(Node const & src) {
    *this = src;
}

Node::~Node() {
}

Node &  Node::operator=(Node const & src) {
    _g = src.getG();
    _h = src.getH();
    _size = src.getSize();
    _puzzle.resize(_size*_size, 0);    
    _parent = src.getParent();
    _puzzle = src.getPuzzle();
    _coordinates = src._coordinates;
    _hash = src._hash;
    return *this;
}

void                    Node::setPuzzle(std::vector<int> &arr) {
    _puzzle = arr;
    for (int i = 0; i < (_size*_size); i++) {
        if (_puzzle[i] == 0) {
            _coordinates.x = i % _size;
            _coordinates.y = i / _size;
            _coordinates.i = i;
        }
    }
    setHash(_puzzle);
}

void                    Node::setParent(Node &parent, char flags){
    _parent = &parent;
    if (!(flags & GREEDY))
        _g = parent.getG() + 1;
}

void                    Node::setH(float h) {_h = h;}

void                    Node::setHash(std::vector<int> src){
    uint64_t         s = src.size();
    for(auto& i : src) {
        s ^= i + 0x9e3779b9 + (s << 6) + (s >> 2);
    }
    _hash = s;
}

void                    Node::setDirec(char direc) {_direc = direc;}

float                   Node::getF() const {return (_g + _h);}

int                     Node::getG() const {return _g;}

float                   Node::getH() const {return _h;}

int                     Node::getSize() const {return _size;}

uint64_t                Node::getHash() const {return _hash;}

Node*                   Node::getParent() const {return _parent;}

std::vector<int>        Node::getPuzzle() const {return _puzzle;}

xy&                     Node::getEmptyPiece() {return _coordinates;}

void                    Node::swapGrid(Node & src, int swapi) {
    xy coordinates = src._coordinates;
    _puzzle = src._puzzle;
    _puzzle[coordinates.i] = _puzzle[swapi];
    _puzzle[swapi] = 0;
    _coordinates.x = swapi % _size;
    _coordinates.y = swapi / _size;
    _coordinates.i = swapi;
    setHash(_puzzle);
}

void                    Node::printverbose(){
    for (int i = 0;i < (_size*_size); i++){
        if (i % _size == 0 && i != 0)
            std::cout << std::endl;
        std::cout << _puzzle[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void                    Node::print() {
    static int gen = 0;
    if (gen == 0)
        std::cout << MAGENTA << "Begin state\n" << RESET;
    else
        std::cout << MAGENTA << "Step: " << gen << "   Move: " << _direc << RESET << std::endl;
    for (int i = 0; i < (_size * _size); i++) {
        if (i % _size == 0 && i != 0){
            std::cout << std::endl;
            for (int i = 0; i < _size*5; i++)
                std::cout << GREEN << "_ ";
            std::cout << RESET << std::endl;
        }
        if (_puzzle[i] == 0)
            std::cout << BOLDGREEN << std::setw(4) << _puzzle[i] << std::setw(6) << " | " << RESET;
        else
            std::cout << GREEN << std::setw(4) << _puzzle[i] << std::setw(6) << " | " << RESET;
    }
    std::cout << std::endl;
    for (int i = 0; i < _size*5; i++)
        std::cout << GREEN << "_ ";
    std::cout << RESET << std::endl;
    gen++;
}
