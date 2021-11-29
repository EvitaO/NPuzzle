#ifndef NODE_HPP_
#define NODE_HPP_

#include <iostream>
#include <vector>
#include <iomanip>

#define manhattan   (1 << 0)
#define euclidean   (1 << 1)
#define hamming     (1 << 2)
#define greedy      (1 << 3)
#define uniform     (1 << 4)
#define astar       (1 << 5)
#define verbose     (1 << 6)

#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BOLDGREEN   "\033[1m\033[32m"
#define RESET   "\033[0m"


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
      void        setParent(Node &parent, char flag);
      void        setH(float h);
      void        setHash(std::vector<int> src);
      void        setDirec(char direc);

      float                 getF() const;
      int                   getG() const;
      float                 getH() const;
      int                   getSize() const;
      uint64_t              getHash() const;
      
      Node*                 getParent() const;
      std::vector<int>      getPuzzle() const;
      xy&                   getEmptyPiece();
      char                  getDirec() const;

      void        swapGrid(Node &src, int swapi);
      void        print();
      void        printverbose();
          
 private:
       int     _g;
       float   _h;
       int     _size;

       Node              *_parent;
       std::vector<int>  _puzzle;
       xy                _coordinates;
       uint64_t          _hash;
       char              _direc;
};

#endif