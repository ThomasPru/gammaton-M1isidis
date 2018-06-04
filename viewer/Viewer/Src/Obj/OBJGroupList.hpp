/* OBJGroup.hpp: interface for the OBJGroup class.*/

#ifndef OBJGROUPLIST_H
#define OBJGROUPLIST_H


#include "string.h"
#include "OBJGroup.hpp"

#include <list>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/** 
 * Classe permettant la gestion d'un ensemble de groupes de facettes,
 * au sens des groupes d�finis dans le format de fichier OBJ.
 *
 * @author       Christophe Renaud
 * @version	1.0.1
 * @since	1.0.3
 * @date         19 mai 2006 
 */
class OBJGroupList
{
private:
  vector<OBJGroup *> list; /**< liste des groupes appartenant � la liste*/

public:
  /**
   * Constructeur par d�faut.
   */
  OBJGroupList(){
  }


  /**
   * Destructeur par d�faut.
   */
  ~OBJGroupList(){
    for(unsigned int i=0; i<list.size(); i++) delete list[i];
    list.clear();
  }


  /**
   * Ajoute un groupe � la liste des groupes. 
   * @param g l'adresse du groupe � ajouter
   */
  inline void addGroup(OBJGroup* g){
    list.push_back(g);
  }

  inline int size() const{
    return list.size();
  }

  /**
   * Recherche le groupe dont le nom est pass� en param�tre.
   * @param name le nom du groupe � rechercher.
   * @return un pointeur vers le groupe correspondant, ou NULL
   * si le groupe n'existe pas.
   */
  OBJGroup* getGroup(char *name);

  /**
   * Retourne le groupe d'indice la valeur pass�e en param�tre.
   * @param i l'indice du groupe � retourner.
   * @return un pointeur vers le groupe correspondant, ou NULL
   * si le groupe n'existe pas.
   */
  OBJGroup* getGroup(int i);

  /**
   * Vide la liste de ses groupes.
   */
  inline void clear(){
    list.clear();
  }

  /** 
   * Ajoute une facette � tous les groupes qui composent la liste.
   * @param f la facette � ajouter.
   */
  void addFacet(OBJTriangle *f);

  /**
   * Envoi du contenu d'une liste de groupes sur un flot de sortie.
   * @param out le flot de sortie sur lequel l'�criture doit se faire
   * @param l la liste � �crire
   * @return le flot de sortie modifi� par l'�criture
   */
  friend ostream& operator<<(ostream& out, const OBJGroupList& l);

};

#endif 


