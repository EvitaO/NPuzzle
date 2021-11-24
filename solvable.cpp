#include "utils.hpp"

std::vector<int>        puzzleSnakeForm(Node *start, int size){
    std::vector<int>    puzzle = start->getPuzzle();
    std::vector<int>    snake;
    xy  coordinates;
    coordinates.x = 0;
    coordinates.y = 0;
    int cnt = 0;

    while(snake.size() < (size*size) - 1){
        for (;coordinates.x < (size - cnt); coordinates.x++){
            if (puzzle[coordinates.x+(coordinates.y*size)] != 0)
                snake.push_back(puzzle[coordinates.x+(coordinates.y*size)]);
        }
        for (coordinates.x--,coordinates.y++; coordinates.y < (size - cnt); coordinates.y++) {
            if (puzzle[coordinates.x+(coordinates.y*size)] != 0)
                snake.push_back(puzzle[coordinates.x+(coordinates.y*size)]);
        }
        for (coordinates.x--, coordinates.y--; coordinates.x >= (0 + cnt); coordinates.x--) {
            if (puzzle[coordinates.x+(coordinates.y*size)] != 0)
                snake.push_back(puzzle[coordinates.x+(coordinates.y*size)]);
        }
        for (coordinates.y--, coordinates.x++; coordinates.y > (0 + cnt); coordinates.y--) {
            if (puzzle[coordinates.x+(coordinates.y*size)] != 0)
                snake.push_back(puzzle[coordinates.x+(coordinates.y*size)]);
        }
        coordinates.y++;
        coordinates.x++;
        cnt++;
    }
    return snake;
}

int     calculateInversions(std::vector<int> vec, int size){
    int inversions = 0;
    for (int i = 0; i < vec.size(); i++){
        int tmp = 0;
        for (int x = i + 1; x < vec.size(); x++){
            if (vec[i] > vec[x] && vec[x] != 0)
            // if ((vec[i] > vec[x] && vec[x] != 0) || (vec[i] == 0 && vec[x] != vec[i]))
                tmp++;
            if (tmp == vec[i] - 1 || vec[i] == 0)
                break;
        }
        inversions += tmp;
    }
    return inversions;
}

bool    isSolvable(int inversions, int size, Node *start){
    if (size % 2 != 0 && inversions % 2 != 0)
        return false;
    else if (size % 2 == 0) {
        if (size - start->getEmptyPiece().y % 2 == 0 && inversions % 2 == 0)
            return false;
        if ((size - start->getEmptyPiece().y) % 2 != 0 && inversions % 2 != 0)
            return false;
    }
    return true;
}

bool    controlSolvabilty(Node *start){
    int size = start->getSize();
    std::vector<int>    vec = puzzleSnakeForm(start, size);
    
    int inversions = calculateInversions(vec, size);
    std::cout << inversions << std::endl;
    return  isSolvable(inversions, size, start);
}