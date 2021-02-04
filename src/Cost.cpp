#include"Cost.h"
#include <iostream>
#include <math.h>
Cost::Cost(){}

//c(yt,yT) = (-1)/(T-t+1)*((Sum(y1t_y1T)^2 + (Sum(y2t_y2T)^2) + Sum(y1t^2+y2t^2_y1T^2+y2T^2)
double Cost::Cost_ab(unsigned int& a, unsigned int& b,  double* ka_1, double* kb)
{
  double res = (-1)*((kb[0]-ka_1[0])*(kb[0]-ka_1[0]) + (kb[1]-ka_1[1])*(kb[1]-ka_1[1]))/(b - a + 1) + (kb[2] - ka_1[2]);
  return (res);
}