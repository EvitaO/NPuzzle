#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "Puzzle.hpp"
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <memory>


std::unique_ptr<Node>   readfile(char *file);
void                    checkline(std::string const &line);
void                    readNumbers(std::string const &line, std::vector<int> &tmp);
void                    counterCheckLine(std::vector<int> const &tmp, int const &size, int &vectorsize);
bool                    controlPuzzle(std::vector<int> input, int size);

std::unique_ptr<Node>   makeStartNode(std::vector<int> &tmp, int const size);

std::unique_ptr<Node>   createPuzzle();
int                     getSizePuzzle();

Options                 chooseInput();

#endif