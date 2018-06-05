#ifndef _OBJTRIANGLE_HPP
#define _OBJTRIANGLE_HPP

#define MOLLEREPSILON 0.000001

#include "OBJVertex.hpp"

//-------------------
//--Added
#include "CRay.hpp"
#include "Surf.hpp"
//-------------------

//#include <iostream>
#include <list>
#include <vector>
using namespace std;


class CIntersection;
class OBJReader;

extern OBJReader r;


class OBJTriangle {
private:
  OBJVertex point[3];
  Surf surface;
public:
  OBJTriangle();
  OBJTriangle(Surf surfac);
  ~OBJTriangle(){};

  void setVertices(int i, int j, int k);
  void setNormals(int i, int j, int k);
  void setTextures(int i, int j, int k);

  OBJVertex getVertex(int i);

  bool getIntersectionWithRay(const CRay& incidentRay, CIntersection &I);

  friend ostream& operator<<(ostream& out, const OBJTriangle& t);

  Surf getSurface() const;
};
#endif
