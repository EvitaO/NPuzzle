#include "utils.hpp"

bool     controlPuzzle(std::vector<int> input, int size){
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

void                     checkline(std::string const &line){
    for (char c : line){
        if (!isdigit(c) && !isspace(c))
            throw std::runtime_error("");
    }
}

void                     readNumbers(std::string const &line, std::vector<int> &tmp){
    int num;
    std::istringstream l(line);
    checkline(line);
    while (l >> num)
        tmp.push_back(num);
}

void                      counterCheckLine(std::vector<int> const &tmp, int const &size, int &vectorsize){
    if (tmp.size() - vectorsize == size)
        vectorsize = tmp.size();
    else
        throw std::runtime_error("");
}

std::unique_ptr<Node>    makeStartNode(std::vector<int> &tmp, int const size){
    std::unique_ptr<Node> start = std::make_unique<Node>(Node(size));
    start->setPuzzle(tmp);
    return start;
}

std::unique_ptr<Node>    readfile(char *file){
    std::string line;
    std::ifstream f(file);
    std::vector<int> tmp;
    int     size = 0;
    int     vecsize = 0;
    if (!f)
        throw std::runtime_error("");
    while (f.is_open()){
        while (getline(f, line)){
            line = line.substr(0, line.find("#"));
            if (line == "" || line == "\n");
            else if (size == 0){
                checkline(line);
                size = stoi(line);
            }
            else{
                readNumbers(line, tmp);
                counterCheckLine(tmp, size, vecsize);    
            }
        }
        f.close();
    }
    if (size == 0 || size == 2 || !(controlPuzzle(tmp, size)))
        throw std::runtime_error("");
    return makeStartNode(tmp, size);
}