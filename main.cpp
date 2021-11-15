//  Copyright 2021 <eovertoo>

#include "Puzzle.hpp"
#include <fstream>
#include <sstream>

std::vector<int>&   createPuzzle(std::vector<int> &board) {
    // int bla[25] = { 17, 9, 24, 12, 15, 14, 10, 4, 0, 11, 7, 6, 1, 8, 22, 3, 18, 19, 23, 16, 20, 13, 5, 2, 21 };
    // int bla[9] = { 8, 7, 3, 6, 1, 5, 0, 2, 4 };
    int bla[16] = { 2, 14, 10, 11, 0, 9, 4, 15, 5, 1, 13, 7, 3, 6, 12, 8 };

    for (int i = 0; i < 16; i++) {
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

bool     controlInput(std::vector<int> input, int size){
    if (input.size() != size*size)
        return false;
    std::vector<std::string> nums(size*size);
    for (int i = 0; i < size*size; i++){
        if (input[i] >= size*size)
            return false;
        else if (nums[input[i]] == "1")
            return false;
        else
            nums[input[i]] = "1";
    }
    if (nums.size() != size*size)
        return false;
    return true;
}

Node*    readfile(char *file){
    std::string line;
    std::ifstream f(file);
    int     size = 0;
    int     vecsize = 0;
    std::vector<int> tmp;
    while (f.is_open()){
        while (getline(f, line)){
            line = line.substr(0, line.find("#"));
            if (line == "" || line == "\n");
            else if (size == 0)
                size = std::stoi(line);
            else{
                int num;
                std::istringstream bla(line);
                while (bla >> num)
                    tmp.push_back(num);
                if (tmp.size() - vecsize == size)
                    vecsize = tmp.size();
                else{
                    throw std::runtime_error("");
                }        
            }
        }
        f.close();
    }
    if (!(controlInput(tmp, size)))
        throw std::runtime_error("");
    Node *ret = new Node(size);
    ret->setPuzzle(tmp);
    return ret;
}

void    aStarAlgo(Node *start){
    Puzzle  puzzle(start->getSize());
    std::deque<Node*> visited;

    puzzle.getOpenList().push(start);
    puzzle.getClosedList().insert(std::make_pair(start->getHash(), 0));
    while (!(puzzle.getOpenList().empty())) {
        Node *tmp = (puzzle.getOpenList().top());
        if (tmp->getH() == 0 && tmp->getG() != 0){
            print(*tmp, 0);
            std::cout << puzzle.getOpenList().size() << std::endl;
            std::cout << puzzle.getClosedList().size() << std::endl;
            break;
        }
        puzzle.getOpenList().pop();
        puzzle.addToList(*tmp);
        visited.push_back(tmp);
    }
    visited.erase(visited.begin(), visited.end());
}

int     main(int argc, char **argv){
    Node *start;
    if (argc != 2){
        std::cout << "oepsieee\n";
        return 0;
    }
    try{
        start = readfile(argv[1]);
        // start->print();
    }
    catch(std::exception &e){
        std::cout << "Invald input format\n";
        return 0;
    }
    aStarAlgo(start);
    return 0;
}









// int     main(void) {

//     Node    start(4);
//     std::vector<int> board(16, 0);
//     int i = 0;
//     start.setPuzzle(createPuzzle(board));
//     // start.setHash(start.getPuzzle());
//     // std::cout << "aaaa  " << start.getHash() << std::endl;
//     Puzzle  puzzle(4);
//     std::deque<Node*> bla;

//     puzzle.getOpenList().push(&start);
//     puzzle.getClosedList().insert(std::make_pair(start.getHash(), 0));
//     while (!(puzzle.getOpenList().empty()) && i < 5) {
//         Node *tmp = (puzzle.getOpenList().top());
//         // if (i >= 0){
//         //     std::cout << "cur\n";
//         //     tmp->print();
//         //     std::cout << tmp->getH() << std::endl;
//         // }
//         if (tmp->getH() == 0 && tmp->getG() != 0){
//             print(*tmp, 0);
//             std::cout << puzzle.getOpenList().size() << std::endl;
//             std::cout << puzzle.getClosedList().size() << std::endl;
//             std::cout << i << std::endl;
//             break;
//         }
//         puzzle.getOpenList().pop();
//         puzzle.addToList(*tmp);
//         bla.push_back(tmp);
//         // i++;
//     }
//     bla.erase(bla.begin(), bla.end());
//     std::cout << "aaa\n";
//     // while(1);
// }

