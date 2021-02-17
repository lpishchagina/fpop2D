#include "OP.h"
#include "Geom.h"
#include "Disk.h"
#include "Rect.h"
#include "Cost.h"
#include "math.h"

#include <iostream>

using namespace std;

#include <Rcpp.h>
using namespace Rcpp;

//##############################constructor#####################################//
OP::OP(std::vector<double>& y1, std::vector<double>& y2, double beta){
  penalty = beta;
  n = y1.size();
  sy12 = new double*[n+1]; 
  for(unsigned int i = 0; i < n+1; i++) {sy12[i] = new double[4];}
}

//##############################destructor######################################//
OP::~OP(){
  for(unsigned int i = 0; i < n+1; i++) {delete(sy12[i]);}
  delete [] sy12;
  sy12 = NULL;
}

//##############################accessory#######################################//
std::vector< unsigned int > OP::get_changepoints() const {return changepoints;}
std::vector< double > OP::get_means1() const{return means1;}
std::vector< double > OP::get_means2() const{return means2;}
double OP::get_globalCost() const {return globalCost;}
unsigned int OP::get_n() const {return n;}
double** OP::get_sy12() {return sy12;}

//##############################vect_sy12#######################################//
double** OP::vect_sy12(std::vector<double>& y1, std::vector<double>& y2){
  unsigned int n = y1.size();
  sy12[0][0] = 0;
  sy12[0][1] = 0;
  sy12[0][2] = 0;
  sy12[0][3] = 0;
  for (unsigned int j = 1; j < (n + 1); j++){
    sy12[j][0] = sy12[j - 1][0] + y1[j - 1];
    sy12[j][1] = sy12[j - 1][1] + y2[j - 1];
    sy12[j][2] = sy12[j - 1][2] + y1[j - 1] * y1[j - 1];
    sy12[j][3] = sy12[j - 1][3] + y2[j - 1] * y2[j - 1];
  }
  return(sy12);
}

//###############################algoFPOP#######################################//
void OP::algoFPOP(std::vector< double >& y1, std::vector< double >& y2, int type){
  //-------------------------preprocessing-------------------------------------
  n = y1.size();
  sy12 = vect_sy12(y1, y2);           
  
  double* m = new double[n + 1];        // "globalCost" = m[n+1] - changepoints.size()*penalty 
  m[0] = 0;
  double** last_chpt_mean = new double*[3];         // vectors of best last changepoints, mean1 and mean2
  for(unsigned int i = 0; i < 3; i++) {last_chpt_mean[i] = new double[n];}
  
  std::list<Geom> list_geom;                        //list of geom
  std::list<Geom> ::iterator it_list;               // iterator for list of geom 
 
  Geom geom_activ;
  Cost cost_activ;
  
  //-------------------------Algorithm------------------------------------------ 
  for (unsigned int t = 0; t < n ; t++){
    Rcpp::Rcout << "create new Dtt" << std::endl;
    geom_activ = Geom(t); 
    list_geom.push_back(geom_activ);
    double min_val = INFINITY;                      //min value of cost
    double mean1;                                   //means for (lbl, t)
    double mean2; 
    unsigned int lbl;                               //best last position for t
    //-----------------First run: search min------------------------------------
    it_list = list_geom.begin();
    while(it_list != list_geom.end()){
      geom_activ = *it_list;
      unsigned int u = geom_activ.get_label_t();
      cost_activ = Cost(u, t, sy12[u], sy12[t + 1], m[u]);
      if(cost_activ.get_min() < min_val){
        lbl = u;
        min_val = cost_activ.get_min();
        mean1 = cost_activ.get_mu1();
        mean2 = cost_activ.get_mu2();  
      }
      ++it_list;
    }
    
    last_chpt_mean[0][t] = lbl;       //last_chpt_mean[0] - vector of best last chpt
    last_chpt_mean[1][t] = mean1;     //last_chpt_mean[1] - vector of means (lbl,t) for y1
    last_chpt_mean[2][t] = mean2;     //last_chpt_mean[2] - vector of means (lbl,t) for y2
    
    m[t + 1] = min_val + penalty;     // new min        
   
    
    //------------------Second run: pruning------------------------------------- 
    
    //------------------type = 1 pruning "intersection"-------------------------
    if (type == 1){
      ////////////////////////////
      Rcpp::Rcout << "geom_activ.get_label_t()" << std::endl;
      it_list = list_geom.begin();
      while( it_list != list_geom.end() )
      {
        geom_activ = *it_list;
        Rcpp::Rcout << geom_activ.get_label_t() << std::endl;
        ++it_list;
      }
      ///////////////////////////
      it_list = list_geom.begin();
      
      while (it_list != list_geom.end()){
        
        double r_new;           //radius
        Disk disk_new;
        
        geom_activ = *it_list;
        lbl = geom_activ.get_label_t();
        
        cost_activ = Cost(lbl, t, sy12[lbl], sy12[t + 1], m[lbl]);
        
        // find radius
        double r2 = (m[t + 1] - m[lbl] - cost_activ.get_coef_Var())/cost_activ.get_coef(); 
        
        //////////////////////////////////
        Rcpp::Rcout << "r2" << std::endl;
        Rcpp::Rcout << r2 << std::endl;
        ////////////////////////////////
        
        
        if (r2 >= 0){
          r_new = sqrt(r2);
          disk_new = Disk(cost_activ.get_mu1(), cost_activ.get_mu2(), r_new);
          
          Rcpp::Rcout << "create disk" << std::endl;
          Rcpp::Rcout << disk_new.get_radius() << std::endl;
          Rcpp::Rcout << "intersection" << std::endl;
          geom_activ.intersection_disk(disk_new);
          Rcpp::Rcout << "res empty" << std::endl;
          Rcpp::Rcout << geom_activ.empty_set(geom_activ.get_rect_t()) << std::endl;
          if (geom_activ.empty_set(geom_activ.get_rect_t())){
            Rcpp::Rcout << "delete geom" << std::endl;
            Rcpp::Rcout << geom_activ.get_label_t() << std::endl;
           it_list = list_geom.erase(it_list);
           --it_list;
           Rcpp::Rcout << "delete !!!!" << std::endl;
          }
        }
        Rcpp::Rcout << "itteration while " << std::endl;
    
        ++it_list;
      }// while (it_list != list_geom.end())
    } //if (type == 1)  
    
    //it_list = list_geom.end();
    Rcpp::Rcout << "update Dtt " << std::endl;
    if ((m[t + 1] - m[t]) > 0){
      geom_activ = Geom(y1[t],y2[t], sqrt(m[t + 1] - m[t]), t); // update Dtt
      list_geom.push_back(geom_activ);
    }
    Rcpp::Rcout << "update Dtt end " << std::endl;
  }//for (unsigned int t = 0; t < n ; t++)
     
  //-----------------------result vectors---------------------------------------
  unsigned int chp = n;
  while (chp > 0){
    changepoints.push_back(chp);
    means1.push_back(last_chpt_mean[1][chp-1]);
    means2.push_back(last_chpt_mean[2][chp-1]);
    chp = last_chpt_mean[0][chp-1];
  }
  reverse(changepoints.begin(), changepoints.end());
  reverse(means1.begin(), means1.end());
  reverse(means2.begin(), means2.end());
  
  globalCost = m[n + 1] - penalty * changepoints.size() ;
  //----------------------------memory------------------------------------------
  delete [] m;
  m = NULL;
  for(unsigned int i = 0; i < 3; i++) {delete(last_chpt_mean[i]);}
  delete [] last_chpt_mean;
  last_chpt_mean = NULL;
}

//#############################End##############################################//