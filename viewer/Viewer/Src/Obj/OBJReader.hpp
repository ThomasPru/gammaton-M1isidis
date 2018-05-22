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
 * @date         30 mars 2009 - modifi�e le 23 d�cembre 2011 pour js
 */
class OBJReader  
{

private:
  vector<Cpoint> pointlist;/**< Liste index�e de sommets.*/
  vector<Cvector> vecteurlist;/**< Liste index�e de Normales aux sommets.*/
  vector<Cpoint> texturelist;/**< Liste index�e de coordonn�es de texture */

  list<string> mlist;/**< Liste des identifiants de mat�riaux.*/
  list<string>::iterator miter;/**< It&eacute;rateur sur la liste de identifiants*/

  list<OBJMaterial*> matlist;/**< Liste des mat�riaux.*/
  list<OBJMaterial*>::iterator matiter;/**< It�rateur sur la liste des mat�riaux.*/

  list<OBJLight *> srclist;/**<liste des sources */
  vector<Cpoint> srcVertices;/**<liste des sommets des sources surfaciques*/

  OBJGroupList gliste;/**< liste des groupes (au sens du format obj) constituant la g�om�trie de la sc�ne */

  /**
   * Lit un fichier MTL pass� en param�tre et importe les mat�riaux
   * dans la sc�ne.
   * @param dataDirectory le r�pertoire dans lequel est stock� le fichier mtl
   * @param Filename le fichier au format MTL dans lequel sont d�crits
   * les mat�riaux.
   * @param scene2ImportInto la sc�ne dans laquelle ins�rer les mat�riaux.
   */
  void importMaterial(const char* dataDirectory, const char* Filename);

  /**
   * Lit un fichier de sources au format LIT pass&eacute; en param�tres 
   * et importe les sources dans la sc�ne.
   * @param Filename le fichier au format LIT dans lequel sont d�crites les sources.
   * @param scene2ImportInto la sc�ne dans laquelle ins�rer les sources lues.
   *
   * Le format d'un fichier LIT, propre � IGLOO, est le suivant :
   * <ul>
   *   <li> \c newlight \a lightname : permet de nommer la source. Ce champ est \b obligatoire et doit �tre le premier � appara�tre dans la d�finition d'une source.
   *   <li> \c category \a value : sp�cifie le type de source. A ce jour, les valeur possible pour \a value sont 0 (source ponctuelle) et 1 (source surfacique). Ce champ est \b obligatoire.
   *   <li> \c samplingrate \a value : nombre d'�chantillons � lancer pour l'�chantillonnage de l'�clairage direct de la source. \a value est une valeur enti�re strictement positive. En cas d'erreur ou d'abscence du membre, \a value est mise � 1 pour une source ponctuelle et � la valeur par d�faut d�finie dans le fichier \c igloo.ini (champ \c DEFAULTSAMPLINGRATEONLIGHTSOURCE ).
   *   <li> \c intensity \a R \a V \a B : intensit� de la source en mode RVB. Chaque composante est un nombre r�el sup�rieur ou �gal � 0. En cas d'abscence de ce champ, l'intensit� par d�faut est (0.0,0.0,0.0).
   * <li> \c g : termine la d�finition d'une source (utilis� pour compatibilit� �ventuelle avec le format obj). Ce champ est \b obligatoire. En cas d'abscence, la source correspondante n'est pas ajout�e � la sc�ne.
   * </ul>
   * Les autres lignes du fichier d�pendent du type de source.
   * <ul> 
   * <li> source de type \a ponctuelle : il faut ajouter le champ suivant
   *   <ul> 
   *     <li> \c position \a x \a y \a z : position de la source. En cas d'abscence, la source est positionn�e en (0.0,0.0,0.0).
   *   </ul>
   * <li> source de type \a surfacique : plusieurs informations suppl�mentaires sont n�cessaires pour d�finir la g�om�trie d'une source surfacique :
   *   <ul>
   *     <li> \c v \a x \a y \a z : d�finition d'un sommet, de coordonn�es (x,y,z). Les sommets peuvent �tre d�finis � n'importe quel endroit dans le fichier mais doivent �videmment �tre d�finis avant d'�tre utilis�s par une facette.
   *     <li> \c f \a s1 \a s2 \a s3 [ \a s4 ] : d�finition d'une facette, par �num�ration de la liste de ses sommets. Chaque sommet est identifi� par son num�ro dans la liste des sommets pr�c�demment d�finis. La num�rotation des sommets commence � 1 (compatibilit� avec le format \c obj ). La classe ne prend en charge que des polygones � 3 ou 4 sommets. La d�finition d'une facette doit appara�tre entre une commande \c newlight et une commande \c g.
   *   </ul>
   * </ul>
   */
  void importLight(const char* Filename);


public:
  /**
   * Constructeur par d&eacute;faut. 
   * Lit un fichier OBJ pass� en param�tres et l'importe dans la sc�ne.
   *
   * @param dataDirectory r�pertoire contenant les fichiers obj, mtl et lit.
   * @param filename nom du fichier OBJ &agrave; importer.
   * @param scene2ImportInto pointeur vers la sc�ne dans laquelle
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
   * Fournit le nombre de groupes (au sens d�fini par le format obj) 
   * charg�s par l'objet.
   * @return le nombre de groupes pr�sents dans l'objet.
   */
  int getGroupNumber(){
    return gliste.size();
  }

  /**
   * Fournit un groupe sp�cifique.
   * @param i le num�ro du groupe � retourner. Les indices commencent � 0
   * et se terminent � <code>getGroupNumber()-1</code>.
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


