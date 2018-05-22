/* OBJReader.hpp: interface for the COBJReader class.*/

#ifndef OBJREADER_H
#define OBJREADER_H

//#pragma warning(disable:4786)
//#pragma warning(disable:4243)

class OBJReader;

#include "../Cpoint.hpp"
#include "OBJGroupList.hpp"
#include "OBJMaterial.hpp"
#include "OBJLight.hpp"

#include <list>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

/** 
 * Classe pour la lecture d'un fichier OBJ et sa transformation en javacsript compatible webgl
 *
 * @author       Christophe Renaud
 * @date         30 mars 2009 - modifiée le 23 décembre 2011 pour js
 */
class OBJReader  
{

private:
  vector<Cpoint> pointlist;/**< Liste indexée de sommets.*/
  vector<Cvector> vecteurlist;/**< Liste indexée de Normales aux sommets.*/
  vector<Cpoint> texturelist;/**< Liste indexée de coordonnées de texture */

  list<string> mlist;/**< Liste des identifiants de matériaux.*/
  list<string>::iterator miter;/**< It&eacute;rateur sur la liste de identifiants*/

  list<OBJMaterial*> matlist;/**< Liste des matériaux.*/
  list<OBJMaterial*>::iterator matiter;/**< Itérateur sur la liste des matériaux.*/

  list<OBJLight *> srclist;/**<liste des sources */
  vector<Cpoint> srcVertices;/**<liste des sommets des sources surfaciques*/

  OBJGroupList gliste;/**< liste des groupes (au sens du format obj) constituant la géométrie de la scène */

  /**
   * Lit un fichier MTL passé en paramètre et importe les matériaux
   * dans la scène.
   * @param dataDirectory le répertoire dans lequel est stocké le fichier mtl
   * @param Filename le fichier au format MTL dans lequel sont décrits
   * les matériaux.
   * @param scene2ImportInto la scène dans laquelle insérer les matériaux.
   */
  void importMaterial(const char* dataDirectory, const char* Filename);

  /**
   * Lit un fichier de sources au format LIT pass&eacute; en paramètres 
   * et importe les sources dans la scène.
   * @param Filename le fichier au format LIT dans lequel sont décrites les sources.
   * @param scene2ImportInto la scène dans laquelle insérer les sources lues.
   *
   * Le format d'un fichier LIT, propre à IGLOO, est le suivant :
   * <ul>
   *   <li> \c newlight \a lightname : permet de nommer la source. Ce champ est \b obligatoire et doit être le premier à apparaître dans la définition d'une source.
   *   <li> \c category \a value : spécifie le type de source. A ce jour, les valeur possible pour \a value sont 0 (source ponctuelle) et 1 (source surfacique). Ce champ est \b obligatoire.
   *   <li> \c samplingrate \a value : nombre d'échantillons à lancer pour l'échantillonnage de l'éclairage direct de la source. \a value est une valeur entière strictement positive. En cas d'erreur ou d'abscence du membre, \a value est mise à 1 pour une source ponctuelle et à la valeur par défaut définie dans le fichier \c igloo.ini (champ \c DEFAULTSAMPLINGRATEONLIGHTSOURCE ).
   *   <li> \c intensity \a R \a V \a B : intensité de la source en mode RVB. Chaque composante est un nombre réel supérieur ou égal à 0. En cas d'abscence de ce champ, l'intensité par défaut est (0.0,0.0,0.0).
   * <li> \c g : termine la définition d'une source (utilisé pour compatibilité éventuelle avec le format obj). Ce champ est \b obligatoire. En cas d'abscence, la source correspondante n'est pas ajoutée à la scène.
   * </ul>
   * Les autres lignes du fichier dépendent du type de source.
   * <ul> 
   * <li> source de type \a ponctuelle : il faut ajouter le champ suivant
   *   <ul> 
   *     <li> \c position \a x \a y \a z : position de la source. En cas d'abscence, la source est positionnée en (0.0,0.0,0.0).
   *   </ul>
   * <li> source de type \a surfacique : plusieurs informations supplémentaires sont nécessaires pour définir la géométrie d'une source surfacique :
   *   <ul>
   *     <li> \c v \a x \a y \a z : définition d'un sommet, de coordonnées (x,y,z). Les sommets peuvent être définis à n'importe quel endroit dans le fichier mais doivent évidemment être définis avant d'être utilisés par une facette.
   *     <li> \c f \a s1 \a s2 \a s3 [ \a s4 ] : définition d'une facette, par énumération de la liste de ses sommets. Chaque sommet est identifié par son numéro dans la liste des sommets précédemment définis. La numérotation des sommets commence à 1 (compatibilité avec le format \c obj ). La classe ne prend en charge que des polygones à 3 ou 4 sommets. La définition d'une facette doit apparaître entre une commande \c newlight et une commande \c g.
   *   </ul>
   * </ul>
   */
  void importLight(const char* Filename);


public:
  /**
   * Constructeur par d&eacute;faut. 
   * Lit un fichier OBJ passé en paramètres et l'importe dans la scène.
   *
   * @param dataDirectory répertoire contenant les fichiers obj, mtl et lit.
   * @param filename nom du fichier OBJ &agrave; importer.
   * @param scene2ImportInto pointeur vers la scène dans laquelle
   * importer le fichier OBJ.
   */
  OBJReader(const string& dataDirectory,
	     const string&  filename);


  /**
   * Destructeur par d&eacute;faut.
   */
  ~OBJReader(){
    pointlist.clear();
    vecteurlist.clear();
    mlist.clear();
    matlist.clear();
    cout << "fin destructeur objreader " << endl;
  };

  /**
   * Fournit le nombre de groupes (au sens défini par le format obj) 
   * chargés par l'objet.
   * @return le nombre de groupes présents dans l'objet.
   */
  int getGroupNumber(){
    return gliste.size();
  }

  /**
   * Fournit un groupe spécifique.
   * @param i le numéro du groupe à retourner. Les indices commencent à 0
   * et se terminent à <code>getGroupNumber()-1</code>.
   * @return un pointeur vers le groupe d'indice <code>i</code> ou 
   * <code>NULL</code> si l'indice n'est pas valide.
   */
  OBJGroup* getGroup(int i){
    return gliste.getGroup(i);
  }

  void toLxs(ostream& lxsFile);

  void toJs(ostream& jsFile);

};

#endif 


