#ifndef TON_HPP_
#define TON_HPP_

class ton{
private:
  //motion probabilities : straight line, parabolic curve, flowing
  float _ks, _kp, _kf;

  //Carrier attributes : humidity, amount of dirt, amount of fungus
  float _sh, _sd, _sf;

public:
  ton(float ks, float kp, float kf, float sh, float sd, float sf);
  
  float getStraightLine();
  float getParabolicCurve();
  float getFlowing();
  
  float getHumidity();
  float getAmountDirt();
  float getAmountFungus();
};

#endif
