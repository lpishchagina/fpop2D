#include <iostream>
#include <vector>

#include "Cost.h"

using namespace std;

//--------------constructor------------------------------------
Cost::Cost(){}

Cost::Cost(double K){   //
  coef = 0;
  coef_Var = 0;
  mu1 = 0;
  mu2 = 0;
  mi_1_penalty = K;
}
//--------------accessory------------------------------------
unsigned int Cost::get_coef () const{return coef;}
double Cost::get_coef_Var() const{return coef_Var;}
double Cost::get_mi_1_penalty() const{return mi_1_penalty;}
double Cost::get_mu1(){return mu1;}
double Cost::get_mu2(){return mu2;}
std::vector<std::vector<double>> Cost::get_sy12(){return sy12;}
//--------------value_cost------------------------------------
double Cost::value_cost(double a1, double a2){
  double res = mi_1_penalty + coef_Var + coef * ((a1 - mu1)*(a1 - mu1) +(a2 - mu2)*(a2 - mu2)); 
  return res;
}
//--------------get_min------------------------------------
double Cost::get_min(){return(coef_Var + mi_1_penalty);}// q_it is a paraboloid => min{q_it} = coef_Var + mi_1_penalty
//--------------preprocessing------------------------------------
std::vector<std::vector<double>> Cost::vect_sy12(std::vector<double>& y1, std::vector<double>& y2){
  unsigned int n = y1.size();
  sy12[0][0] = 0;
  sy12[0][1] = 0;
  sy12[0][2] = 0;
  sy12[0][3] = 0;
  for (unsigned int j = 1; j < (n + 1); j++){
    sy12[j][0] = sy12[j-1][0] + y1[j-1];
    sy12[j][1] = sy12[j-1][1] + y2[j-1];
    sy12[j][2] = sy12[j-1][2] + y1[j-1] * y1[j-1];
    sy12[j][2] = sy12[j-1][2] + y2[j-1] * y2[j-1];
  }
  return(sy12); 
}
//--------------value_coef------------------------------------
unsigned int Cost::value_coef(unsigned int i, unsigned int t){return  (t - i + 1);}

double Cost::value_mu1(unsigned int i, unsigned int t, std::vector<double> si_1, std::vector<double> st){
  double res = (1/(t - i + 1)) * (st[0] - si_1[0]);
  return res;
}
double Cost::value_mu2(unsigned int i, unsigned int t, std::vector<double> si_1, std::vector<double> st){
  double res = (1/(t - i + 1)) * (st[1] - si_1[1]);
  return res;
}
double Cost::value_coef_Var( unsigned int i, unsigned int t, std::vector<double> si_1, std::vector<double> st, double m1, double m2){
  double res = (1/(t - i + 1)) * ((st[2] - si_1[2]) + (st[3] - si_1[3])) - m1 * m1 - m2 * m2;
  return res;
}
//------------------------------------------------------------------------------