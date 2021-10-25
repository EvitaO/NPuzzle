#ifndef GRID_HPP_
#define GRID_HPP_

// Copyright 2021 <eovertoo>

class Grid{
 public:
        Grid();
        Grid(Grid const & src);
        ~Grid();

        Grid &  operator=(Grid const & src);

        int     getF() const;
        int     getG() const;
        int     getH() const;
        Grid*   getParent() const;

 private:
        int     _f;
        int     _g;
        int     _h;

        Grid    *_parent;
        int     **_puzzle;
};

#endif  // GRID_HPP_
