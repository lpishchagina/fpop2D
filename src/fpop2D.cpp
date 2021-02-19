#include "OP.h"
#include "Geom.h"
#include "Disk.h"
#include "Rect.h"
#include "Cost.h"
#include "math.h"

#include <Rcpp.h>
using namespace Rcpp;
using namespace std;

//' @title FPOP2D 
//'                                                                                                        
//' @description Detecting changepoints using the functional pruning optimal partitioning method (fpop) in bivariate time series.                         
//'                                                                                                       
//' @param data1 is a vector of data1(a univariate time series).                                
//' @param data2 is a vector of data2(a univariate time series).                                
//' @param penalty is a value of penalty (a non-negative real number).                                        
//' @param type is a value defining the  type of pruning (0 = PELT, 1 = intersection set, 2 = difference of intersection and union set ).       
//'                                                                                                          
//' @return a list of 4 elements  = (changepoints, means1, means2, globalCost).                    
//'  
//' \describe{
//' \item{\code{changepoints}}{is the vector of changepoints.}
//' \item{\code{means1}}{is the vector of successive means for data1.}
//' \item{\code{means2}}{is the vector of successive means for data2.}
//' \item{\code{globalCost}}{is a number equal to the global cost.}
//' }                                                                                                                                                                             #     
//'             
//' @examples FPOP2D (data1 = c(0,0,0,1,1,1), data2 = c(2,2,2,0,0,0), penalty = 2*log(6),  type = 1) 
// [[Rcpp::export]]
List FPOP2D(std::vector<double> data1, std::vector<double> data2, double penalty, int type) {
  //----------stop--------------------------------------------------------------
  if(data1.size() != data2.size()){throw std::range_error("data1 and data2 have different length");}
  if(penalty < 0) {throw std::range_error("penalty should be a non-negative number");}
  if(type < 0 || type > 2)
  {throw std::range_error("type must be one of: 0, 1 or 2");}
  //----------------------------------------------------------------------------
 
  OP Y = OP(data1, data2, penalty);
  
  Y.algoFPOP(data1, data2, type);     //FPOP algorithm: type of pruning  = intersection
  
  List res;
  res["changepoints"] = Y.get_changepoints();
  res["means1"] = Y.get_means1();
  res["means2"] = Y.get_means2();
  res["globalCost"] = Y.get_globalCost();
  
  return res;
}
