#ifndef COST_H
#define COST_H

#include <vector>

// q_it(theta1, theta2) = mi_1+penalty + (t - i + 1) * [(theta1 - E(y1_it))^2 + (theta2 - E(y2_it))^2] + (t - i + 1) * (Var(y1_it) + Var(y2_it))
//coef_Var = coef*(Var(y1_it) + Var(y2_it))
//mi_1_penalty =mi_1+penalty
//coef = (t - i + 1) 
//(mu1,mu2) = (E(y1_it), E(y2_it) )
// q_it = mi_1_penalty + coef * [(theta1 - mu1)^2 + (theta2 - mu2^2)] + coef_Var

class Cost{
public:
  //--------------constructor------------------------------------
  Cost();
  Cost(double K); // for minimum?
  //--------------accessory------------------------------------ 
  unsigned int get_coef() const;
  double get_coef_Var() const;
  double get_mi_1_penalty() const;
  double get_mu1();
  double get_mu2();
  std::vector<std::vector<double>> get_sy12();
  //--------------preprocessing------------------------------------
  std::vector<std::vector<double>> vect_sy12(std::vector<double>& y1, std::vector<double>& y2); //sum y1,y2, y1^2, y2^2
  unsigned int value_coef(unsigned int i, unsigned int t);
  double value_mu1(unsigned int i, unsigned int t, std::vector<double> si_1, std::vector<double> st);
  double value_mu2(unsigned int i, unsigned int t, std::vector<double> si_1, std::vector<double> st);
  double value_coef_Var( unsigned int i, unsigned int t, std::vector< double> si_1, std::vector< double> st,   double m1, double m2);
  
  //--------------value_cost------------------------------------
  double get_min();                          // q_it is a paraboloid => min{q_it} = coef_Var + mi_1_penalty
  double value_cost(double a1, double a2);   //q_it(a1, a2) 
 
private:
  unsigned int coef;    //(t - i + 1)
  double coef_Var;    //  coef * (Var(y1_it) + Var(y2_it))
  double mi_1_penalty; // mi_1 + penalty

  double mu1;                 //muj = E(yj_it), j =1,2
  double mu2;
  std::vector<std::vector< double >> sy12;  // vector sum y1,y2, y1^2, y2^2
};

#endif // COST_H