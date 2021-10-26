#ifndef GRID_HPP_
#define GRID_HPP_

// Copyright 2021 <eovertoo>

#include <iostream>

struct        xy {
       int    x, y;
};



class Grid{
 public:
       Grid(int s);
       Grid(Grid const & src);
       ~Grid();

       Grid &  operator=(Grid const & src);
       void    setPuzzle(int **arr);

       int     getF() const;
       int     getG() const;
       int     getH() const;
       int     getSize() const;
       Grid*   getParent() const;
       int**   getPuzzle() const;
       xy      getEmptyPiece() const;
       int**    getChild(int x, int y, int swapx, int swapy);
 private:
       Grid();
       int     _f;
       int     _g;
       int     _h;
       int     _size;

       Grid    *_parent;
       int     **_puzzle;
};

struct        CompareF {
       bool    operator()(Grid const & a, Grid const & b) {return a.getF() < b.getF();}
};

#endif  // GRID_HPP_
