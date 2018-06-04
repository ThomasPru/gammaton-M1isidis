#ifndef _OBJLIGHT_HPP
#define _OBJLIGHT_HPP

#include "OBJTriangle.hpp"
#include "../Crgb.hpp"
#include "../Cpoint.hpp"
#include <vector>
#include <string>
using namespace std;

class OBJLight {
public:
  const static int POINTLIGHT = 0;
  const static int AREALIGHT  = 1;
private:
  const static int UNKNOWN = -1;
  // attributs communs
  string name;
  int type;
  Crgb color;
  float power;
  int samplingRate;
  // attributs pour une POINTLIGHT
  Cpoint position;
  // attributs pour une AREALIGHT
  vector <OBJTriangle *> faces;

public:
  OBJLight(char *name);
  ~OBJLight(){ faces.clear();}

  void setType(int type){ this->type = type;}
  void setColor(float r, float g, float b){ color.assign(r,g,b);}
  void setPower(float p){ power = p;}
  void setSamplingRate(int sr){ samplingRate = sr; }
  void setPointLightPosition(float x, float y, float z){
    position.assign(x,y,z);
  }

  void addTriangle(int v1, int v2, int v3){
    OBJTriangle *t = new OBJTriangle();
    t->setVertices(v1, v2, v3);
    faces.push_back(t);
  }


  int getType(){ return type; }
  string getName(){ return name;}
  Crgb getColor(){ return color;}
  float getPower(){ return power;}
  int getSamplingRate(){ return samplingRate;}
  Cpoint getPointLightPosition(){ return position;}

  void toLxs(ostream& lxsFile, const vector<Cpoint> &srcVertices);

  friend ostream& operator<<(ostream& out, const OBJLight& t);
};
#endif
