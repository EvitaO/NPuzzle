//  Copyright 2021 <eovertoo>

#include "Puzzle.hpp"
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <memory>

int     getUserInput(){
    std::string input;
    std::cout << "give the size of a puzzle\n";
    std::cin >> input;

    for (int i = 0; i < std::strlen(input.c_str()); i++)
    {
        if (!isdigit(input[i]))
            throw std::runtime_error("");
    }
    int size = stoi(input);
    if (size <= 1)
        throw std::runtime_error("");
    return size;
}

std::unique_ptr<Node>   createPuzzle(){
    srand(time(NULL));
    int size = getUserInput();
    std::vector<int> grid(size*size, -1);
    for (int i = 0; i < size*size; i++){
        while (1){
            int tmp = rand() % (size * size);
            if (grid[tmp] == -1){
                grid[tmp] = i;
                break;
            }
        }
    }
    std::unique_ptr<Node> ret = std::make_unique<Node>(Node(size));
    ret->setPuzzle(grid);
    ret->print();
    return ret;
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

std::unique_ptr<Node>    readfile(char *file){
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
    std::unique_ptr<Node> ret = std::make_unique<Node>(Node(size));
    // std::unique_ptr<Node> ret = new Node(size);
    ret->setPuzzle(tmp);
    return ret;
}

void    aStarAlgo(Node *start){
    Puzzle  puzzle(start->getSize());
    int i = 0;

    puzzle.getOpenList().push(start);
    puzzle.getClosedList().insert(std::make_pair(start->getHash(), 0));
    while (!(puzzle.getOpenList().empty())) {
        i++;      
        Node *tmp = (puzzle.getOpenList().top());
        if (tmp->getH() == 0 && tmp->getG() != 0){
            print(*tmp, 0);
            std::cout << "Number of moves: " << tmp->getG() << std::endl;
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

int     main(int argc, char **argv){
    std::unique_ptr<Node> start;
    {
    if (argc != 2){
        try{
            start = createPuzzle();
        }
        catch(std::exception &e){
            std::cout << "Invalid size\n";
            return 0;
        }// std::cout << "oepsieee\n";
    }
    else{
        try{
            start = readfile(argv[1]);
            // start->print();
        }
        catch(std::exception &e){
            std::cout << "Invald input format\n";
            return 0;
        }
    }
    aStarAlgo(&(*start));
    }
    std::cout << "a\n";
    // while(1);
    return 0;
}
