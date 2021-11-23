//  Copyright 2021 <eovertoo>

#include "utils.hpp"

void    print(Node &tmp, int *moves){
    if (tmp.getParent() != NULL){
        (*moves)++;
        print(*(tmp.getParent()), moves);
    }
    tmp.print();
    std::cout << "---------------------\n";
}

void    aStarAlgo(Node *start, Options input){
    Puzzle  puzzle(start->getSize(), input);
    int i = 0;
    int moves = 0;

    puzzle.calculateHeuristic(*start);
    puzzle.getOpenList().push(start);
    puzzle.getClosedList().insert(std::make_pair(start->getHash(), 0));
    while (!(puzzle.getOpenList().empty())) {
        i++;
        Node *tmp = (puzzle.getOpenList().top());
        if (puzzle.isGoal(*tmp)){
            print(*tmp, &moves);
            std::cout << "Number of moves: " << moves << std::endl;
            std::cout << "Time complexity: " << i << std::endl;
            std::cout << "Size complexity: " << puzzle.getAllList().size() << std::endl;
            std::cout << puzzle.getOpenList().size() << std::endl;
            std::cout << puzzle.getClosedList().size() << std::endl;
            break;
        }     
        puzzle.getOpenList().pop();
        puzzle.addToList(*tmp);
    }
}

bool    isValid(Node *start){
    std::vector<int>    goal;
    for (int i = 1; i < start->getSize() * start->getSize(); i++)
        goal.push_back(i);
    std::vector<int>    init;
    int cnt = 0;
    int size = start->getSize();
    std::vector<int>    puzzle = start->getPuzzle();
    xy  coordinates;
    coordinates.x = 0;
    coordinates.y = 0;

    while(init.size() < (size*size) - 1){
        for (;coordinates.x < (size - cnt); coordinates.x++){
            if (puzzle[coordinates.x+(coordinates.y*size)] != 0)
                init.push_back(puzzle[coordinates.x+(coordinates.y*size)]);
        }
        for (coordinates.x--,coordinates.y++; coordinates.y < (size - cnt); coordinates.y++) {
            if (puzzle[coordinates.x+(coordinates.y*size)] != 0)
                init.push_back(puzzle[coordinates.x+(coordinates.y*size)]);
        }
        for (coordinates.x--, coordinates.y--; coordinates.x >= (0 + cnt); coordinates.x--) {
            if (puzzle[coordinates.x+(coordinates.y*size)] != 0)
                init.push_back(puzzle[coordinates.x+(coordinates.y*size)]);
        }
        for (coordinates.y--, coordinates.x++; coordinates.y > (0 + cnt); coordinates.y--) {
            if (puzzle[coordinates.x+(coordinates.y*size)] != 0)
                init.push_back(puzzle[coordinates.x+(coordinates.y*size)]);
        }
        coordinates.y++;
        coordinates.x++;
        cnt++;
    }
    int inversions = 0;
    for (int i = 0; i < size*size; i++){
        int tmp = 0;
        for (int x = i; x < init.size(); x++){
            if (init[i] > init[x])
                tmp++;
            if (tmp == init[i] - 1)
                break;
        }
        inversions += tmp;
    }
    if (size % 2 != 0 && inversions % 2 != 0)
        return false;
    else if (size % 2 == 0) {
        if (size - start->getEmptyPiece().y % 2 == 0 && inversions % 2 == 0)
            return false;
        if (size - start->getEmptyPiece().y % 2 != 0 && inversions % 2 != 0)
            return false;
    }
    return true;
}
               
int     main(int argc, char **argv){
    std::unique_ptr<Node> start; 
    {
    if (argc > 2){
        std::cout << "Invalid input\n";
        return 0;
    }
    if (argc != 2){
        try{
            start = createPuzzle();
        }
        catch(std::exception &e){
            std::cout << "Invalid size\n";
            return 0;
        }
    }
    else {
        try{
            start = readfile(argv[1]);
        }
        catch(std::exception &e){
            std::cout << "Invald input format\n";
            return 0;
        }
    }
    if (isValid(&(*start)))
        aStarAlgo(&(*start), chooseInput());
    else
        std::cout << "Puzzle is unsolvable\n";
    }
    // while(1);
    return 0;
}
