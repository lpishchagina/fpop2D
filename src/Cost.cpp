#include <iostream>
#include <vector>

#include "Cost.h"

using namespace std;

//--------------constructor------------------------------------
Cost::Cost(){}

Cost::Cost(double mi_1pen){   //start cost
  coef = 0;
  coef_Var = 0;
  mu1 = 0;
  mu2 = 0;
  mi_1_p = mi_1pen;
}

Cost::Cost(unsigned int i, unsigned int t, std::vector<std::vector< double >> vectS, double mi_1pen){
  coef = t -i + 1;
  mu1 = (1/(t - i + 1)) * (vectS[t][0] - vectS[i-1][0]);
  mu2 = (1/(t - i + 1)) * (vectS[t][1] - vectS[i-1][1]);
  coef_Var = (1/(t - i + 1)) * ((vectS[t][2] - vectS[i-1][2]) + (vectS[t][3] - vectS[i-1][3])) - mu1 * mu1 - mu2 * mu2;
  mi_1_p = mi_1pen;
}
//--------------accessory------------------------------------
unsigned int Cost::get_coef () const{return coef;}
double Cost::get_coef_Var() const{return coef_Var;}
double Cost::get_mi_1_p() const{return mi_1_p;}
double Cost::get_mu1(){return mu1;}
double Cost::get_mu2(){return mu2;}

//--------------value_cost------------------------------------
double Cost::value_cost(double a1, double a2){
  double res = mi_1_p + coef_Var + coef * ((a1 - mu1)*(a1 - mu1) +(a2 - mu2)*(a2 - mu2)); 
  return res;
}
//--------------get_min------------------------------------
double Cost::get_min(){return(coef_Var + mi_1_p);}// q_it is a paraboloid => min{q_it} = coef_Var + mi_1_penalty
