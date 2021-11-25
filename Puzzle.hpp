#ifndef PUZZLE_HPP_
#define PUZZLE_HPP_

#include "Node.hpp"
#include <unordered_map>
#include <deque>
#include <queue>
#include <memory>
#include <cmath>
#include <cstdlib>

struct        Options {
    int   heuristic;
    int   search;
};

struct        CompareF {
        bool    operator()(Node const *a, Node const *b) {
            if (a->getF() == b->getF() && a->getH() == b->getH())
                return a->getG() > b->getG();
            if (a->getF() == b->getF() && a->getG() == b->getG())
                return a->getH() > b->getH();
            if (a->getF() == b->getF())
                return a->getH() > b->getH();
            return (a->getF() > b->getF());
        }
};

class Puzzle {
    
    public:
        Puzzle(int s, Options input);
        ~Puzzle();

        void        setStart(Node &src);
        void        controlSolvabilty(Node &start);
        int         manhattanZero(xy coordinates_start);

        void        solve();

        void        addToList(Node &src);
        void        setupChild(Node &src, int newpos);

        void        setGoal();
        bool        isGoal(Node &n);

        void        calculateHeuristic(Node &n);
        void        calculateManhattan(Node &n);
        void        calculateMisplacedNodes(Node &n);
        void        calculateEuclidean(Node &n);

        std::unordered_map<uint64_t, int>&                              getClosedList();
        std::priority_queue<Node*, std::vector<Node*>, CompareF >&      getOpenList();
        std::deque<std::unique_ptr<Node> >                              getAllList();

        void        printSolution(Node &tmp, int *moves);

    private:

        Puzzle();

        int                                                             _size;
        Options                                                         _userinput;
        std::priority_queue<Node*, std::vector<Node*>, CompareF >       _openlist;
        std::unordered_map<uint64_t, int>                               _closedlist;
        std::deque<xy>                                                  _goal;
        std::deque<std::unique_ptr<Node> >                              _allNodes;
};

#endif