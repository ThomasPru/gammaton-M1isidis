#ifndef _OBJTRIANGLE_HPP
#define _OBJTRIANGLE_HPP

#include "OBJVertex.hpp"
#include <iostream>
#include <list>
#include <vector>
using namespace std;



class OBJTriangle {
private:
  OBJVertex point[3];
public:
  OBJTriangle();
  ~OBJTriangle(){};

  void setVertices(int i, int j, int k);
  void setNormals(int i, int j, int k);
  void setTextures(int i, int j, int k);


  OBJVertex getVertex(int i);

  friend ostream& operator<<(ostream& out, const OBJTriangle& t);
};
#endif
