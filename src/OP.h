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

class OP{
public:
  //--------------constructor------------------------------------
  OP(){};
  OP(std::vector<double>& y1, std::vector<double>& y2, double beta);
  ~OP();
  //--------------accessory------------------------------------
  std::vector< int > get_last_chpts() const;
  std::vector< double > get_means1() const;
  std::vector< double > get_means2() const;
  double get_globalCost() const;
  unsigned int get_n() const;
  double** get_sy12();
  //--------------preprocessing------------------------------------
  double** vect_sy12(std::vector<double>& y1, std::vector<double>& y2);
  //--------------backtracking------------------------------------
 // void backtracking(int ndata);
  //--------------algoFPOP------------------------------------
  void algoFPOP(std::vector< double >& y1, std::vector< double >& y2, int type);
  
private:
  double penalty;
  unsigned int n;
  
  double** sy12;  // vector sum y1,y2, y1^2, y2^2
  std::vector< double > means1; 
  std::vector< double > means2;
  double globalCost;
  std::vector< int >last_chpts;
  
};

#endif //OP_H