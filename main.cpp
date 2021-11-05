// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"
#include <thread>

// void    print(Node &tmp);

std::vector<std::vector<int> >   createPuzzle() {
    std::vector<std::vector<int> > board(4, std::vector<int>(4, 0));

    int bla[4][4] = { {15, 0, 1, 6}, {12, 3, 10, 9}, {11, 7, 14, 13}, {5, 4, 2, 8} };
    // int bla[5][5] = { {6, 1, 3, 17, 19}, {8, 11, 23, 0, 24}, {12, 10, 2, 5, 9}, {20, 13, 15, 18, 22}, {4, 7, 16, 14, 21} };
    // int bla[3][3] = { {1, 2, 3}, {0, 6, 4}, {8, 7, 5} };
    // int bla[3][3] = { {8, 7, 3}, {6, 1, 5}, {0, 2, 4} };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            board[i][j] = bla[i][j];
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

    Node    *start = new Node(4);
    int i = 0;
    start->setPuzzle(createPuzzle());
    Puzzle  puzzle(4);

    puzzle.getOpenList().push(start);
    while (!(puzzle.getOpenList().empty()) && i < 5) {
        Node *tmp = puzzle.getOpenList().top();
        if (tmp->getH() == 0 && tmp->getG() != 0){
            print(*tmp, 0);
            return 0;
        }
        puzzle.getOpenList().pop();
        puzzle.getClosedList().insert(tmp);
        puzzle.test(tmp);
        // i++;
    }
}
