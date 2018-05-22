#ifndef _OBJMATERIAL_HPP
#define _OBJMATERIAL_HPP

#include <iostream>
#include <string>
using namespace std;
#include "../Crgb.hpp"

class OBJMaterial {
private:
  float Ka[3];
  float Kd[3];
  float Ks[3];
  float d, Ns;
  int illum;
  string name;
  string map_ka, map_kd, map_ks;
public:
  OBJMaterial();
  OBJMaterial(const string& name);
  ~OBJMaterial();


  void setKa(float *ka);
  void setKd(float *kd);
  void setKs(float *ks);
  void setRefractionIndex(float d);
  void setShininess(float s);
  void setIllum(int i);
  void setMapKa(const string& mka);
  void setMapKd(const string& mkd);
  void setMapKs(const string& mks);

  bool operator==(const string& name);


  string getName(){ return name; }
  Crgb getAmbiantColor();
  Crgb getDiffuseColor();
  Crgb getSpecularColor();

  bool isTextured(){ 
    return (!(map_ka.empty() && map_kd.empty() && map_ks.empty()));
  }

  // exporte la définition du matériau
  void toLxm(ostream& lxmFile);
  // exporte la commande d'utilisation du matériau
  void toLxs(ostream& lxsFile);

  friend ostream& operator<<(ostream& out, const OBJMaterial& m);

private:
  static const int LXS_CARPAINT=0;
  static const int LXS_GLASS=1;
  static const int LXS_GLOSSY=2;
  static const int LXS_MATTE=3;
  static const int LXS_MATTE_TRANSLUCENT=4;
  static const int LXS_METAL=5;
  static const int LXS_MIRROR=6;
  static const int LXS_MIX=7;
  static const int LXS_NULL=8;
  static const int LXS_PLASTIC=9;
  static const int LXS_ROUGH_GLASS=10;
  static const int LXS_SHINY_METAL=11;
  static const int LXS_SUBSTRATE=12;

  static const int LXS_MATTE_TEXTURE=20;

  int materialType;

  bool isNull(float t[3]){
    return (t[0]==0.0 && t[1]==0.0 && t[2]==0.0);
  }


};
#endif
