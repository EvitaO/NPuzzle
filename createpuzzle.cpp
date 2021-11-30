#include "utils.hpp"

std::unique_ptr<Node>   createPuzzle(){
    srand(time(NULL));
    int size = getSizePuzzle();
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
    return makeStartNode(grid, size);
}

int     getSizePuzzle(){
    std::string input;
    std::cout << "give the size of a puzzle (>= 3 && <= 20)\n";
    std::cin >> input;

    if (std::cin.eof())
        exit(EXIT_FAILURE);
    for (int i = 0; i < std::strlen(input.c_str()); i++)
    {
        if (!isdigit(input[i]))
            throw std::runtime_error("");
    }
    int size = stoi(input);
    if (size <= 2 || size > 20)
        throw std::runtime_error("");
    return size;
}