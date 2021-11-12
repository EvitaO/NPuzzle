//  Copyright 2021 <eovertoo>

#include "Puzzle.hpp"
#include <thread>
#include <deque>

std::vector<int>&   createPuzzle(std::vector<int> &board) {
    // std::vector<int> board(9, 0);

    // int bla[16] = { 6, 5, 11, 8, 15, 10, 2, 14, 4, 0, 1, 3, 13, 7, 9, 12 };
    // int bla[4][4] = { {15, 0, 1, 6}, {12, 3, 10, 9}, {11, 7, 14, 13}, {5, 4, 2, 8} };
    // int bla[25] = { 6, 1, 3, 17, 19, 8, 11, 23, 0, 24, 12, 10, 2, 5, 9, 20, 13, 15, 18, 22, 4, 7, 16, 14, 21 };
    int bla[25] = { 17, 9, 24, 12, 15, 14, 10, 4, 0, 11, 7, 6, 1, 8, 22, 3, 18, 19, 23, 16, 20, 13, 5, 2, 21 };
    // int bla[3][3] = { {1, 2, 3}, {0, 6, 4}, {8, 7, 5} };
    // int bla[9] = { 8, 7, 3, 6, 1, 5, 0, 2, 4 };
    // int bla[16] = { 13, 12, 14, 4, 9, 8, 0, 3, 15, 10, 2, 5, 6, 1, 11, 7 };
    // int bla[16] = { 15, 6, 13, 4, 10, 11, 14, 1, 7, 2, 9, 0, 12, 8, 5, 3 };


    for (int i = 0; i < 25; i++) {
        // for (int j = 0; j < 3; j++)
            board[i] = bla[i];
    }
    return board;
}

void    print(Node &tmp, int moves){
    if (tmp.getParent() != NULL)
        print(*(tmp.getParent()), moves+1);
    tmp.print();
    std::cout << "---------------------\n";
}

int     main(void) {

    Node    start(25);
    std::vector<int> board(25, 0);
    int i = 0;
    start.setPuzzle(createPuzzle(board));
    // start.setHash(start.getPuzzle());
    // std::cout << "aaaa  " << start.getHash() << std::endl;
    Puzzle  puzzle(25);
    std::deque<Node*> bla;

    puzzle.getOpenList().push(&start);
    puzzle.getClosedList().insert(std::make_pair(start.getHash(), 0));
    while (!(puzzle.getOpenList().empty()) && i < 5) {
        Node *tmp = (puzzle.getOpenList().top());
        // if (i >= 0){
        //     std::cout << "cur\n";
        //     tmp->print();
        //     std::cout << tmp->getH() << std::endl;
        // }
        if (tmp->getH() == 0 && tmp->getG() != 0){
            print(*tmp, 0);
            std::cout << puzzle.getOpenList().size() << std::endl;
            std::cout << puzzle.getClosedList().size() << std::endl;
            std::cout << i << std::endl;
            break;
        }
        puzzle.getOpenList().pop();
        puzzle.addToList(*tmp);
        bla.push_back(tmp);
        // i++;
    }
    bla.erase(bla.begin(), bla.end());
    std::cout << "aaa\n";
    // while(1);
}

