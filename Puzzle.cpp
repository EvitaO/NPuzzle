// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"
#include <iterator>


Puzzle::Puzzle() {}

Puzzle::Puzzle(int s) {
    _size = s;
    setGoal();
}

Puzzle::Puzzle(Puzzle const & src) {*this = src;}

Puzzle::~Puzzle() {
    while (!(_openlist.empty())){
        Node *tmp = _openlist.top();
        _openlist.pop();
        delete tmp;
    }
}

Puzzle &    Puzzle::operator=(Puzzle const & src) {
    _size = src._size;
    _openlist = src._openlist;
    _closedlist = src._closedlist;
    return *this;
}

void        Puzzle::addToList(Node &src) {
    xy  current = src.getEmptyPiece();
    int kids[4] = { current.i+1, \
                    current.i-1, \
                    current.i-_size, \
                    current.i+_size };
    for(int i = 0; i < 4; i++){
        if ((current.i % _size == 0 && i == 1) || (current.i % _size == _size-1 && i == 0));
        else if (kids[i] >= 0 && kids[i] < (_size*_size)) {
            if (src.getParent() != NULL && src.getParent()->getEmptyPiece().i == kids[i]);
            else{
                Node *tmp = new Node(src.getSize());
                tmp->getChild(src, kids[i]);
                auto it = _closedlist.find(tmp->getHash());
                if (it == _closedlist.end()){
                    tmp->setParent(src);
                    calculateManhattan(*tmp);
                    _openlist.push(tmp);
                    _closedlist.insert(std::make_pair(tmp->getHash(), tmp->getG()));
                }
                else if (it->second > tmp->getG()){
                    // _closedlist.erase(tmp->getHash());
					_closedlist[tmp->getHash()] = tmp->getG();
                    tmp->setParent(src);
                    calculateManhattan(*tmp);
                    _openlist.push(tmp);
                    // _closedlist.insert(std::make_pair(tmp->getHash(), tmp->getG()));
                }
                else
                    delete tmp;
            } 
        }
    }
}

void        Puzzle::calculateMisplacedNodes(Node &n){
    int h = 0;
    std::vector<int> grid = n.getPuzzle();
    if (n.getParent() != NULL && n.getParent()->getH() != 0){
        h = n.getParent()->getH();
        xy old_cor = n.getParent()->getEmptyPiece();
        xy new_cor = n.getEmptyPiece();
        xy goal = _mapGoal.find(grid[old_cor.i])->second;
        if (goal.x == old_cor.x && goal.y == old_cor.y)
            h--;
        else if (goal.x == new_cor.x && goal.y == new_cor.y)
            h++;
        n.setH(h);
    }
    else{
        for (int i = 0; i < (_size*_size); i++){
            if (grid[i] != 0){
                xy goal = _mapGoal.find(grid[i])->second;
                if (goal.x != i % _size || goal.y != i / _size)
                    h++;
            }
        }
    }
    n.setH(h);
}

void        Puzzle::calculateManhattan(Node &n) {
    int h = 0;
    
    std::vector<int> grid = n.getPuzzle();
    if (n.getParent() != NULL && n.getParent()->getH() != 0){
        h = n.getParent()->getH();
        xy old_cor = n.getParent()->getEmptyPiece();
        xy new_cor = n.getEmptyPiece();
        xy goal = _mapGoal.find(grid[old_cor.i])->second;

        int newpos = abs(old_cor.x - goal.x) + abs(old_cor.y - goal.y);
        int oldpos = abs(new_cor.x - goal.x) + abs(new_cor.y - goal.y);
        h = h - oldpos + newpos;
        n.setH(h);
        return;
    }
    else{
        // std::vector<int> grid = n.getPuzzle();
        for (int i = 0; i < (_size*_size); i++) {
            if (grid[i] != 0){
                h += abs((i/_size) - _mapGoal.find(grid[i])->second.y) + abs((i%_size) - _mapGoal.find(grid[i])->second.x);
            }
        }
        n.setH(h);
    }
}

void    Puzzle::setGoal(){
    xy coordinates;
    coordinates.x = 0;
    coordinates.y = 0;
    coordinates.i = 0;
    int val = 1;
    int cnt = 0;

    while(val < (_size*_size)){
        for (;coordinates.x < (_size - cnt) && val < (_size*_size); coordinates.x++, val++, coordinates.i++){
            _mapGoal.insert(std::make_pair(val, coordinates));
        }
        for (coordinates.x--,coordinates.y++; coordinates.y < (_size - cnt) && val < (_size*_size); val++, coordinates.y++, coordinates.i++) {
            _mapGoal.insert(std::make_pair(val, coordinates));
        }
        for (coordinates.x--, coordinates.y--; coordinates.x >= 0 && val < (_size*_size) - cnt; val++, coordinates.x--, coordinates.i++) {
            _mapGoal.insert(std::make_pair(val, coordinates));
        }
        for (coordinates.y--, coordinates.x++; coordinates.y > 0 && val < (_size*_size) - cnt; val++, coordinates.y--, coordinates.i++) {
            _mapGoal.insert(std::make_pair(val, coordinates));
        }
        coordinates.y++;
        coordinates.x++;
        cnt++;
    }
}

std::unordered_map<uint64_t, int>&    Puzzle::getClosedList() {
    return _closedlist;
}

std::priority_queue<Node*, std::vector<Node*>, CompareF >&     Puzzle::getOpenList() {
    return _openlist;
}
