// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"
#include <iterator>


Puzzle::Puzzle() {}

Puzzle::Puzzle(int s, Options input) {
    _size = s;
    _mapGoal.resize(s*s);
    _userinput = input;
    setGoal();
}

Puzzle::Puzzle(Puzzle const & src) {*this = src;}

Puzzle::~Puzzle() {
}

Puzzle &    Puzzle::operator=(Puzzle const & src) {
    _size = src._size;
    _openlist = src._openlist;
    _closedlist = src._closedlist;
    return *this;
}


void        Puzzle::setupChild(Node &src, int newpos){
    if (src.getParent() != NULL && src.getParent()->getEmptyPiece().i == newpos);
    else{
        std::unique_ptr<Node> tmp = std::make_unique<Node>(Node(src.getSize()));
        tmp->swapGrid(src, newpos);
        tmp->setParent(src, _userinput.search);
        auto it = _closedlist.find(tmp->getHash());
        if (it == _closedlist.end()){
            calculateHeuristic(*tmp);
            _openlist.push(&(*tmp));
            _closedlist.insert(std::make_pair(tmp->getHash(), tmp->getG()));
            _allNodes.push_back(std::move(tmp));
        }
        else if (it->second > tmp->getG()){
		    _closedlist[tmp->getHash()] = tmp->getG();
            calculateHeuristic(*tmp);
            _openlist.push(&(*tmp));
            _allNodes.push_back(std::move(tmp));
        }
    }
}

void        Puzzle::addToList(Node &src) {
    xy  current = src.getEmptyPiece();
    //MOVE RIGHT
    if (current.i % _size != _size-1){
        if (current.i+1 >= 0 && current.i+1 < (_size*_size))
            setupChild(src, current.i+1);
    }
    //MOVE LEFT      
    if (current.i % _size != 0){
        if (current.i-1 >= 0 && current.i-1 < (_size*_size))
            setupChild(src, current.i-1);
    }
    //MOVE UP
    if (current.i-_size >= 0 && current.i-_size < (_size*_size))
        setupChild(src, current.i-_size);
    //MOVE DOWN
    if (current.i+_size >= 0 && (current.i+_size) < (_size*_size))
        setupChild(src, current.i+_size);
}

void        Puzzle::calculateHeuristic(Node &n){
    if (_userinput.search == 0 || _userinput.search == 1){
        if (_userinput.heuristic == 0)
            calculateManhattan(n);
        if (_userinput.heuristic == 1)
            calculateEuclidean(n);
        if (_userinput.heuristic == 2)
            calculateMisplacedNodes(n);
    }
    else
        n.setH(0);
}

void        Puzzle::calculateMisplacedNodes(Node &n){
    int h = 0;
    std::vector<int> grid = n.getPuzzle();
    if (n.getParent() != NULL && n.getParent()->getH() != 0){
        h = n.getParent()->getH();
        xy old_cor = n.getParent()->getEmptyPiece();
        xy new_cor = n.getEmptyPiece();
        xy goal = _mapGoal[grid[old_cor.i]];
        if (goal.x == old_cor.x && goal.y == old_cor.y)
            h--;
        else if (goal.x == new_cor.x && goal.y == new_cor.y)
            h++;
        n.setH(h);
    }
    else{
        for (int i = 0; i < (_size*_size); i++){
            if (grid[i] != 0){
                xy goal = _mapGoal[grid[i]];
                if (goal.x != i % _size || goal.y != i / _size)
                    h++;
            }
        }
        n.setH(h);
    }
}

void        Puzzle::calculateEuclidean(Node &n){
    float h = 0;
    std::vector<int> grid = n.getPuzzle();
    for(int i = 0; i < (_size*_size); i++){
        if (grid[i] != 0){
            int y = pow(abs((i/_size) - _mapGoal[grid[i]].y), 2);
            int x = pow(abs((i%_size) - _mapGoal[grid[i]].x), 2);
            h += sqrt((y+x));
        }
    }
    n.setH(h);
}

void        Puzzle::calculateManhattan(Node &n){
    int h = 0;
    
    std::vector<int> grid = n.getPuzzle();
    if (n.getParent() != NULL && n.getParent()->getH() != 0){
        h = n.getParent()->getH();
        xy new_cor = n.getParent()->getEmptyPiece();
        xy old_cor = n.getEmptyPiece();
        xy goal = _mapGoal[grid[new_cor.i]];

        int newpos = abs(new_cor.x - goal.x) + abs(new_cor.y - goal.y);
        int oldpos = abs(old_cor.x - goal.x) + abs(old_cor.y - goal.y);
        h = h - oldpos + newpos;
        n.setH(h);
        return;
    }
    else{
        for (int i = 0; i < (_size*_size); i++){
            if (grid[i] != 0){
                h += abs((i/_size) - _mapGoal[grid[i]].y) + abs((i%_size) - _mapGoal[grid[i]].x);
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
            _mapGoal[val] = coordinates;
        }
        for (coordinates.x--,coordinates.y++; coordinates.y < (_size - cnt) && val < (_size*_size); val++, coordinates.y++, coordinates.i++) {
            _mapGoal[val] = coordinates;
        }
        for (coordinates.x--, coordinates.y--; coordinates.x >= (0 + cnt) && val < (_size*_size); val++, coordinates.x--, coordinates.i++) {
            _mapGoal[val] = coordinates;
        }
        for (coordinates.y--, coordinates.x++; coordinates.y > (0 + cnt) && val < (_size*_size); val++, coordinates.y--, coordinates.i++) {
            _mapGoal[val] = coordinates;
        }
        coordinates.y++;
        coordinates.x++;
        cnt++;
    }
}

bool                                Puzzle::isGoal(Node &n){
    if (_userinput.search == 0 && n.getH() == 0)
        return true;
    if (_userinput.search == 1 && n.getH() == 0)
        return true;
    if (_userinput.search == 2){
        std::vector<int> grid = n.getPuzzle();
        for (int i = 0; i < (_size*_size); i++){
            if (grid[i] != 0){
                xy goal = _mapGoal[grid[i]];
                if (goal.x != i % _size || goal.y != i / _size)
                    return false;
            }
        }
        return true;
    }
    return false;
}

std::unordered_map<uint64_t, int>&    Puzzle::getClosedList() {
    return _closedlist;
}

std::priority_queue<Node*, std::vector<Node*>, CompareF >&     Puzzle::getOpenList() {
    return _openlist;
}

std::deque<std::unique_ptr<Node> >     Puzzle::getAllList(){
    return std::move(_allNodes);
}
