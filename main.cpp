//  Copyright 2021 <eovertoo>

#include "utils.hpp"

void    aStarAlgo(Node *start, Options input){
    Puzzle  puzzle(start->getSize(), input);
    try{
        puzzle.setStart(*start);
        puzzle.solve();
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
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
    // if (controlSolvabilty(&(*start)))
        aStarAlgo(&(*start), chooseInput());
    // else
    //     std::cout << "Puzzle is unsolvable\n";
    }
    // while(1);
    return 0;
}
