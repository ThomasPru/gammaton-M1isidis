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
 * d�finis dans le format de fichier OBJ.
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
  OBJMaterial *mat; /**< materiau commun � toutes les facettes */
public:
  /**
   * Constructeur par d�faut. Le nom est initialis� � "NULL".
   */
  OBJGroup(){
    name = "";
    mat=NULL;
  }
  /**
   * Constructeur param�trique. Un groupe vide de nom <code>name</code>
   * est cr��.
   * @param name le nom du groupe � cr�er.
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
   * Destructeur par d�faut.
   */
  ~OBJGroup();

  /**
   * M�thode permettant de comparer le nom du groupe � un nom pass� en 
   * param�tre.
   * @param name le nom � tester
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
   * Ajoute une facette � la liste des facettes appartenant au groupe.
   * @param f l'adresse de la facette � ajouter
   */
  inline void addFacet(OBJTriangle* f){
    facets.push_back(f);
  }

  /**
   * Fournit le nombre de facettes g�r�es par le groupe.
   * @return le nombre de facettes g�r�es par le groupe.
   */
  int size(){ return facets.size(); }

  /**
   * Fournit une facette sp�cifique du groupe.
   * @param i le num�ro de la facette � renvoyer
   * @return un pointeur vers la facette demand�e ou <code>NULL</code> 
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


