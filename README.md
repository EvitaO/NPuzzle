# NPuzzle

The goal of this project is to solve the N-puzzle ("taquin" in French) game using the A*
search algorithm or one of its variants.</br></br>
You start with a square board made up of N*N cells. One of these cells will be empty,
the others will contain numbers, starting from 1, that will be unique in this instance of
the puzzle.</br></br>
Your search algorithm will have to find a valid sequence of moves in order to reach the
final state, a.k.a the "snail solution", which depends on the size of the puzzle (Example
below). While there will be no direct evaluation of its performance in this instance of the
project, it has to have at least a vaguely reasonable perfomance : Taking a few second to
solve a 3-puzzle is pushing it, ten seconds is unacceptable.</br></br>

<img src="./image/npuzzle.png" width="400">

### Compile
```
Cmake -B build && cd build
make all
```
### Usage
```
./npuzzle [file] [-flag] [-flag] [-flag]
Optional flags:
  -v          verbose-mode
  -m          use manhattan heuristic
  -e          use euclidean heuristic
  -h          use hamming heuristic
  -a          use astar search
  -g          use greedy search
  -u          use uniform-cost search
It is not possible to use multiple heuristics and/or multiple search methods

File has to have a '.txt' extension
If no file is given, the program will create a puzzle
```

### Output
<img src="./image/output.png" width="400">

### Tester
```
./test/npuzzle_test
```
