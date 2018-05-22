#include "OBJTriangle.hpp"

OBJTriangle::OBJTriangle(){
  for(int i=0; i<3; i++){
    point[i].setCoordinate(-1);
    point[i].setNormal(-1);
    point[i].setTexture(-1);
  }
}

void OBJTriangle::setVertices(int i, int j, int k){
  point[0].setCoordinate(i);
  point[1].setCoordinate(j);
  point[2].setCoordinate(k);
}

void OBJTriangle::setNormals(int i, int j, int k){
  point[0].setNormal(i);
  point[1].setNormal(j);
  point[2].setNormal(k);
}

void OBJTriangle::setTextures(int i, int j, int k){
  point[0].setTexture(i);
  point[1].setTexture(j);
  point[2].setTexture(k);
}



OBJVertex OBJTriangle::getVertex(int i){
  return point[i];
}


ostream& operator<<(ostream& out, const OBJTriangle& t){
  out << "f ";
  for(int i=0; i<3; i++)
    out << t.point[i].getCoordinate() << "/" << t.point[i].getTexture() << "/" << t.point[i].getNormal() << " ";
  out << endl;
  return out;
}
