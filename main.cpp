// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"

std::vector<std::vector<int> >   createPuzzle() {
    std::vector<std::vector<int> > board(3, std::vector<int>(3, 0));

    int bla[3][3] = { {2, 0, 3}, {1, 6, 4}, {8, 7, 5} };

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

int     main(void) {

    Node    start(3);
    
    start.setPuzzle(createPuzzle());
    start.print();

    Puzzle  puzzle(3);

    puzzle.getOpenList().push(start);
    while (!(puzzle.getOpenList().empty())) {
        Node tmp = puzzle.getOpenList().top();
        //tmp.print();
        puzzle.getOpenList().pop();
        if (puzzle.getClosedList().find(tmp) == puzzle.getClosedList().end()){
            if (puzzle.addToList(tmp))
                break;
        }
        puzzle.getClosedList().insert(tmp);
        
    }
}
