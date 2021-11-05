// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"
#include <iterator>
#include <mutex>

std::mutex bla;

Puzzle::Puzzle() {}

Puzzle::Puzzle(int s) {
    _size = s;
    _goalState.resize(_size, std::vector<int>(_size, 0));
    setGoal();
}

Puzzle::Puzzle(Puzzle const & src) {*this = src;}

Puzzle::~Puzzle() {}

Puzzle &    Puzzle::operator=(Puzzle const & src) {
    _size = src._size;
    _openlist = src._openlist;
    _closedlist = src._closedlist;
    _goalState = src._goalState;
    return *this;
}

void        Puzzle::addToList(Node &src, int newx, int newy) {
    std::set<Node*>::iterator pos;

    // for(int i = 0; i < 4; i++){
        // if (kids[i][0] >= 0 && kids[i][0] < _size && kids[i][1] >= 0 && kids[i][1] < _size) {
        if (newx >= 0 && newx < _size && newy >= 0 && newy < _size){
            if (src.getParent() != NULL && src.getParent()->getEmptyPiece().x == newx && src.getParent()->getEmptyPiece().y == newy);
            else{
                Node *tmp = new Node(src.getSize());
                tmp->getChild(src, newx, newy);
                bla.lock();
                pos = _closedlist.find(tmp);
                bla.unlock();

            //mayb makes it better or worser, not sure yet
                if (pos != _closedlist.end()) 
                {
                    if ((*pos)->getF() <= tmp->getF());
                    else {
                        bla.lock();
                        _closedlist.erase(pos);
                        bla.unlock();
                        calculateManhattan(*tmp);
                        tmp->setParent(src);
                        bla.lock();
                        _openlist.push(tmp);
                        _closedlist.insert(tmp);
                        bla.unlock();
                    }
                }
                else{
            // if (pos == _closedlist.end()){
                    calculateManhattan(*tmp);
                    tmp->setParent(src);
                    bla.lock();
                    _openlist.push(tmp);
                    _closedlist.insert(tmp);
                    bla.unlock();
                }
            } 
        }
    // }
}



void        Puzzle::test(Node *src) {
    // int kids[4][2] = { {src->getEmptyPiece().x, src->getEmptyPiece().y + 1}, {src->getEmptyPiece().x, src->getEmptyPiece().y - 1}, {src->getEmptyPiece().x + 1, src->getEmptyPiece().y}, {src->getEmptyPiece().x - 1, src->getEmptyPiece().y} }; 
    int x1 = src->getEmptyPiece().x;
    int y1 = src->getEmptyPiece().y + 1;
    int x2 = src->getEmptyPiece().x;
    int y2 = src->getEmptyPiece().y - 1;
    int x3 = src->getEmptyPiece().x + 1;
    int y3 = src->getEmptyPiece().y;
    int x4 = src->getEmptyPiece().x - 1;
    int y4 = src->getEmptyPiece().y;

    std::thread         t1([this, src, x1, y1]() {addToList(const_cast<Node &>(*src), x1, y1); });
    std::thread         t2([this, src, x2, y2]() {addToList(const_cast<Node &>(*src), x2, y2); });
    std::thread         t3([this, src, x3, y3]() {addToList(const_cast<Node &>(*src), x3, y3); });
    std::thread         t4([this, src, x4, y4]() {addToList(const_cast<Node &>(*src), x4, y4); });
    // std::thread     t1(&Puzzle::addToList, this, src, kids[0][0], kids[0][1]);
    // std::thread     t2(&Puzzle::addToList, this, src, kids[1][0], kids[1][1]);
    // std::thread     t3(&Puzzle::addToList, this, src, kids[2][0], kids[2][1]);
    // std::thread     t4(&Puzzle::addToList, this, src, kids[3][0], kids[3][1]);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}



void        Puzzle::calculateManhattan(Node &n) {
    int h = 0;
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            if (n.getPuzzle()[i][j] == 0);
            else{
                h += abs(i - _mapGoal.find(n.getPuzzle()[i][j])->second.first) + abs(j - _mapGoal.find(n.getPuzzle()[i][j])->second.second);
            }
        }
    }
    n.setH(h);
}



std::vector<std::vector<int> >  Puzzle::getGoal() const {return _goalState;}

void    Puzzle::setGoal(){
    int i = 0;
    int j = 0;
    int val = 1;
    while (val < (_size * _size)) {
        for (;j < _size && _goalState[i][j] == 0 && val < (_size * _size); j++, val++){
            _goalState[i][j] = val;
            std::pair<int, int> xy = std::make_pair(i, j);
            _mapGoal.insert(std::make_pair(val, xy));
        }
        for (j--,i++; i < _size && _goalState[i][j] == 0 && val < (_size * _size); val++, i++) {
            _goalState[i][j] = val;
            std::pair<int, int> xy = std::make_pair(i, j);
            _mapGoal.insert(std::make_pair(val, xy));
        }
        for (j--, i--; j >= 0 && _goalState[i][j] == 0 && val < (_size * _size); val++, j--) {
            _goalState[i][j] = val;
            std::pair<int, int> xy = std::make_pair(i, j);
            _mapGoal.insert(std::make_pair(val, xy));
        }
        for (i--, j++; i >= 0 && _goalState[i][j] == 0 && val < (_size * _size); val++, i--) {
            _goalState[i][j] = val;
            std::pair<int, int> xy = std::make_pair(i, j);
            _mapGoal.insert(std::make_pair(val, xy));
        }
        i++;
        j++;
    }
}

std::set<Node*, ComparePuzzle>&    Puzzle::getClosedList() {
    return _closedlist;
}

std::priority_queue<Node*, std::vector<Node*>, CompareF >&     Puzzle::getOpenList() {
    return _openlist;
}
