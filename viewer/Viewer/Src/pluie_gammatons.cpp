#include "pluie_gammatons.hpp"

pluie_gammatons::pluie_gammatons(int nb_rayons){
  float ks = 0.5;
  float kp = 0.5;
  float kf = 0.5;
  float sh = 0.5;
  float sd = 0.5;
  float sf = 0.5;

  Cvector v(0, -1, 0);
  
  for(int i = 0; i < nb_rayons; i++){
    Cpoint p(rand()%4-2, 5, rand()%4-2);
    
    CRay r = new CRay(ks, kp, kf, sh, sd, sf, p, v);
    list_gam.push_back(c);
  }
}

int pluie_gammatons::getSizeListGam(){
  return list_gam.size();
}
