#ifndef PUZZLE_HPP_
#define PUZZLE_HPP_

// Copyright 2021 <eovertoo>

#include "Node.hpp"
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <map>
#include <cstdlib>
#include <functional>
#include <cmath>
#include <vector>

struct        CompareF {
        bool    operator()(Node const *a, Node const *b) {
            if (a->getF() == b->getF())
                return a->getH() > b->getH();
            return (a->getF() > b->getF());
        }
};

class Puzzle {
    
    public:
        Puzzle(int size);
        Puzzle(Puzzle const & src);
        ~Puzzle();

        Puzzle &    operator=(Puzzle const & src);


        void        addToList(Node &src);
        void        setGoal();
        void        calculateManhattan(Node &n);
        std::unordered_map<int, int>&    getClosedList();
        std::priority_queue<Node*, std::vector<Node*>, CompareF >&     getOpenList();


    private:

        Puzzle();

        int _size;
        std::priority_queue<Node*, std::vector<Node*>, CompareF >  _openlist;
        std::unordered_map<int, int>  _closedlist;
        std::unordered_map<int, xy> _mapGoal;
};



#endif

// 1 2 3 4 x
// 12      5
// 11      6
// 10  9 8   7
//       x