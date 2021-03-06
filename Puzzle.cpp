#include "Puzzle.hpp"
#include "utils.hpp"

Puzzle::Puzzle() {}

Puzzle::Puzzle(int s, char flag) {
    _size = s;
    _goal.resize(s*s);
    _flags = flag;
    setGoal();
}

Puzzle::~Puzzle() {
}

void        Puzzle::setStart(Node &src){
    controlSolvability(src);
    calculateHeuristic(src);
    _openlist.push(&src);
    _closedlist.insert(std::make_pair(src.getHash(), 0));
}

void        Puzzle::solve(){
    int i = 0;
    int moves = 0;
    while (!(_openlist.empty())) {
        i++;
        Node *tmp = (_openlist.top());
        if (_flags & VERBOSE)
            tmp->printverbose();
        if (isGoal(*tmp)){
            printSolution(*tmp, &moves);
            std::cout << CYAN << "Number of moves: " << moves << RESET << std::endl;
            std::cout << CYAN << "Time complexity: " << i << RESET << std::endl;
            std::cout << CYAN << "Size complexity: " << _allNodes.size() + 1 << RESET << std::endl;
            return ;
        }     
        _openlist.pop();
        addToList(*tmp);
    }
}

void        Puzzle::setupChild(Node &src, int newpos, char direc){
    if (src.getParent() != NULL && src.getParent()->getEmptyPiece().i == newpos)
        return;
    else{
        std::unique_ptr<Node> tmp = std::make_unique<Node>(Node(src.getSize()));
        tmp->swapGrid(src, newpos);
        tmp->setParent(src, _flags);
        tmp->setDirec(direc);
        auto it = _closedlist.find(tmp->getHash());
        if (it == _closedlist.end()){
            calculateHeuristic(*tmp);
            _openlist.push(&(*tmp));
            _closedlist.insert(std::make_pair(tmp->getHash(), tmp->getG()));
            _allNodes.push_back(std::move(tmp));
        }
        else if (it->second > tmp->getG()){
		    _closedlist[tmp->getHash()] = tmp->getG();
            calculateHeuristic(*tmp);
            _openlist.push(&(*tmp));
            _allNodes.push_back(std::move(tmp));
        }
    }
}

void        Puzzle::addToList(Node &src) {
    xy  current = src.getEmptyPiece();
    //MOVE RIGHT
    if (current.i % _size != _size-1){
        if (current.i+1 >= 0 && current.i+1 < (_size*_size))
            setupChild(src, current.i+1, 'R');
    }
    //MOVE LEFT      
    if (current.i % _size != 0){
        if (current.i-1 >= 0 && current.i-1 < (_size*_size))
            setupChild(src, current.i-1, 'L');
    }
    //MOVE UP
    if (current.i-_size >= 0 && current.i-_size < (_size*_size))
        setupChild(src, current.i-_size, 'U');
    //MOVE DOWN
    if (current.i+_size >= 0 && (current.i+_size) < (_size*_size))
        setupChild(src, current.i+_size, 'D');
}

void        Puzzle::calculateHeuristic(Node &n){
    if (!(_flags & UNIFORM)){
        if (_flags & EUCLIDEAN)
            calculateEuclidean(n);
        else if (_flags & HAMMING)
            calculateHamming(n);
        else
            calculateManhattan(n);
    }
    else
        n.setH(0);
}

void        Puzzle::calculateHamming(Node &n){
    int h = 0;
    std::vector<int> grid = n.getPuzzle();
    if (n.getParent() != NULL && n.getParent()->getH() != 0){
        h = n.getParent()->getH();
        xy old_cor = n.getParent()->getEmptyPiece();
        xy new_cor = n.getEmptyPiece();
        xy goal = _goal[grid[old_cor.i]];
        if (goal.x == old_cor.x && goal.y == old_cor.y)
            h--;
        else if (goal.x == new_cor.x && goal.y == new_cor.y)
            h++;
        n.setH(h);
    }
    else{
        for (int i = 0; i < (_size*_size); i++){
            if (grid[i] != 0){
                xy goal = _goal[grid[i]];
                if (goal.x != i % _size || goal.y != i / _size)
                    h++;
            }
        }
        n.setH(h);
    }
}

void        Puzzle::calculateEuclidean(Node &n){
    float h = 0;
    std::vector<int> grid = n.getPuzzle();
    for(int i = 0; i < (_size*_size); i++){
        if (grid[i] != 0){
            int y = pow(abs((i/_size) - _goal[grid[i]].y), 2);
            int x = pow(abs((i%_size) - _goal[grid[i]].x), 2);
            h += sqrt((y+x));
        }
    }
    n.setH(h);
}

void        Puzzle::calculateManhattan(Node &n){
    int h = 0;
    
    std::vector<int> grid = n.getPuzzle();
    if (n.getParent() != NULL && n.getParent()->getH() != 0){
        h = n.getParent()->getH();
        xy new_cor = n.getParent()->getEmptyPiece();
        xy old_cor = n.getEmptyPiece();
        xy goal = _goal[grid[new_cor.i]];

        int newpos = abs(new_cor.x - goal.x) + abs(new_cor.y - goal.y);
        int oldpos = abs(old_cor.x - goal.x) + abs(old_cor.y - goal.y);
        h = h - oldpos + newpos;
        n.setH(h);
        return;
    }
    else{
        for (int i = 0; i < (_size*_size); i++){
            if (grid[i] != 0){
                h += abs((i/_size) - _goal[grid[i]].y) + abs((i%_size) - _goal[grid[i]].x);
            }
        }
        n.setH(h);
    }
}

int         Puzzle::manhattanZero(xy coordinates_start){
    xy coordinates_goal = _goal[0];

    return (abs(coordinates_start.x - coordinates_goal.x) + abs(coordinates_start.y - coordinates_goal.y));
}

std::vector<int>    Puzzle::convertPuzzle(std::vector<int> puzzle, std::vector<int> rowgoal){
    std::vector<int>    convertPuzzle;
    convertPuzzle.resize(_size*_size);

    for (int i = 0; i < _size*_size; i++){
        int x = _goal[puzzle[i]].x;
        int y = _goal[puzzle[i]].y;
        int index = y *_size + x;
        convertPuzzle[i] = rowgoal[index];
    }
    return convertPuzzle;
}

void        Puzzle::controlSolvability(Node &start){
    std::vector<int>    rowgoal;
    rowgoal.resize(_size*_size);
    for (int i = 1; i < (_size*_size); i++)
        rowgoal[i - 1] = i;
    rowgoal[_size*_size - 1] = 0;
    std::vector<int>    rowstart = convertPuzzle(start.getPuzzle(), rowgoal);
    int start_inversion = calculateInversions(rowstart, _size);
    if (start_inversion % 2 != manhattanZero(start.getEmptyPiece()) % 2)
        throw std::runtime_error("Puzzle is unsolvable");
}

void        Puzzle::setGoal(){
    xy coordinates;
    coordinates.x = 0;
    coordinates.y = 0;
    coordinates.i = 0;
    int val = 1;
    int cnt = 0;

    while(val < (_size*_size)){
        for (;coordinates.x < (_size - cnt) && val < (_size*_size); coordinates.x++, val++, coordinates.i++){
            _goal[val] = coordinates;
        }
        for (coordinates.x--,coordinates.y++; coordinates.y < (_size - cnt) && val < (_size*_size); val++, coordinates.y++, coordinates.i++) {
            _goal[val] = coordinates;
            if (val + 1 == _size*_size){
                coordinates.x--;
                _goal[0] = coordinates;
                return;
            }
        }
        for (coordinates.x--, coordinates.y--; coordinates.x >= (0 + cnt) && val < (_size*_size); val++, coordinates.x--, coordinates.i++) {
            _goal[val] = coordinates;
        }
        for (coordinates.y--, coordinates.x++; coordinates.y > (0 + cnt) && val < (_size*_size); val++, coordinates.y--, coordinates.i++) {
            _goal[val] = coordinates;
            if (val + 1 == _size*_size){
                coordinates.x++;
                _goal[0] = coordinates;
                return;
            }
        }
        coordinates.y++;
        coordinates.x++;
        cnt++;
    }
}

bool        Puzzle::isGoal(Node &n){
    if (!(_flags & GREEDY) && !(_flags & UNIFORM) && n.getH() == 0)
        return true;
    if (_flags & GREEDY && n.getH() == 0)
        return true;
    if (_flags & UNIFORM){
        std::vector<int> grid = n.getPuzzle();
        for (int i = 0; i < (_size*_size); i++){
            if (grid[i] != 0){
                xy goal = _goal[grid[i]];
                if (goal.x != i % _size || goal.y != i / _size)
                    return false;
            }
        }
        return true;
    }
    return false;
}

void            Puzzle::printSolution(Node &tmp, int *moves){
    if (tmp.getParent() != NULL){
        (*moves)++;
        printSolution(*(tmp.getParent()), moves);
    }
    tmp.print();
}