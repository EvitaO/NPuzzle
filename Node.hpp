#ifndef NODE_HPP_
#define NODE_HPP_

// Copyright 2021 <eovertoo>

#include <iostream>
#include <vector>

struct        xy {
       int    x, y, i;
};



class Node{
 public:
      Node();
      Node(int s);
      Node(Node const & src);
      ~Node();

      Node &      operator=(Node const & src);

      void        setPuzzle(std::vector<int> &arr);
      void        setParent(Node &parent);
      void        setH(int h);
      void        setHash(std::vector<int> src);
      
      int         getF() const;
      int         getG() const;
      int         getH() const;
      int         getSize() const;
      uint64_t    getHash() const;
      
      Node*              getParent() const;
      std::vector<int>   getPuzzle() const;
      xy&                getEmptyPiece();

      void        swapGrid(Node &src, int swapi);
      void        print();
          
 private:
       int     _g;
       int     _h;
       int     _size;

       Node              *_parent;
       std::vector<int>  _puzzle;
       xy                _coordinates;
       uint64_t          _hash;
};

#endif  // NODE_HPP_
