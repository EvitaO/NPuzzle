#ifndef NODE_HPP_
#define NODE_HPP_

// Copyright 2021 <eovertoo>

#include <iostream>
#include <vector>
#include <algorithm>

struct        xy {
       int    x, y;
};



class Node{
 public:
      Node(int s);
      Node(Node const & src);
      ~Node();

      Node &      operator=(Node const & src);
      void        setPuzzle(std::vector<std::vector<int> >);
      void        setParent(Node *parent);
      void        setH(int h);
      
      int         getF() const;
      int         getG() const;
      int         getH() const;
      int         getSize() const;
      Node*       getParent() const;
      std::vector<std::vector<int> >       getPuzzle() const;
      xy          getEmptyPiece() const;
      std::vector<std::vector<int> >       getChild(int x, int y, int swapx, int swapy);

      void        print();
          
 private:
       Node();
     //   int     _f;
       int     _g;
       int     _h;
       int     _size;

       Node    *_parent;
       std::vector<std::vector<int> > _puzzle;
};

#endif  // NODE_HPP_
