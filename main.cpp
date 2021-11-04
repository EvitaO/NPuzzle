// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"

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
    start->print();

    Puzzle  puzzle(4);

    puzzle.getOpenList().push(start);
    while (!(puzzle.getOpenList().empty()) && i < 2) {
        Node *tmp = puzzle.getOpenList().top();
        // std::cout << "new src = :\n";
        // tmp->print();
        if (tmp->getH() == 0 && tmp->getG() != 0){
            print(*tmp, 0);
            return 0;
        }
        // tmp->print();
        // std::cout << &tmp << std::endl;
        // std::cout << "aaa\n";
        // std::cout << &(puzzle.getOpenList().top()) << std::endl;
        // tmp->print();
        // std::cout <<  tmp->getH() << "   " << tmp->getG() << "    " << tmp->getF() << std::endl;
        // std::cout << puzzle.getOpenList().size() << std::endl;
        puzzle.getOpenList().pop();
        // std::cout << puzzle.getOpenList().size() << std::endl;
        // puzzle.getOpenList().top()->print();
        puzzle.getClosedList().insert(tmp);
        // std::cout << puzzle.getClosedList().size() << std::endl;
        puzzle.addToList(*tmp);
        // std::cout << ";lal  " << puzzle.getOpenList().size() << std::endl;
        // std::cout << ";lal2  " << puzzle.getClosedList().size() << std::endl;

        // i++;
    }
    // while (!(puzzle.getOpenList().empty())) {
    //     puzzle.getOpenList().top()->print();
    //     puzzle.getOpenList().pop();
    // }
}
