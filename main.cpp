//  Copyright 2021 <eovertoo>

#include "utils.hpp"
#include <chrono>
#include <Python.h>

void    aStarAlgo(Node *start, char flag){
    Puzzle  puzzle(start->getSize(), flag);
    try{
        puzzle.setStart(*start);
        puzzle.solve();
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void    help(){
    std::cout << "Usage:    npuzzle [file] [-flag] [-flag]\n";
    std::cout << "Optional flags:\n";
    std::cout << "  -m          use manhattan heuristic\n";
    std::cout << "  -e          use euclidean heuristic\n";
    std::cout << "  -h          use hamming heuristic\n";
    std::cout << "  -a          use astar search\n";
    std::cout << "  -g          use greedy search\n";
    std::cout << "  -u          use uniform-cost search\n";
    std::cout << "It is not possible to use multiple heuristics and/or multiple search methods\n";

    std::cout << "\nFile has to have a '.txt' extension\n";
    std::cout << "If no file is given, the program will create a puzzle\n";
}

std::string    flags(char flag, char **argv, int argc){
    std::string filename = "";
    for (int i = 1; i < argc; i++){
        if (argv[i][0] == '-' && std::strlen(argv[i]) == 2){
        switch(argv[i][1]){
            case 'm':
                if (flag & euclidean || flag & hamming)
                    throw std::runtime_error("\nIncorrect format used");
                else
                    flag |= manhattan;
                break;
            case 'e':
                if (flag & manhattan || flag & hamming)
                    throw std::runtime_error("\nIncorrect format used");
                else
                    flag |= euclidean;
                break;
            case 'h':
                if (flag & manhattan || flag & euclidean)
                    throw std::runtime_error("\nIncorrect format used");
                else
                    flag |= hamming;
                break;
            case 'u':
                if (flag & astar || flag & greedy)
                    throw std::runtime_error("\nIncorrect format used");
                else
                    flag |= uniform;
                break;
            case 'g':
                if (flag & astar || flag & uniform)
                    throw std::runtime_error("\nIncorrect format used");
                else
                    flag |= greedy;
                break;
            case 'a':
                if (flag & greedy || flag & uniform)
                    throw std::runtime_error("\nIncorrect format used");
                else
                    flag |= astar;
                break;
            default:
                throw std::runtime_error("\nIncorrect argument used");
                break;
        }
        }
        else if (filename == "")
            filename = argv[i];
        else
            throw std::runtime_error("\nIncorrect argument used");
    }
    return filename;
}

int     main(int argc, char **argv){
    auto begin_time = std::chrono::steady_clock::now();
    std::unique_ptr<Node> start; 
    {
    if (argc > 4){
        help();
        std::cout << "\nInvalid input\n";
        return 0;
    }
    char flag;
    std::string file;
    try{
        file = flags(flag, argv, argc);
    }
    catch(std::exception &e){
        help();
        std::cout << e.what() << std::endl;
        return 0;
    }
    if (file == ""){
        try{
            start = createPuzzle();
        }
        catch(std::exception &e){
            std::cout << "Invalid size\n";
            return 0;
        }
    }
    else {
        if (std::strlen(file.c_str()) < std::strlen(".txt") || file.compare(std::strlen(file.c_str()) - std::strlen(".txt"), std::strlen(".txt"), ".txt") != 0){
            help();
            std::cout << "\nInvalid file\n";
            return 0;
        }   
        try{
            start = readfile(argv[1]);
        }
        catch(std::exception &e){
            std::cout << "Invald input file\n";
            return 0;
        }
    }
    aStarAlgo(&(*start), flag);
    }
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - begin_time;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString('sys.path.appen("./test.py")');
    Py_Finalize();
    // while(1);
    return 0;
}
