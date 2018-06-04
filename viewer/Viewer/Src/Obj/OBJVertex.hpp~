#ifndef _OBJVERTEX_HPP
#define _OBJVERTEX_HPP

#include <iostream>
#include <list>
#include <vector>
using namespace std;


class OBJVertex {
private:
  int icoordinate;
  int inormal;
  int itexture;
public:
  OBJVertex(){};
  ~OBJVertex(){};

  void setCoordinate(int i){ icoordinate = i;}
  void setNormal(int i){ inormal = i;}
  void setTexture(int i){ itexture = i;}

  int getCoordinate() const { return icoordinate;}
  int getNormal() const { return inormal;}
  int getTexture() const { return itexture;}

  bool operator<(const OBJVertex& v);
  bool operator==(const OBJVertex& v);

  friend ostream& operator<<(ostream& out, const OBJVertex& v);
};

#endif
