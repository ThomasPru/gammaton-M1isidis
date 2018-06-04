#include "pluie_gammatons.hpp"

pluie_gammatons::pluie_gammatons(int nb_rayons){
  float ks = 0.0;
  float kp = 0.0;
  float kf = 0.0;
  float sh = 0.0;
  float sd = 0.0;
  float sf = 0.0;

  Cvector v(0.0, -0.5, 0.5);
  
  for(int i = 0; i < nb_rayons; i++){
    Cpoint p((7*(float) rand() / RAND_MAX)*2-5, 3, -8*((float) rand() / RAND_MAX));
    
    CRay r(ks, kp, kf, sh, sd, sf, p, v);
    list_gam.push_back(r);
    //cout << "nombre de gammatons : " << list_gam.size() << endl;
  }
}

int pluie_gammatons::getSizeListGam(){
  return list_gam.size();
}

CRay pluie_gammatons::getListInd(int i){
  return list_gam[i];
}
