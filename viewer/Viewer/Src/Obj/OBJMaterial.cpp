#include "OBJMaterial.hpp"

#include <cstring>

OBJMaterial::OBJMaterial(){
  Ka[0] = Ka[1] = Ka[2] = 0.2;
  Kd[0] = Kd[1] = Kd[2] = 0.7;
  Ks[0] = Ks[1] = Ks[2] = 0.0;
  d = 1;
  Ns = 0;
  illum = 2;
  // name = new char[8];
//   strcpy(name,"no_name");
  name = "no_name";
  map_ka = map_kd = map_ks = "";
}

OBJMaterial::OBJMaterial(const string& matname){
  Ka[0] = Ka[1] = Ka[2] = 0.2;
  Kd[0] = Kd[1] = Kd[2] = 0.7;
  Ks[0] = Ks[1] = Ks[2] = 0.0;
  d = 1;
  Ns = 0;
  illum = 2;
//   name = new char[strlen(matname)+1];
//   strcpy(name,matname);
  name = matname;
  map_ka = map_kd = map_ks = "";
}

OBJMaterial::~OBJMaterial(){
//   delete name;
//   delete map_ka;
//   delete map_kd;
//   delete map_ks;
}



void OBJMaterial::setKa(float *ka){
  memcpy(this->Ka, ka, 3*sizeof(float));
}

void OBJMaterial::setKd(float *kd){
  memcpy(this->Kd, kd, 3*sizeof(float));
}

void OBJMaterial::setKs(float *ks){
  memcpy(this->Ks, ks, 3*sizeof(float));
}


void OBJMaterial::setRefractionIndex(float d){
  this->d = d;
}

void OBJMaterial::setShininess(float s){
  this->Ns = s;
}


void OBJMaterial::setIllum(int i){
  this->illum = i;
}


void OBJMaterial::setMapKa(const string& mka){
  map_ka=mka;
}

void OBJMaterial::setMapKd(const string& mkd){
  map_kd=mkd;

}

void OBJMaterial::setMapKs(const string& mks){
  map_ks=mks;

}

Crgb OBJMaterial::getAmbiantColor(){
  Crgb color;
  color.assign(Ka[0], Ka[1], Ka[2]);
  return color;
}

Crgb OBJMaterial::getDiffuseColor(){
  Crgb color;
  color.assign(Kd[0], Kd[1], Kd[2]);
  return color;
}

Crgb OBJMaterial::getSpecularColor(){
  Crgb color;
  color.assign(Ks[0], Ks[1], Ks[2]);
  return color;
}


bool OBJMaterial::operator==(const string& name){
  return (this->name == name);
}

void OBJMaterial::toLxm(ostream& lxmFile){

  lxmFile << "# Material \'" << name << "\'" << endl;

  // déterminer le type de matériel - version temporaire
  if(isNull(Ks)) materialType = LXS_MATTE;
  else materialType = LXS_SUBSTRATE;
  if(!map_ka.empty() || !map_kd.empty() || !map_ks.empty()){// texture
    materialType = LXS_MATTE;
  }
  switch(materialType){
  case LXS_MATTE:
    lxmFile << "# Type : \'matte\' (Lambertian)" << endl;
    lxmFile << "Texture \"Kd-"<< name << "\" ";
    if(map_ka.empty() && map_kd.empty()){// pas de texture
      lxmFile << " \"color\" \"constant\" \"color value\" [";
      lxmFile << Kd[0 ]<< " " << Kd[1] << " " << Kd[2] <<"]"<<endl;  
      //       lxmFile << "Texture \"sigma-"<< name << "\" \"float\" \"constant\" ";
      //       lxmFile << "\"float value\" [0.0]"<< endl; 
    }else{// il y a une texture qu'on suppose diffuse
      lxmFile << " \"color\" \"imagemap\" \"string filename\" [";
      lxmFile << "\"";
      if(map_kd.empty()) lxmFile << map_ka; else lxmFile << map_kd;
      lxmFile << "\"] \"float vscale\" [-1.0]" << endl;
    }// else
    break;
  case LXS_SUBSTRATE : 
    lxmFile << "# Type : \'substrate\'" << endl;
    lxmFile << "Texture \"Kd-"<< name << "\" \"color\" \"constant\" ";
    lxmFile << "\"color value\" ["<<Kd[0]<<" "<<Kd[1]<<" "<<Kd[2]<<"]"<<endl;
    lxmFile << "Texture \"Ks-"<< name << "\" \"color\" \"constant\" ";
    lxmFile << "\"color value\" ["<<Ks[0]<<" "<<Ks[1]<<" "<<Ks[2]<<"]"<<endl;
    lxmFile << "Texture \"uroughness-" << name << "\" \"float\" \"constant\" ";
    lxmFile << "\"float value\" [0.001289]" << endl;
    lxmFile << "Texture \"vroughness-" << name << "\" \"float\" \"constant\" ";
    lxmFile << "\"float value\" [0.001289]" << endl;
    break;
  case LXS_MATTE_TEXTURE:
  default:
    lxmFile << "# Dummy Material \'Default\'" << endl;
    lxmFile << "Texture \"Kd-Default\" \"color\" \"constant\" ";
    lxmFile << "\"color value\" [0.5 0.5 0.5]" << endl;
    break;
  }// switch

  lxmFile << endl;
}

void OBJMaterial::toLxs(ostream& lxsFile){
  lxsFile << "Material ";
  switch(materialType){// initialisé lors d'un appel antérieur à toLxm
  case LXS_MATTE:
    lxsFile << "\"matte\" \"texture Kd\" \"Kd-" << name << "\" ";
//     lxsFile << "\"texture sigma\" \"sigma-" << name << "\"" <<endl;
    break;
  case LXS_SUBSTRATE:
    lxsFile << "\"substrate\" \"texture Kd\" \"Kd-" << name << "\" ";
    lxsFile << "\"texture Ks\" \"Ks-" << name << "\" ";
    lxsFile << "\"texture uroughness\" \"uroughness-" << name << "\" ";
    lxsFile << "\"texture vroughness\" \"vroughness-" << name << "\" " << endl;
    break;
  default:
    lxsFile << "\"matte\" \"texture Kd\" \"Kd-Default\"" << endl;
    break;
  }
  lxsFile << endl;
}

ostream& operator<<(ostream& out, const OBJMaterial& m){
  out << "materiau " << m.name << " :" << endl;
  out << " - Ka = (" << m.Ka[0] << "," <<  m.Ka[1] << "," <<  m.Ka[2] << ")" << endl;
  out << " - Kd = (" <<  m.Kd[0] << "," <<  m.Kd[1] << "," <<  m.Kd[2] << ")" << endl;
  out << " - Ks = (" <<  m.Ks[0] << "," <<  m.Ks[1] << "," <<  m.Ks[2] << ")" << endl;
  return out;
}
