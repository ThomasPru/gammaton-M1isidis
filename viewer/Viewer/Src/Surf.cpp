#include "Surf.hpp"

Surf::Surf(float s, float p, float f, float humidity, float dirt, float fungus){
  _s = s;
  _p = p;
  _f = f;

  _humidity = humidity;
  _dirt = dirt;
  _fungus = fungus;
}


float Surf::getS(){
  return _s;
}

float Surf::getP(){
  return _p;
}

float Surf::getF(){
  return _f;
}

float Surf::getHumidity(){
  return _humidity;
}

float Surf::getDirt(){
  return _dirt;
}

float Surf::getFungus(){
  return _fungus;
}
