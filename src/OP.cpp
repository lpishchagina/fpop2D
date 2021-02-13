#include "OP.h"
#include "Geom.h"
#include "Disk.h"
#include "Rect.h"
#include "Cost.h"
#include "math.h"

#include <iostream>
//#include <vector>

//#include <stdlib.h>

using namespace std;
//
#include <Rcpp.h>
using namespace Rcpp;

//--------------constructor------------------------------------
OP::OP(std::vector<double>& y1, std::vector<double>& y2, double beta){
  penalty = beta;
  n = y1.size();
  sy12 = new double*[n+1]; 
  for(unsigned int i = 0; i < n+1; i++) {sy12[i] = new double[4];}
}
//--------------destructor------------------------------------
OP::~OP(){
  for(unsigned int i = 0; i < n+1; i++) {delete(sy12[i]);}
  delete [] sy12;
  sy12 = NULL;
}
//--------------accessory------------------------------------
std::vector< int > OP::get_last_chpts() const {return last_chpts;}
std::vector< double > OP::get_means1() const{return means1;}
std::vector< double > OP::get_means2() const{return means2;}
double OP::get_globalCost() const {return globalCost;}
unsigned int OP::get_n() const {return n;}
double** OP::get_sy12() {return sy12;}
//--------------preprocessing------------------------------------
//std::vector<std::vector<double>>
double** OP::vect_sy12(std::vector<double>& y1, std::vector<double>& y2){
  unsigned int n = y1.size();
  sy12[0][0] = 0;
  sy12[0][1] = 0;
  sy12[0][2] = 0;
  sy12[0][3] = 0;
  for (unsigned int j = 1; j < (n + 1); j++){
    sy12[j][0] = sy12[j-1][0] + y1[j-1];
    sy12[j][1] = sy12[j-1][1] + y2[j-1];
    sy12[j][2] = sy12[j-1][2] + y1[j-1] * y1[j-1];
    sy12[j][3] = sy12[j-1][3] + y2[j-1] * y2[j-1];
  }
  return(sy12);
}
//--------------algoFPOP------------------------------------
void OP::algoFPOP(std::vector< double >& y1, std::vector< double >& y2, int type){
  
  n = y1.size();
  sy12 = vect_sy12(y1, y2);
  double** s = get_sy12();
  double m_new = 0;   // globalCost for the moment t 
  double m_min;       // min cost
  unsigned int label;
  Cost cost_new;
  Geom geom_new;
  
  std::list <Geom> list_geom; // list of geom,  geom has 3 elements: label_t, rect_t, cost_t
  std::list<Geom> ::iterator it_list;
  
  double mean1;	// means for segment 
  double mean2;
 
  Disk disk_new;  //pruning "intersection"
  Rect rect_new;
  double r_new;
  Geom geom_update;
  
  //algoFPOP 
  for(unsigned int t = 1; t < n + 1; t++){                        //!!!!!!!!!!!!
    cost_new = Cost(1, t, s[0], s[t], -penalty);      // attention: (m_new + penalty)- true or false?
    geom_new = Geom(cost_new.get_mu1(), cost_new.get_mu2(), sqrt(m_new + penalty), t, cost_new);// // initialization of new geom??????
    it_list = list_geom.begin();
    list_geom.push_front(geom_new);
    it_list = list_geom.begin();
    ++it_list;//  pass: 1 element, it is new geom
    
    label = geom_new.get_label_t();
    m_min = geom_new.get_cost_t().get_min();
    mean1 = geom_new.get_cost_t().get_mu1();
    mean2 = geom_new.get_cost_t().get_mu2();
    
    //first run: search m_min
    while(it_list != list_geom.end()){
      geom_new = *it_list;
      cost_new = Cost(geom_new.get_label_t(), t, s[geom_new.get_label_t()-1], s[t], geom_new.get_cost_t().get_mi_1_p());//
      if (cost_new.get_min() < m_min){
        label = geom_new.get_label_t();
        m_min = cost_new.get_min();
        mean1 = cost_new.get_mu1();
        mean2 = cost_new.get_mu2();
      }
      ++it_list;
    }
    m_new = m_min + penalty; // globalCost for the moment t
    // fill result vectors
    last_chpts.push_back(label); //best last chpt  for the moment t
    means1.push_back(mean1);// means for segment 
    means2.push_back(mean2);
    
    //second run: pruning 
    //type = 1 pruning "intersection"
    if (type == 1){
      it_list = list_geom.begin();
      ++it_list; //  pass: 1 element, it is new geom
      while(it_list != list_geom.end()){
        geom_new = *it_list;
        r_new = sqrt((m_new - geom_new.get_cost_t().get_mi_1_p())/geom_new.get_cost_t().get_coef() - geom_new.get_cost_t().get_coef_Var());
        disk_new = Disk(geom_new.get_cost_t().get_mu1(), geom_new.get_cost_t().get_mu2(), r_new);
        //intersection result
        geom_update = Geom(geom_new.get_label_t(), geom_new.get_cost_t(), geom_new.intersection(geom_new.get_rect_t(), disk_new));
        
        if (geom_update.empty_set(geom_update.get_rect_t())){ 
          unsigned int i = geom_update.get_label_t();
          
          last_chpts.erase(last_chpts.begin() + i - 1);// index?
          means1.erase(means1.begin() + i - 1);
          means2.erase(means2.begin() + i - 1);
          it_list = list_geom.erase(it_list);// delete previous geom
        } 
         else{
           it_list = list_geom.erase(it_list);
           list_geom.insert(it_list,geom_update);
           ++it_list;	
         } 
      }	
    } 
  }
}