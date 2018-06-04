#include "Cpoint.hpp"

#include <iostream>
using namespace std;

ostream& operator<<(ostream& out, const Cpoint& p){
  out << p.x << " " << p.y << " " << p.z;
  return out;
}

double Cpoint::getX() const{
  return x;
}

double Cpoint::getY() const{
  return y;
}

double Cpoint::getZ() const{
  return z;
}
