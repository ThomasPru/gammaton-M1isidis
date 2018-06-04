#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <stdio.h>

extern float angle_rotX;
extern float angle_rotY;
extern float trans_axeZ;

void gerer_clavier(unsigned char touche, int x, int y)
{

  switch(touche){

  case '8':
    angle_rotX -= 10.0; break;
  case '2':
    angle_rotX += 10.0; break;
  case '4':
    angle_rotY -= 10.0; break;
  case '6':
    angle_rotY += 10.0; break;
  case '+':
    trans_axeZ += 1.0; break;
  case '-':
    trans_axeZ -= 1.0; break;
 
  }

  glutPostRedisplay();
}


