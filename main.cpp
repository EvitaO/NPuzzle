// Copyright 2021 <eovertoo>

#include "Grid.hpp"
#include <queue>
#include <vector>
#include <array>


int     main(void) {
    Grid    start(3);
    int ** arra = new int*[3];
    for (int i = 0; i < 3; i++)
        arra[i] = new int[3];

    int bla[3][3] = { {2, 4, 8}, {5, 7, 1}, {3, 6, 0} };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            arra[i][j] = bla[i][j];
    }

    start.setPuzzle(arra);

    int**   a = start.getPuzzle();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            std::cout << a[i][j] << " ";
        std::cout << std::endl;
    }

    xy cordinates = start.getEmptyPiece();
    std::cout << "cordinates zero piece, x = " << cordinates.x << " y = " << cordinates.y << std::endl << std::endl;

    int kids[4][2] = { {cordinates.x, cordinates.y + 1}, {cordinates.x, cordinates.y - 1}, {cordinates.x + 1, cordinates.y}, {cordinates.x - 1, cordinates.y} };

    std::priority_queue<Grid, std::vector<Grid>, CompareF >  openlist;

    for(int i = 0; i < 4; i++){
        if (start.getChild(cordinates.x, cordinates.y, kids[i][0], kids[i][1]) != NULL) {
            Grid tmp(3);
            tmp.setPuzzle(start.getChild(cordinates.x, cordinates.y, kids[i][0], kids[i][1]));
            openlist.push(tmp);
        }
    }

    while (!openlist.empty()) {
        Grid tmp = openlist.top();
        for (int i = 0; i < 3 ; i++) {
            for (int j = 0; j < 3; j++)
                std::cout << tmp.getPuzzle()[i][j] << " ";
            std::cout << std::endl;
        }
        openlist.pop();
        std::cout << std::endl;
    }
}
