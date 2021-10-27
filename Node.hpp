#ifndef NODE_HPP_
#define NODE_HPP_

// Copyright 2021 <eovertoo>

#include <iostream>

struct        xy {
       int    x, y;
};



class Node{
 public:
      Node(int s);
      Node(Node const & src);
      ~Node();

      Node &      operator=(Node const & src);
      void        setPuzzle(int **arr);

      int         getF() const;
      int         getG() const;
      int         getH() const;
      int         getSize() const;
      Node*       getParent() const;
      int**       getPuzzle() const;
      xy          getEmptyPiece() const;
      int**       getChild(int x, int y, int swapx, int swapy);

      void        print();
          
 private:
       Node();
       int     _f;
       int     _g;
       int     _h;
       int     _size;

       Node    *_parent;
       int     **_puzzle;
};

#endif  // NODE_HPP_
