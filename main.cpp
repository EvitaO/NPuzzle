// Copyright 2021 <eovertoo>

#include "Puzzle.hpp"

int**   createPuzzle() {
    int ** arra = new int*[3];
    for (int i = 0; i < 3; i++)
        arra[i] = new int[3];

    int bla[3][3] = { {2, 4, 8}, {5, 7, 1}, {3, 6, 0} };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            arra[i][j] = bla[i][j];
    }
    return arra;
}

bool    isgoal(Node current) {
    int size = 3;
    int goal[3][3] = {0};
    int i = 0;
    int j = 0;
    int val = 1;
    while (val < (size * size)) {
        for (;j < size && goal[i][j] == 0 && val < (size * size); j++, val++)
            goal[i][j] = val;
        for (j--,i++; i < size && goal[i][j] == 0 && val < (size * size); val++, i++)
            goal[i][j] = val;
        for (j--, i--; j >= 0 && goal[i][j] == 0 && val < (size * size); val++, j--)
            goal[i][j] = val;
        for (i--, j++; i >= 0 && goal[i][j] == 0 && val < (size * size); val++, i--)
            goal[i][j] = val;
        i++;
        j++;
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << goal[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return true;
}

int     main(void) {
    Node    start(3);
    
    start.setPuzzle(createPuzzle());

    isgoal(start);
   
    Puzzle  puzzle(3);

    xy cordinates = start.getEmptyPiece();
    std::cout << "cordinates zero piece, x = " << cordinates.x << " y = " << cordinates.y << std::endl << std::endl;

    int kids[4][2] = { {cordinates.x, cordinates.y + 1}, {cordinates.x, cordinates.y - 1}, {cordinates.x + 1, cordinates.y}, {cordinates.x - 1, cordinates.y} };

    for(int i = 0; i < 4; i++){
        if (start.getChild(cordinates.x, cordinates.y, kids[i][0], kids[i][1]) != NULL) {
            Node tmp(3);
            tmp.setPuzzle(start.getChild(cordinates.x, cordinates.y, kids[i][0], kids[i][1]));
            puzzle.getOpenList().push(tmp);            
        }
    }

    while (!(puzzle.getOpenList().empty())) {
        Node tmp = puzzle.getOpenList().top();
        tmp.print();
        puzzle.getClosedList().insert(tmp);
        puzzle.getOpenList().pop();
    }

    std::cout << puzzle.getClosedList().size() << std::endl;
}
