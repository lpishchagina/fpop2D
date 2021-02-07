#include <iostream>
#include <vector>

#include "Cost.h"

using namespace std;

//--------------constructor------------------------------------
Cost::Cost(){}

Cost::Cost(double free_c, unsigned int c){
  cnst = free_c;                              
  coef = c;                        
  mu = {0, 0};              
}
//--------------accessory------------------------------------
unsigned int Cost::get_coef () const {return coef;}
double Cost::get_cnst() const {return cnst;}
std::vector<double> Cost::get_mu(){return mu;}
std::vector<std::vector<double>> Cost::get_sy12(){return sy12;}
//--------------value_cost------------------------------------
double Cost::value_cost(double a1, double a2){
  double res = cnst + coef * ((a1 - mu[0])*(a1 - mu[0]) +(a2 - mu[1])*(a2 - mu[1])); 
  return res;
}
//--------------get_min------------------------------------
double Cost::get_min(){return(cnst);} // q_it is a paraboloid => min{q_it} = cnst
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

unsigned int Cost::value_coef(unsigned int i, unsigned int t){return  (t - i + 1);}

std::vector<double> Cost::value_mu(unsigned int i, unsigned int t, std::vector<double> si_1, std::vector<double> st){
  std::vector<double> res(2,0);
  res[0] = (1/(t - i + 1)) * (st[0] - si_1[0]);
  res[1] = (1/(t - i + 1)) * (st[1] - si_1[1]);
  return res;
}

double Cost::value_cnst( unsigned int i, unsigned int t, std::vector<double> si_1, std::vector<double> st,  std::vector<double> m, double mi_1, double beta){
  double res = (1/(t - i + 1)) * ((st[2] - si_1[2]) + (st[3] - si_1[3])) - m[0] * mu[0] - mu[1] * mu[2] + mi_1 + beta;
  return res;
}

//------------------------------------------------------------------------------