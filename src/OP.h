#ifndef OP_H
#define OP_H

#include "Geom.h"
#include "Disk.h"
#include "Rect.h"
#include "Cost.h"

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include "Rcpp.h"

//##############################################################################//
//###############################Class OP#######################################//
class OP{
public:
//------------------------------constructor-------------------------------------//
  OP(){};
  OP(std::vector<double>& y1, std::vector<double>& y2, double beta);
//---------------------------------destructor-----------------------------------//
  ~OP();
//---------------------------------accessory------------------------------------//
  std::vector<unsigned int> get_changepoints() const;
  std::vector<double> get_means1() const;
  std::vector<double> get_means2() const;
  double get_globalCost() const;
  unsigned int get_n() const;
  double** get_sy12();
//------------------------------vect_sy12---------------------------------------//
  double** vect_sy12(std::vector<double>& y1, std::vector<double>& y2);
//-------------------------------algoFPOP---------------------------------------//
  void algoFPOP(std::vector<double>& y1, std::vector<double>& y2, int type);
  
private:
  double penalty;                                       //value of penalty 
  unsigned int n;                                       // data length
  double** sy12;                                        // vector sum y1,y2, y1^2, y2^2
  std::vector<unsigned int> changepoints;               // changepoints vector 
  std::vector<double> means1;                           // means vector for y1
  std::vector<double> means2;                           // means vector for y2        
  double globalCost;                                    // value of global cost 
};
//#############################End Class OP#####################################//
#endif //OP_H