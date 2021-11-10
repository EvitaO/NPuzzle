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
    
    if (n.getParent() != NULL && n.getParent()->getH() != 0){
        h = n.getParent()->getH();
        xy old_cor = n.getParent()->getEmptyPiece();
        xy new_cor = n.getEmptyPiece();
        int newpos = abs(old_cor.x - _mapGoal.find(n.getPuzzle()[old_cor.i])->second.x) + abs(old_cor.y - _mapGoal.find(n.getPuzzle()[old_cor.i])->second.y);
        int oldpos = abs(new_cor.x - _mapGoal.find(n.getPuzzle()[old_cor.i])->second.x) + abs(new_cor.y - _mapGoal.find(n.getPuzzle()[old_cor.i])->second.y);
        h = h - oldpos + newpos;
        n.setH(h);
        return;
    }
    std::vector<int> grid = n.getPuzzle();
    for (int i = 0; i < _size; i++) {
        if (grid[i] != 0){
            h += abs((i/static_cast<int>(sqrt(_size))) - _mapGoal.find(grid[i])->second.y) + abs((i%static_cast<int>(sqrt(_size))) - _mapGoal.find(grid[i])->second.x);
        }
    }
    n.setH(h);
}



const std::vector<int>  Puzzle::getGoal() const {return _goalState;}

void    Puzzle::setGoal(){
    xy coordinates;
    coordinates.x = 0;
    coordinates.y = 0;
    coordinates.i = 0;
    int val = 1;
    if (_size == 16){
        _goalState[0] = 1;
        _goalState[1] = 2;
        _goalState[2] = 3;
        _goalState[3] = 4;
        _goalState[4] = 12;
        _goalState[5] = 13;
        _goalState[6] = 14;
        _goalState[7] = 5;
        _goalState[8] = 11;
        _goalState[9] = 0;
        _goalState[10] = 15;
        _goalState[11] = 6;
        _goalState[12] = 10;
        _goalState[13] = 9;
        _goalState[14] = 8;
        _goalState[15] = 7;
     
        coordinates.x = 0;        
        coordinates.y = 0;        
        _mapGoal.insert(std::make_pair(1, coordinates));

        coordinates.x = 1;        
        coordinates.y = 0;        
        _mapGoal.insert(std::make_pair(2, coordinates));

        coordinates.x = 2;        
        coordinates.y = 0;        
        _mapGoal.insert(std::make_pair(3, coordinates));

        coordinates.x = 3;        
        coordinates.y = 0;        
        _mapGoal.insert(std::make_pair(4, coordinates));

        coordinates.x = 3;        
        coordinates.y = 1;        
        _mapGoal.insert(std::make_pair(5, coordinates));

        coordinates.x = 3;        
        coordinates.y = 2;        
        _mapGoal.insert(std::make_pair(6, coordinates));

        coordinates.x = 3;        
        coordinates.y = 3;        
        _mapGoal.insert(std::make_pair(7, coordinates));

        coordinates.x = 2;        
        coordinates.y = 3;        
        coordinates.i = 8; 
        _mapGoal.insert(std::make_pair(8, coordinates));

        coordinates.x = 1;        
        coordinates.y = 3;        
        _mapGoal.insert(std::make_pair(9, coordinates));

        coordinates.x = 0;        
        coordinates.y = 3;        
        _mapGoal.insert(std::make_pair(10, coordinates));

        coordinates.x = 0;        
        coordinates.y = 2;        
        _mapGoal.insert(std::make_pair(11, coordinates));
 
        coordinates.x = 0;        
        coordinates.y = 1;        
        _mapGoal.insert(std::make_pair(12, coordinates));

        coordinates.x = 1;        
        coordinates.y = 1;        
        _mapGoal.insert(std::make_pair(13, coordinates));

        coordinates.x = 2;        
        coordinates.y = 1;        
        _mapGoal.insert(std::make_pair(14, coordinates));

        coordinates.x = 2;        
        coordinates.y = 2;        
        _mapGoal.insert(std::make_pair(15, coordinates));
        return;
    }

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