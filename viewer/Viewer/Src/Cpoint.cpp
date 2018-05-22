#include "Cpoint.hpp"

#include <iostream>
using namespace std;

ostream& operator<<(ostream& out, const Cpoint& p){
  out << p.x << " " << p.y << " " << p.z;
  return out;
}
