// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"
#include <iterator>


Puzzle::Puzzle() {}

Puzzle::Puzzle(int s) {
    _size = s;
    _goalState.resize(_size, 0);
    setGoal();
}

Puzzle::Puzzle(Puzzle const & src) {*this = src;}

Puzzle::~Puzzle() {
}

Puzzle &    Puzzle::operator=(Puzzle const & src) {
    _size = src._size;
    _openlist = src._openlist;
    _closedlist = src._closedlist;
    _goalState = src._goalState;
    return *this;
}

void        Puzzle::addToList(Node &src) {
    xy  current = src.getEmptyPiece();
    int kids[4] = { current.i+1, \
                    current.i-1, \
                    current.i-static_cast<int>(sqrt(_size)), \
                    current.i+static_cast<int>(sqrt(_size)) }; 
    for(int i = 0; i < 4; i++){
        if ((current.i % static_cast<int>(sqrt(_size)) == 0 && i == 1) || (current.i % static_cast<int>(sqrt(_size)) == sqrt(_size)-1 && i == 0));
        else if (kids[i] >= 0 && kids[i] < _size) {
            if (src.getParent() != NULL && src.getParent()->getEmptyPiece().i == kids[i]);
            else{
                Node *tmp = new Node(src.getSize());
                tmp->getChild(src, kids[i]);
         
                if (_closedlist.find(tmp->getPuzzle()) == _closedlist.end()){
                    tmp->setParent(src);
                    calculateManhattan(*tmp);
                    _openlist.push(tmp);
                    _closedlist.insert(tmp->getPuzzle());
                }
                else
                    delete tmp;
            } 
        }
    }
}

void        Puzzle::calculateManhattan(Node &n) {
    int h = 0;
    
    // if (n.getParent() != NULL && n.getParent()->getH() != 0){
    //     h = n.getParent()->getH();
    //     xy old_cor = n.getParent()->getEmptyPiece();
    //     xy new_cor = n.getEmptyPiece();
    //     int newpos = abs(old_cor.x - _mapGoal.find(n.getPuzzle()[old_cor.i])->second.x) + abs(old_cor.y - _mapGoal.find(n.getPuzzle()[old_cor.i])->second.y);
    //     int oldpos = abs(new_cor.x - _mapGoal.find(n.getPuzzle()[old_cor.i])->second.x) + abs(new_cor.y - _mapGoal.find(n.getPuzzle()[old_cor.i])->second.y);
    //     h = h - oldpos + newpos;
    //     n.setH(h);
    //     return;
    // }
    std::vector<int> grid = n.getPuzzle();
    for (int i = 0; i < _size; i++) {
        if (grid[i] != 0){
            h += abs((i/static_cast<int>(sqrt(_size))) - _mapGoal.find(grid[i])->second.y) + abs((i%static_cast<int>(sqrt(_size))) - _mapGoal.find(grid[i])->second.x);
        }
    }
    std::cout << "babies\n";
    n.print();
    std::cout << h << std::endl;
    n.setH(h);
}



const std::vector<int>  Puzzle::getGoal() const {return _goalState;}

void    Puzzle::setGoal(){
    xy coordinates;
    coordinates.x = 0;
    coordinates.y = 0;
    coordinates.i = 0;
    int val = 1;
    while (val < _size) {
        for (;coordinates.x < sqrt(_size) && _goalState[coordinates.i] == 0 && val < (_size); coordinates.x++, val++, coordinates.i++){
            _goalState[coordinates.i] = val;
            _mapGoal.insert(std::make_pair(val, coordinates));
        }
        for (coordinates.x--,coordinates.y++; coordinates.y < sqrt(_size) && _goalState[coordinates.i] == 0 && val < (_size); val++, coordinates.y++, coordinates.i++) {
            _goalState[coordinates.i] = val;
            _mapGoal.insert(std::make_pair(val, coordinates));
        }
        for (coordinates.x--, coordinates.y--; coordinates.x >= 0 && _goalState[coordinates.i] == 0 && val < (_size); val++, coordinates.x--, coordinates.i++) {
            _goalState[coordinates.i] = val;
            _mapGoal.insert(std::make_pair(val, coordinates));
        }
        for (coordinates.y--, coordinates.x++; coordinates.y >= 0 && _goalState[coordinates.i] == 0 && val < (_size); val++, coordinates.y--, coordinates.i++) {
            _goalState[coordinates.i] = val;
            _mapGoal.insert(std::make_pair(val, coordinates));
        }
        coordinates.y++;
        coordinates.x++;
    }
    for (int i = 1; i < 16; i++){
        std::cout << i << " x=  " << _mapGoal[i].x << " y=  " << _mapGoal[i].y << std::endl;
    }
}

std::unordered_set<std::vector<int>, ComparePuzzle>&    Puzzle::getClosedList() {
    return _closedlist;
}

std::priority_queue<Node*, std::vector<Node*>, CompareF >&     Puzzle::getOpenList() {
    return _openlist;
}


// 1   2   3   4
// 12  13  14  5
// 11  0   15  6
// 10  9   8   7

//         x       y
// 1       0       0       
// 2       1       0
// 3       2       0
// 4       3       0
// 5       3       1
// 6       3       2
// 7       3       3
// 8       2       3
// 9       1       3
// 10      0       3
// 11      0       2
// 12      0       1
// 13      1       1
// 14      2       1
// 15      2       2