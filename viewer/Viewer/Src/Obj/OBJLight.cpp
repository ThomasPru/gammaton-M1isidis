#include "OBJLight.hpp"

OBJLight::OBJLight(char *name){
  this->name = string(name);
  type = UNKNOWN;
  samplingRate = 1;
}


void OBJLight::toLxs(ostream& lxsFile, const vector<Cpoint> &srcVertices){
  lxsFile << "AttributeBegin" << endl;

  switch(type){
  case OBJLight::POINTLIGHT: 
    lxsFile << "\tLightSource \"point\"" << endl;
    lxsFile << "\t\t\"point from\" [";
    lxsFile << position.x << " " << position.y << " " << position.z;
    lxsFile << " ] \"color L\" [ ";
    lxsFile << color.r << " " << color.g << " " << color.b;
    lxsFile << " ]" << endl;
    break;
  case OBJLight::AREALIGHT:{
    list <int> vertexIndice; // indice des sommets réellement utilisés
    for(int tri=0; tri<faces.size(); tri++)
      for(int som=0; som<3; som++)
	vertexIndice.push_back(faces[tri]->getVertex(som).getCoordinate());
    vertexIndice.sort();
    vertexIndice.unique();
    // la liste contient en un unique exemplaire la liste des indices
    // de sommet de triangle qui apparaissent dans la description
    // géométrique de la source surfacique. De plus ces sommets sont triés
    // par ordre croissant d'indice. Lorsqu'un indice est présent dans
    // un triangle, il suffit de trouver sa position dans la liste et de
    // sauver cette position comme indice local de la source.
    lxsFile << "\tAreaLightSource \"area\" ";
    lxsFile << "\"integer nsamples\" [" << samplingRate << "] ";
    lxsFile << "\"color L\" [";
    lxsFile << color.r << " " << color.g << " " << color.b << "]" << endl;
    lxsFile << "\tShape \"trianglemesh\" \"integer indices\" [" << endl;
    // export des indices locaux
    for(int tri=0; tri<faces.size(); tri++){
      lxsFile << "\t\t";
      for(int som=0; som<3; som++){
	int indice = faces[tri]->getVertex(som).getCoordinate();
	int indiceLocal=0;
	for(list<int>::iterator it=vertexIndice.begin();
	    it!=vertexIndice.end(); it++){
	  if(indice==*it) break;
	  indiceLocal++;
	}
	lxsFile << indiceLocal << " ";
      }
      lxsFile << endl;
    }

    // export des coordonnées de chaque sommet
    lxsFile << "\t] \"point P\" [" << endl;
    for(list<int>::iterator it=vertexIndice.begin();
	it!=vertexIndice.end(); it++){
      Cpoint p = srcVertices[*it];
      lxsFile << "\t\t" << p.x << " " << p.y << " " << p.z << endl;
    }
    lxsFile << "\t]" << endl;
    vertexIndice.clear();
    break;
  }
  default:
    lxsFile << "inconnue" << endl;
    break;
  }
  lxsFile << "AttributeEnd" << endl << endl;
}


ostream& operator<<(ostream& out, const OBJLight& t){
  out << "sources ";
  switch(t.type){
  case OBJLight::POINTLIGHT: 
    out << "ponctuelle de position (";
    out << t.position.x << ",";
    out << t.position.y << ",";
    out << t.position.z << ")";
    out << " couleur = " << t.color.r << "," << t.color.g << "," << t.color.b;
    break;
  case OBJLight::AREALIGHT:
    out << "surfacique composee des triangles suivants :" << endl;
    for(int i=0; i<t.faces.size(); i++)
      out << *(t.faces[i]) << endl;
    break;
  default:
    out << "inconnue" << endl;
    break;
  }
  return out;
}
