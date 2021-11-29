#ifndef PUZZLE_HPP_
#define PUZZLE_HPP_

#include "Node.hpp"
#include <unordered_map>
#include <deque>
#include <queue>

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
        Puzzle(int s, char flag);
        ~Puzzle();

        void                setStart(Node &src);
        void                controlSolvability(Node &start);
        int                 manhattanZero(xy coordinates_start);
        std::vector<int>    convertPuzzle(std::vector<int> puzzle, std::vector<int> rowgoal);



        void        solve();

        void        addToList(Node &src);
        void        setupChild(Node &src, int newpos, char direc);

        void        setGoal();
        bool        isGoal(Node &n);

        void        calculateHeuristic(Node &n);
        void        calculateManhattan(Node &n);
        void        calculateHamming(Node &n);
        void        calculateEuclidean(Node &n);

        std::unordered_map<uint64_t, int>&                              getClosedList();
        std::priority_queue<Node*, std::vector<Node*>, CompareF >&      getOpenList();
        std::deque<std::unique_ptr<Node> >                              getAllList();

        void        printSolution(Node &tmp, int *moves);

    private:

        Puzzle();

        int                                                             _size;
        char                                                            _flags;
        std::priority_queue<Node*, std::vector<Node*>, CompareF >       _openlist;
        std::unordered_map<uint64_t, int>                               _closedlist;
        std::deque<xy>                                                  _goal;
        std::deque<std::unique_ptr<Node> >                              _allNodes;
};

#endif