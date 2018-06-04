#include "OBJVertex.hpp"

#include <iostream>
using namespace std;


bool OBJVertex::operator<(const OBJVertex& v){
  return icoordinate < v.icoordinate;
}

bool OBJVertex::operator==(const OBJVertex& v){
  return (icoordinate==v.icoordinate && inormal==v.inormal);
}

ostream& operator<<(ostream& out, const OBJVertex& v){
  out << "(" << v.icoordinate;
  out << "," << v.inormal;
  out << "," << v.itexture;
  out << ")";
  return out;
}


