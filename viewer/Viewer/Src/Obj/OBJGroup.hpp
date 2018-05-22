/* OBJGroup.hpp: interface for the OBJGroup class.*/

#ifndef OBJGROUP_H
#define OBJGROUP_H


#include "string.h"
#include "OBJTriangle.hpp"
#include "OBJMaterial.hpp"
#include "../Cpoint.hpp"
#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/** 
 * Classe permettant la gestion d'un groupe de facettes au sens des groupes
 * définis dans le format de fichier OBJ.
 *
 * @author       Christophe Renaud
 * @version	1.0.1
 * @since	1.0.3
 * @date         13 mai 2006 
 */
class OBJGroup
{
private:
  string name; /**< nom du groupe */
  vector<OBJTriangle*> facets; /**< liste des facettes appartenant au groupe*/
  OBJMaterial *mat; /**< materiau commun à toutes les facettes */
public:
  /**
   * Constructeur par défaut. Le nom est initialisé à "NULL".
   */
  OBJGroup(){
    name = "";
    mat=NULL;
  }
  /**
   * Constructeur paramétrique. Un groupe vide de nom <code>name</code>
   * est créé.
   * @param name le nom du groupe à créer.
   */
  OBJGroup(char *name){
    this->name = string(name);
    mat = NULL;
  }

  OBJGroup(const string& name){
    this->name = name;
    mat = NULL;
  }

  /**
   * Destructeur par défaut.
   */
  ~OBJGroup();

  /**
   * Méthode permettant de comparer le nom du groupe à un nom passé en 
   * paramètre.
   * @param name le nom à tester
   * @return true si <code>name</code> correspond au nom du groupe, false sinon
   */
  inline bool nameIs(char *name) const{
    return (this->name==string(name));
  }

  /**
   * Fournit le nom du groupe au sens du format obj.
   * @return le nom du groupe.
   */
  inline string getName(){
    return name;

  }
  /**
   * Ajoute une facette à la liste des facettes appartenant au groupe.
   * @param f l'adresse de la facette à ajouter
   */
  inline void addFacet(OBJTriangle* f){
    facets.push_back(f);
  }

  /**
   * Fournit le nombre de facettes gérées par le groupe.
   * @return le nombre de facettes gérées par le groupe.
   */
  int size(){ return facets.size(); }

  /**
   * Fournit une facette spécifique du groupe.
   * @param i le numéro de la facette à renvoyer
   * @return un pointeur vers la facette demandée ou <code>NULL</code> 
   * si l'indice n'est pas valide.
   */
  OBJTriangle* getFacet(int i);


  void setMaterial(OBJMaterial *m){
    mat = m;
  }




  OBJMaterial getMaterial();

  void toLxs(ostream& lxsFile, 
	     const vector <Cpoint> &pointList,
	     const vector <Cvector> &vecteurList,
	     const vector <Cpoint> &textureList);

  void toJs(ostream& jsFile, 
	    const vector <Cpoint> &pointList,
	    const vector <Cvector> &vecteurList,
	    const vector <Cpoint> &textureList,
	    const bool last);




  friend ostream& operator<<(ostream& out, const OBJGroup& g);

};

#endif 


