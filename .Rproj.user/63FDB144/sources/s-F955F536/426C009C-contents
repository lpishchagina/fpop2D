#ifndef OP_H
#define OP_H

#include <iostream>
#include <math.h>
#include <vector>

class OP{
public:
  //--------------constructor------------------------------------
  OP(){};
  OP(std::vector<double>& y1, std::vector<double>& y2, double beta);
  //--------------accessory------------------------------------
  std::vector< int > get_changepoints() const;
  std::vector< double > get_means1() const;
  std::vector< double > get_means2() const;
  double get_globalCost() const;
  unsigned int get_n() const;
  std::vector<std::vector<double>> get_sy12();
  //--------------preprocessing------------------------------------
  std::vector<std::vector<double>> vect_sy12(std::vector<double>& y1, std::vector<double>& y2);
  //--------------algoFPOP------------------------------------
  void algoFPOP(std::vector< double >& y1, std::vector< double >& y2, double beta, int type);
private:
  double penalty;
  unsigned int n;
  
  std::vector<std::vector<double>> sy12;  // vector sum y1,y2, y1^2, y2^2
  std::vector< int >last_changepoints;
  std::vector<double> m;//cost
  std::vector< int > changepoints; 
  std::vector< double > means1; 
  std::vector< double > means2;
  double globalCost;
  
};

#endif //OP_H