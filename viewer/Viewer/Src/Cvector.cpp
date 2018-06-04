#include "Cvector.hpp"

Cvector::Cvector(){
  x = 0;
  y = 0;
  z = 0;
}

Cvector::Cvector(const Cvector &cv){
  x = cv.getX();
  y = cv.getY();
  z = cv.getZ();
}

Cvector::Cvector(Cpoint a, Cpoint b){
  x = a.getX() - b.getX();
  y = a.getY() - b.getY();
  z = a.getZ() - b.getZ();
}

Cvector::Cvector(double x_c, double y_c, double z_c){
  x = x_c;
  y = y_c;
  z = z_c;
}


void Cvector::assign( float vx, float vy, float vz ){
  x = vx;
  y = vy;
  z = vz;
}

void Cvector::assign( const Cvector &v ){
  x = v.x;
  y = v.y;
  z = v.z;
}


float Cvector::getX() const{
  return x;
}

float Cvector::getY() const{
  return y;
}

float Cvector::getZ() const{
  return z;
}


