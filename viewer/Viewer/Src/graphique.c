#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>

#include <iostream>
#include "Obj/OBJReader.hpp"

//------------------
extern float angle_rotX;
extern float angle_rotY;
extern float trans_axeZ;

extern OBJReader r;

/** 
 * Fonction permettant de dessiner un cube centré sur l'origine 
 * du repère de de taille dimxdimxdim.
 * @param dim la taille du côté du cube.
 */

static void cube(float dim)
{
  glBegin(GL_QUADS);
  /* face avant rouge */
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-dim/2, -dim/2, dim/2);
  glVertex3f( dim/2, -dim/2, dim/2);
  glVertex3f( dim/2,  dim/2, dim/2);
  glVertex3f(-dim/2,  dim/2, dim/2);
  
  /* face droite verte */
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(dim/2, -dim/2, dim/2);
  glVertex3f(dim/2, -dim/2, -dim/2);
  glVertex3f(dim/2,  dim/2, -dim/2);
  glVertex3f(dim/2,  dim/2, dim/2);

  /* face gauche jaune */
  glColor3f(1.0, 1.0, 0.0);
  glVertex3f(-dim/2, -dim/2, dim/2);
  glVertex3f(-dim/2,  dim/2, dim/2);
  glVertex3f(-dim/2,  dim/2, -dim/2);
  glVertex3f(-dim/2, -dim/2, -dim/2);

  /* face arriere blanche */
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(-dim/2, -dim/2, -dim/2);
  glVertex3f(-dim/2,  dim/2, -dim/2);
  glVertex3f( dim/2,  dim/2, -dim/2);
  glVertex3f( dim/2, -dim/2, -dim/2);

  /* face superieure cyan */
  glColor3f(0.0, 1.0, 1.0);
  glVertex3f(-dim/2, dim/2, dim/2);
  glVertex3f( dim/2, dim/2, dim/2);
  glVertex3f( dim/2, dim/2, -dim/2);
  glVertex3f(-dim/2, dim/2, -dim/2);

  /* face inferieure magenta */
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(-dim/2, -dim/2, dim/2);
  glVertex3f(-dim/2, -dim/2, -dim/2);
  glVertex3f( dim/2, -dim/2, -dim/2);
  glVertex3f( dim/2, -dim/2, dim/2);

  glEnd();
}




/** 
 * Fonction permettant de dessiner le repère du monde sous 
 * forme d'une croix 3D.
 * @param dim la taille de la ligne représentant un demi-axe.
 */

static void repere(float dim)
{

  glBegin(GL_LINES);
 
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(-dim, 0.0, 0.0);
  glVertex3f( dim, 0.0, 0.0);
  glVertex3f(0.0,-dim, 0.0);
  glVertex3f(0.0, dim, 0.0);
  glVertex3f(0.0, 0.0, -dim);
  glVertex3f(0.0, 0.0,  dim);

  glEnd();
}



/**
 * Fonction utilisée pour afficher le monde 3D à visualiser. Cette fonction
 * sera appelée à chaque fois qu'un "rafraichissement" de la fenêtre
 * d'affichage sera nécessaire.
 */

void dessiner(void)
{
  
  /* effacer l'ecran */
  glClearColor(0.0, 0.0, 0.0, 1.0);

  /* raz de la fenetre avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* dessin des objets */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, trans_axeZ);
  glRotatef(angle_rotX, 1.0, 0.0, 0.0);
  glRotatef(angle_rotY, 0.0, 1.0, 0.0);
  //cube(2.0);
  r.drawScene();
  
  repere(2.0);
  
  glFlush();
  return;

}
