#include <iostream>
#include <vector>
#include "math.h"

#include "Cost.h"

using namespace std;

#include <Rcpp.h>
using namespace Rcpp;

//--------------constructor------------------------------------
Cost::Cost(){}

Cost::Cost(double mi_1pen){   //start cost
  coef = 1;
  coef_Var = 0;
  mu1 = 0;
  mu2 = 0;
  mi_1_p = mi_1pen;
}

Cost::Cost(unsigned int i, unsigned int t, double* si_1, double* st, double mi_1pen){
  coef = t -i + 1;
  mu1 = (1/(t - i + 1)) * (st[0] - si_1[0]);
  mu2 = (1/(t - i + 1)) * (st[1] - si_1[1]);
  coef_Var = (st[2] - si_1[2]) + (st[3] - si_1[3]) - coef * (mu1 + mu2) * (mu1 + mu2);
  mi_1_p = mi_1pen;
}
//--------------accessory------------------------------------
unsigned int Cost::get_coef() const{return coef;}
double Cost::get_coef_Var() const{return coef_Var;}
double Cost::get_mi_1_p() const{return mi_1_p;}
double Cost::get_mu1(){return mu1;}
double Cost::get_mu2(){return mu2;}
//---------------------------------------------------------
//--------------get_min------------------------------------
double Cost::get_min(){ return(coef_Var + mi_1_p);}// q_it is a paraboloid => min{q_it} = coef_Var + mi_1_penalty
