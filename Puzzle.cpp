// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"
#include <iterator>

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

bool        Puzzle::addToList(Node &src) {
    xy coordinates = src.getEmptyPiece();
    int kids[4][2] = { {coordinates.x, coordinates.y + 1}, {coordinates.x, coordinates.y - 1}, {coordinates.x + 1, coordinates.y}, {coordinates.x - 1, coordinates.y} }; 
    std::set<Node*>::iterator bla;

    for(int i = 0; i < 4; i++){
        
        // if (src.getParent() != NULL && kids[i][0] != src.getParent()->getEmptyPiece().x && kids[i][1] != src.getParent()->getEmptyPiece().y);
        if (kids[i][0] >= 0 && kids[i][0] < _size && kids[i][1] >= 0 && kids[i][1] < _size) {
            if (src.getParent() != NULL && src.getParent()->getPuzzle() == src.getChild(coordinates.x, coordinates.y, kids[i][0], kids[i][1]));
                // std::cout << "aa\n";
            // std::cout << &src << std::endl;
            else{
            Node *tmp = new Node(src.getSize());
            tmp->setPuzzle(src.getChild(coordinates.x, coordinates.y, kids[i][0], kids[i][1]));
            bla = _closedlist.find(tmp);

            //mayb makes it better or worser, not sure yet
            // std::cout << &tmp << std::endl;
            // std::cout << &src << std::endl;
            if (bla != _closedlist.end()) 
            {
                if ((*bla)->getF() <= tmp->getF());
                else {
                    _closedlist.erase(bla);
                    calculateManhattan(*tmp);
                    tmp->setParent(src);
                    _openlist.push(tmp);
                    _closedlist.insert(tmp);
                }
            }
            else{
            // if (bla == _closedlist.end()){
                calculateManhattan(*tmp);
                tmp->setParent(src);
                _openlist.push(tmp);
                _closedlist.insert(tmp);
            }
            } 
        }
    }
    return false;
}

void        Puzzle::calculateManhattan(Node &n) {
    int h = 0;
    int f = 0;
    for (int i = 0; i < _size; i++) {
        f = 0;
        for (int j = 0; j < _size; j++) {
            f = 0;
            for(int k = 0; k < _size && f == 0; k++){
                for (int l = 0; l < _size; l++){
                    if (n.getPuzzle()[i][j] == _goalState[k][l] && n.getPuzzle()[i][j] != 0){
                        h += (i >= k) ? (i - k) : (k - i);
                        h += (j >= l) ? (j - l) : (l - j);
                        f = 1;
                        break;
                    }
                }
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
        for (;j < _size && _goalState[i][j] == 0 && val < (_size * _size); j++, val++)
            _goalState[i][j] = val;
        for (j--,i++; i < _size && _goalState[i][j] == 0 && val < (_size * _size); val++, i++)
            _goalState[i][j] = val;
        for (j--, i--; j >= 0 && _goalState[i][j] == 0 && val < (_size * _size); val++, j--)
            _goalState[i][j] = val;
        for (i--, j++; i >= 0 && _goalState[i][j] == 0 && val < (_size * _size); val++, i--)
            _goalState[i][j] = val;
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
