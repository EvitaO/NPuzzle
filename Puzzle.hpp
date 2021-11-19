#ifndef PUZZLE_HPP_
#define PUZZLE_HPP_

// Copyright 2021 <eovertoo>

#include "Node.hpp"
#include <unordered_map>
#include <deque>
#include <queue>
#include <memory>

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
        void        setupChild(Node &src, int newpos);
        void        setGoal();
        void        calculateManhattan(Node &n);
        void        calculateMisplacedNodes(Node &n);

        std::unordered_map<uint64_t, int>&                              getClosedList();
        std::priority_queue<Node*, std::vector<Node*>, CompareF >&      getOpenList();
        std::deque<std::unique_ptr<Node> >                              getAllList();


    private:

        Puzzle();

        int _size;
        std::priority_queue<Node*, std::vector<Node*>, CompareF >       _openlist;
        std::unordered_map<uint64_t, int>                               _closedlist;
        std::deque<xy>                                                  _mapGoal;
        std::deque<std::unique_ptr<Node> >                              _allNodes;
};

#endif