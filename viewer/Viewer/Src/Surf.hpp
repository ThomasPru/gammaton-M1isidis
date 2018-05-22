#ifndef SURF_HPP_
#define SURF_HPP_

class Surf{
private:
  // ton-reflectance
  float _s, _p, _f;
  //material properties
  float _humidity, _dirt, _fungus;
public:
  Surf(float s, float p, float f, float humidity, float dirt, float fungus);
  float getS();
  float getP();
  float getF();
  float getHumidity();
  float getDirt();
  float getFungus();
};

#endif
