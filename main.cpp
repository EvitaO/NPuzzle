// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"
#include <thread>

// void    print(Node &tmp);

std::vector<int>   createPuzzle() {
    std::vector<int> board(9, 0);

    // int bla[16] = { 6, 5, 11, 8, 15, 10, 2, 14, 4, 0, 1, 3, 13, 7, 9, 12 };
    // int bla[4][4] = { {15, 0, 1, 6}, {12, 3, 10, 9}, {11, 7, 14, 13}, {5, 4, 2, 8} };
    // int bla[5][5] = { {6, 1, 3, 17, 19}, {8, 11, 23, 0, 24}, {12, 10, 2, 5, 9}, {20, 13, 15, 18, 22}, {4, 7, 16, 14, 21} };
    // int bla[3][3] = { {1, 2, 3}, {0, 6, 4}, {8, 7, 5} };
    int bla[9] = { 8, 7, 3, 6, 1, 5, 0, 2, 4 };
    // int bla[16] = { 13, 12, 14, 4, 9, 8, 0, 3, 15, 10, 2, 5, 6, 1, 11, 7 };

    for (int i = 0; i < 9; i++) {
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

    Node    *start = new Node(9);
    int i = 0;
    start->setPuzzle(createPuzzle());
    Puzzle  puzzle(9);

    puzzle.getOpenList().push(start);
    puzzle.getClosedList().insert(start->getPuzzle());
    // start->print();
    std::cout << "\n\n";
    while (!(puzzle.getOpenList().empty()) && i < 705) {
        Node *tmp = puzzle.getOpenList().top();
        if (i > 7500){
            tmp->print();
            std::cout << "\nF:  " << tmp->getF() << "\n" ;
            std::cout << "\nG:  " << tmp->getG() << "\n" ;
            std::cout << "\nH:  " << tmp->getH() << "\n" ;
            std::cout << puzzle.getClosedList().size() << std::endl;
            std::cout << puzzle.getOpenList().size() << std::endl;
        }
        if (tmp->getH() == 0 && tmp->getG() != 0){
            print(*tmp, 0);
            std::cout << puzzle.getOpenList().size() << std::endl;
            std::cout << puzzle.getClosedList().size() << std::endl;
            std::cout << i << std::endl;
            break;
        }
        puzzle.getOpenList().pop();
        puzzle.addToList(*tmp);
        // std::cout << "aaa\n";
        // delete tmp;
        // std::cout << "bbb\n";
        // i++;
        // while (i == 700);
    }
//     std::cout << "aaa\n";
//     while(1);
}
