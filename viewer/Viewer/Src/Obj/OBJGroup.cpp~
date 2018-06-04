#include "OBJGroup.hpp"
#include <algorithm>

OBJGroup::~OBJGroup(){
  for(int i=0; i<facets.size(); i++) delete facets[i];
  facets.clear();
  // delete mat; ne pas effacer car apprtient à la liste des matériaux
}


OBJTriangle* OBJGroup::getFacet(int i){
  return facets[i];
}

OBJMaterial OBJGroup::getMaterial(){
  return *mat;
}

void OBJGroup::toLxs(ostream& lxsFile, 
		     const vector <Cpoint> &pointList,
		     const vector <Cvector> &vecteurList,
		     const vector <Cpoint> &textureList){
  vector <int> localIndice; // indices locaux des sommets
  vector <OBJVertex> localVertex;// liste locale des sommets (unicité de chaque sommet)

  // cas des g isolé dans le fichier obj
  if(facets.size()==0) return;

  cout << "   groupe (" << name << ")";
  cout << facets.size() << "facettes" << endl;

  // initialisation des deux listes locales
  for(int i=0; i<facets.size(); i++){

    if(i%1000==0)
      cout << i << "    facettes traitées (" << 100*i/facets.size() << "%)" << endl;
    for(int s=0; s<3; s++){
      OBJVertex v = facets[i]->getVertex(s);
      int indice = -1;
      // recherche de l'existence du sommet dans la liste locale
      for(int is=0; is<localVertex.size(); is++){
	if(v==localVertex[is]){ indice = is; break;}
      }
      if(indice<0){
	localVertex.push_back(v);
	indice = localVertex.size()-1;
      }
      // mise à jour de la liste des indices
      localIndice.push_back(indice);
    }
  }

  // export au format LXS
  
    // (0) Entête de l'objet
    lxsFile << "AttributeBegin" << endl;

    // (0.1) - matériau de l'objet
    mat->toLxs(lxsFile);

    lxsFile << "Shape \"trianglemesh\" \"integer indices\" [" << endl; 

    // (1) liste des facettes = triplets d'indice de sommets
    // dans la liste locale
    int il=0; // indice dans le vecteur local d'indice
    for(int i=0; i<facets.size(); i++){
      
      lxsFile << "  "; // indentation des données
      lxsFile << localIndice[il] << " ";
      lxsFile << localIndice[il+1] << " ";
      lxsFile << localIndice[il+2] << endl;
      il+=3;

    }
    // fermer le trianglemesh
    lxsFile << "] ";

    // (2) ajout des sommets au mesh

    lxsFile << "\"point P\" [" << endl;
    for(int i=0; i<localVertex.size(); i++){
      Cpoint p = pointList[localVertex[i].getCoordinate()];
      lxsFile << "  " << p.x << " " << p.y << " " << p.z << endl;
    }
    lxsFile << "] ";

    // (3) ajout des normales au mesh
    lxsFile << "\"normal N\" [" << endl;
    for(int i=0; i<localVertex.size(); i++){
      Cvector p = vecteurList[localVertex[i].getNormal()];
      lxsFile << "  " <<p.x << " " << p.y << " " << p.z << endl;
    }
    lxsFile << "] ";

    // (4) RAJOUTER LES TEXTURES SI ELLES EXISTENT
    if(mat->isTextured()){
      lxsFile << "\"float uv\" [" << endl;
      for(int i=0; i<localVertex.size(); i++){
	Cpoint p = textureList[localVertex[i].getTexture()];
	// le signe de p.y (v dans le repère de texture uv) est inversé
	// car il semble que le repère de texture de luxrender inverse
	// cette coordonnées ??? - remis à la bonne valeur, l'inversion
	// étant incluse dans le matériau 
	lxsFile << "  " << p.x << " " << p.y << endl;
      }
      lxsFile << "] ";
    }

    lxsFile << endl;
    // (5) refermer le groupe
    lxsFile << "AttributeEnd" << endl;

}

void OBJGroup::toJs(ostream& jsFile, 
		    const vector <Cpoint> &pointList,
		    const vector <Cvector> &vecteurList,
		    const vector <Cpoint> &textureList,
		    const bool last){
  vector <int> localIndice; // indices locaux des sommets
  vector <OBJVertex> localVertex;// liste locale des sommets (unicité de chaque sommet)
  // cas des g isolé dans le fichier obj
  if(facets.size()==0) return;

  cout << "   groupe (" << name << ")";
  cout << facets.size() << "facettes" << endl;

  for(int i=0; i<facets.size(); i++){
    for(int s=0; s<3; s++){
      if(s==0) jsFile << "\t";
      jsFile << facets[i]->getVertex(s).getCoordinate();
      if(s!=2) jsFile << ",";
      else if(!last) jsFile << "," << endl;
      else jsFile << endl;
    }
  }

}

ostream& operator<<(ostream& out, const OBJGroup& g){
  out << "groupe " << g.name << " de taille " << g.facets.size() << endl;
  out << "materiau : " << *(g.mat) << endl;
  for(int i=0; i<g.facets.size(); i++)
    cout << *(g.facets[i]) << endl;
  return out;
}
