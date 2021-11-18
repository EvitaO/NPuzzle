#ifndef NODE_HPP_
#define NODE_HPP_

// Copyright 2021 <eovertoo>

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct        xy {
       int    x, y, i;
};



class Node{
 public:
      Node();
      Node(int s);
      Node(Node *src);
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
      Node*       getParent() const;
      std::vector<int>       getPuzzle() const;
      xy&         getEmptyPiece();
      void        getChild(Node &src, int swapi);
      uint64_t    getHash() const;
      void        print();
      std::vector<Node>&      getChildren();
          
 private:
     //   int     _f;
       int     _g;
       int     _h;
       int     _size;

       Node    *_parent;
       std::vector<int> _puzzle;
       xy     _coordinates;
       uint64_t     _hash;
       std::vector<Node> _children;
};

#endif  // NODE_HPP_
