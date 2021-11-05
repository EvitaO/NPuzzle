#ifndef PUZZLE_HPP_
#define PUZZLE_HPP_

// Copyright 2021 <eovertoo>

#include "Node.hpp"
#include <set>
#include <queue>
#include <unordered_map>
#include <map>
#include <cstdlib>


struct        CompareF {
        bool    operator()(Node const *a, Node const *b) {
            // if (a.getPuzzle() == b.getPuzzle() && a.getF() >= b.getF())
            //     return true;
            // if (a->getF() == b->getF())
            //     return a->getH() > b->getH();
            return a->getF() > b->getF();
        }
};

struct        ComparePuzzle {
       bool    operator()(Node const *a, Node const *b) {return a->getPuzzle() != b->getPuzzle();}
};

class Puzzle {
    public:
        Puzzle(int size);
        Puzzle(Puzzle const & src);
        ~Puzzle();

        Puzzle &    operator=(Puzzle const & src);

        std::vector<std::vector<int> >  getGoal() const;

        void        addToList(Node &src);
        void        setGoal();
        void        calculateManhattan(Node &n);
        void        test(Node *src);
        std::set<Node*, ComparePuzzle>&    getClosedList();
        std::priority_queue<Node*, std::vector<Node*>, CompareF >&     getOpenList();


    private:

        Puzzle();

        int _size;
        std::priority_queue<Node*, std::vector<Node*>, CompareF >  _openlist;
        std::set<Node*, ComparePuzzle>  _closedlist;
        std::vector<std::vector<int> > _goalState;
        std::unordered_map<int, std::pair<int, int> > _mapGoal;
};



#endif