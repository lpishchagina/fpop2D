#ifndef COST_H
#define COST_H

#include <math.h>

class Cost
{
public:
  Cost();
  
  //value of the cost function on the interval [a, b]
  double Cost_ab(unsigned int& a, unsigned int& b, double* ka_1, double* kb);  
};

#endif // COST_H