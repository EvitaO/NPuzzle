#include "Puzzle.hpp"
#include "utils.hpp"

Puzzle::Puzzle() {}

Puzzle::Puzzle(int s, Options input) {
    _size = s;
    _goal.resize(s*s);
    _userinput = input;
    setGoal();
}

Puzzle::~Puzzle() {
}

void        Puzzle::setStart(Node &src){
    controlSolvabilty(src);
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
        if (isGoal(*tmp)){
            printSolution(*tmp, &moves);
            std::cout << "Number of moves: " << moves << std::endl;
            std::cout << "Time complexity: " << i << std::endl;
            std::cout << "Size complexity: " << _allNodes.size() << std::endl;
            std::cout << _openlist.size() << std::endl;
            std::cout << _closedlist.size() << std::endl;
            exit(EXIT_SUCCESS);
        }     
        _openlist.pop();
        addToList(*tmp);
    }
    exit(EXIT_FAILURE);

}

void        Puzzle::setupChild(Node &src, int newpos){
    if (src.getParent() != NULL && src.getParent()->getEmptyPiece().i == newpos)
        return;
    else{
        std::unique_ptr<Node> tmp = std::make_unique<Node>(Node(src.getSize()));
        tmp->swapGrid(src, newpos);
        tmp->setParent(src, _userinput.search);
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
            setupChild(src, current.i+1);
    }
    //MOVE LEFT      
    if (current.i % _size != 0){
        if (current.i-1 >= 0 && current.i-1 < (_size*_size))
            setupChild(src, current.i-1);
    }
    //MOVE UP
    if (current.i-_size >= 0 && current.i-_size < (_size*_size))
        setupChild(src, current.i-_size);
    //MOVE DOWN
    if (current.i+_size >= 0 && (current.i+_size) < (_size*_size))
        setupChild(src, current.i+_size);
}

void        Puzzle::calculateHeuristic(Node &n){
    if (_userinput.search == 0 || _userinput.search == 1){
        if (_userinput.heuristic == 0)
            calculateManhattan(n);
        if (_userinput.heuristic == 1)
            calculateEuclidean(n);
        if (_userinput.heuristic == 2)
            calculateMisplacedNodes(n);
    }
    else
        n.setH(0);
}

void        Puzzle::calculateMisplacedNodes(Node &n){
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

void        Puzzle::controlSolvabilty(Node &start){
    std::vector<int>    goal;
    goal.resize(_size*_size);
    for (int i = 1; i < (_size*_size); i++){
        int x = _goal[i].x;
        int y = _goal[i].y;
        int index = y *_size + x;
        goal[index] = i; 
    }
    int goal_inversion = calculateInversions(goal, _size);
    std::cout << "---------------\n";
    int start_inversion = calculateInversions(start.getPuzzle(), _size);
    std::cout << goal_inversion << std::endl;
    std::cout << "---------------\n";
    std::cout << start_inversion << std::endl;
    // if (goal_inversion % 2 != start_inversion % 2)
    //     throw std::runtime_error("Puzzle is unsolvable");

    if (_size % 2 == 0){
        if ((_size - start.getEmptyPiece().y) % 2 == 0 && start_inversion % 2 != 0)
            throw std::runtime_error("Puzzle is unsolvable");
    }
    else if (start_inversion % 2 != 0)
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
        }
        for (coordinates.x--, coordinates.y--; coordinates.x >= (0 + cnt) && val < (_size*_size); val++, coordinates.x--, coordinates.i++) {
            _goal[val] = coordinates;
        }
        for (coordinates.y--, coordinates.x++; coordinates.y > (0 + cnt) && val < (_size*_size); val++, coordinates.y--, coordinates.i++) {
            _goal[val] = coordinates;
        }
        coordinates.y++;
        coordinates.x++;
        cnt++;
    }
}

bool        Puzzle::isGoal(Node &n){
    if (_userinput.search == 0 && n.getH() == 0)
        return true;
    if (_userinput.search == 1 && n.getH() == 0)
        return true;
    if (_userinput.search == 2){
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

std::unordered_map<uint64_t, int>&                              Puzzle::getClosedList() {
    return _closedlist;
}

std::priority_queue<Node*, std::vector<Node*>, CompareF >&      Puzzle::getOpenList() {
    return _openlist;
}

std::deque<std::unique_ptr<Node> >                              Puzzle::getAllList(){
    return std::move(_allNodes);
}

void            Puzzle::printSolution(Node &tmp, int *moves){
    if (tmp.getParent() != NULL){
        (*moves)++;
        printSolution(*(tmp.getParent()), moves);
    }
    tmp.print();
    std::cout << "---------------------\n";
}