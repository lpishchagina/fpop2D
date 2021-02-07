#ifndef COST_H
#define COST_H

#include <vector>

// q_it(theta1, theta2) = mi_1+penalty + (t - i + 1) * [(theta1 - E(y1_it))^2 + (theta2 - E(y2_it))^2] + (t - i + 1) * (Var(y1_it) + Var(y2_it))
//cnst = mi_1 + penalty + K*(Var(y1_it) + Var(y2_it))
//coef = (t - i + 1) 
//mu = (E(y1_it), E(y2_it) )
// q_it(theta1, theta2) = cnst + coef * [(theta1 - mu[1])^2 + (theta2 - mu[2]^2]

class Cost{
public:
  //--------------constructor------------------------------------
  Cost();
  Cost(double cnst, unsigned int coef);
  //--------------accessory------------------------------------ 
  unsigned int get_coef() const;
  double get_cnst() const;
  std::vector<double> get_mu();
  std::vector<std::vector<double>> get_sy12();
  //--------------preprocessing------------------------------------
  std::vector<std::vector<double>> vect_sy12(std::vector<double>& y1, std::vector<double>& y2); //sum y1,y2, y1^2, y2^2
  unsigned int value_coef(unsigned int i, unsigned int t);
  std::vector<double> value_mu(unsigned int i, unsigned int t, std::vector<double> si_1, std::vector<double> st);
  double value_cnst( unsigned int i, unsigned int t, std::vector< double> si_1, std::vector< double> st,  std::vector<double> m, double mi_1, double beta);
  
  //--------------value_cost------------------------------------
  double get_min();                          // q_it is a paraboloid => min{q_it} = cnst
  double value_cost(double a1, double a2);   //q_it(a1, a2) 
 
private:
  double cnst;                              // cnst = mi_1 + penalty + K*(Var(y1_it) + Var(y2_it))
  unsigned int coef;                        //coef = (t - i + 1) 
  std::vector<double> mu;                 //mu[J] = E(yj_it), j =1,2
  std::vector<std::vector< double >> sy12;  // vector sum y1,y2, y1^2, y2^2
};

#endif // COST_H