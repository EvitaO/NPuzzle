#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "Puzzle.hpp"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>
#include <chrono>

//Functions to read file and control input
std::unique_ptr<Node>   readfile(char *file);
void                    checkline(std::string const &line);
void                    readNumbers(std::string const &line, std::vector<int> &tmp);
void                    counterCheckLine(std::vector<int> const &tmp, int const &size, int &vectorsize);
bool                    controlPuzzle(std::vector<int> input, int size);

//Make start node
std::unique_ptr<Node>   makeStartNode(std::vector<int> &tmp, int const size);

//Create puzzle for user
std::unique_ptr<Node>   createPuzzle();
int                     getSizePuzzle();

//Function to check amount of inversions in puzzle
int                     calculateInversions(std::vector<int> vec, int size);


#endif