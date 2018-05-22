#ifndef _CRGB_HPP
#define _CRGB_HPP

class Crgb {
public:
  float r, g, b;

  Crgb(){ r=g=b=0;}
  Crgb(float r, float g, float b){
    this->r = r; this->g = g; this->b = b;
  }

  void assign(float r, float g, float b){
    this->r = r; this->g = g; this->b = b;
  }
};
#endif
