#ifndef _CPOINT_HPP
#define _CPOINT_HPP

#include <iostream>
using namespace std;

/** Classe permettant la représentation d'un point 3D, inspirée
 * de la classe Cpoint du sdk maxwell
 */
class Cpoint
{
public:
  double x, y, z;

  Cpoint(){ x = y = z = 0.0;}

  Cpoint(float vx, float vy, float vz )
  {
    x = vx;
    y = vy;
    z = vz;
  }

  void  setZero(){ x = y = z = 0.0;}

  //-----------------------
  //----accesseurs
  double getX() const;

  double getY() const;

  double getZ() const;
  
  //----------------------

  
  // ASSIGN //

  void assign( float vx, float vy, float vz )
  {
    x = vx;
    y = vy;
    z = vz;
  }

  void assign( const Cpoint &v )
  {
    x = v.x;
    y = v.y;
    z = v.z;
  }

  // COMPARE //

  bool operator < ( const Cpoint &v )
  {
    return ( x < v.x || ( x == v.x && ( y < v.y || ( y == v.y && z < v.z ) ) ) );
  }

  bool operator > ( const Cpoint &v )
  {
    return ( x > v.x || ( x == v.x && ( y > v.y || ( y == v.y && z > v.z ) ) ) );
  }

  bool operator == ( const Cpoint &v )
  {
    return ( x == v.x && y == v.y && z == v.z );
  }

  friend ostream& operator<<(ostream& out, const Cpoint& p);

};


//typedef Cpoint  Cvector ;
#endif
