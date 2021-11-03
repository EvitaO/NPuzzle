// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"

std::vector<std::vector<int> >   createPuzzle() {
    std::vector<std::vector<int> > board(3, std::vector<int>(3, 0));

    // int bla[4][4] = { {15, 0, 1, 6}, {12, 3, 10, 9}, {11, 7, 14, 13}, {5, 4, 2, 8} };
    // int bla[5][5] = { {6, 1, 3, 17, 19}, {8, 11, 23, 0, 24}, {12, 10, 2, 5, 9}, {20, 13, 15, 18, 22}, {4, 7, 16, 14, 21} };
    // int bla[3][3] = { {1, 2, 3}, {0, 6, 4}, {8, 7, 5} };
    int bla[3][3] = { {8, 7, 3}, {6, 1, 5}, {0, 2, 4} };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            board[i][j] = bla[i][j];
    }
    return board;
}

/*
1 2 3
8 0 4
7 6 5

1 2 3
0 6 4
8 7 5

 */
// bool    isgoal(Node current) {
//     int size = 3;
//     std::vector<std::vector<int> > goal(3, std::vector<int>(3, 0));
//     int i = 0;
//     int j = 0;
//     int val = 1;
//     while (val < (size * size)) {
//         for (;j < size && goal[i][j] == 0 && val < (size * size); j++, val++)
//             goal[i][j] = val;
//         for (j--,i++; i < size && goal[i][j] == 0 && val < (size * size); val++, i++)
//             goal[i][j] = val;
//         for (j--, i--; j >= 0 && goal[i][j] == 0 && val < (size * size); val++, j--)
//             goal[i][j] = val;
//         for (i--, j++; i >= 0 && goal[i][j] == 0 && val < (size * size); val++, i--)
//             goal[i][j] = val;
//         i++;
//         j++;
//     }
//     if (current.getPuzzle() == goal)
//         return true;
//     return false;
// }

// void    print(Node *tmp){
//     // std::cout << &(*(tmp->getParent()->getParent())) << std::endl;
//     // std::cout << &(*(tmp->getParent())) << std::endl;
//     if (tmp->getParent() != NULL)
//         print(tmp->getParent());
//     tmp->getParent()->print();
// }

int     main(void) {

    Node    start(3);
    int i = 0;
    start.setPuzzle(createPuzzle());
    start.print();

    Puzzle  puzzle(3);

    puzzle.getOpenList().push(start);
    while (!(puzzle.getOpenList().empty()) && i < 10) {
        Node tmp = puzzle.getOpenList().top();
        if (tmp.getH() == 0 && tmp.getG() != 0){
            // print(&tmp);
            return 0;
        }
        // tmp.print();
        // std::cout <<  tmp.getH() << "   " << tmp.getG() << "    " << tmp.getF() << std::endl;
        puzzle.getOpenList().pop();
        puzzle.getClosedList().insert(tmp);
        // std::cout << puzzle.getClosedList().size() << std::endl;
        puzzle.addToList(tmp);
        // i++;
    }
    // while (1);
}
