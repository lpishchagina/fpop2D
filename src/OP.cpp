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
std::vector< int > OP::get_changepoints() const {return changepoints;}
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

//--------------algoFPOP----------------------------------
void OP::algoFPOP(std::vector< double >& y1, std::vector< double >& y2, int type){
  n = y1.size();
  sy12 = vect_sy12(y1, y2);            //preprocessing
  double** s = get_sy12();
  m.push_back(0);
  m.push_back(penalty);                 // "globalCost" for the moment t  = 0, t = 0:n-1
  std::list<Geom> ::iterator it_list;  // itterator for list of geom "list_geom"
  Geom geom_activ;
  Cost cost_activ;
  
  std:: vector <double> mus1;
  std:: vector <double> mus2;
  
  //FPOP//  
  for (unsigned int t = 0 ; t < n ; t++){
    
    // initialisation of new geom:label_t = t, rect_t  = "square" Dtt 
    geom_activ = Geom(y1[t], y2[t], sqrt(m[t+1] - m[t]), t);
    list_geom.push_front(geom_activ);         //add to the list of geom "list_geom"
    cost_activ = Cost(t, t, s[t], s[t+1], m[t]);
    
    it_list = list_geom.begin();
    geom_activ = *it_list;
    
    unsigned int i = geom_activ.get_label_t();
    double min_val_cost = cost_activ.get_min();       // q_it is a paraboloid => min{q_it} = coef_Var + mi_1_p
    double mean1 = cost_activ.get_mu1(); // means for interval (i,t)
    double mean2 = cost_activ.get_mu2();
    ++ it_list;
    
    //first run: search m[t+2]
    while (it_list != list_geom.end()){
      geom_activ = *it_list;
      unsigned int lbl = geom_activ.get_label_t();
      cost_activ = Cost(lbl, t, s[lbl], s[t+1], m[lbl]);// add point y(t) to the previous  geoms
    
      if (min_val_cost > cost_activ.get_min()){
        i = geom_activ.get_label_t();
        min_val_cost = cost_activ.get_min();
        mean1 = cost_activ.get_mu1();
        mean2 = cost_activ.get_mu2();
      }
      ++ it_list;
    }
    
    m.push_back(min_val_cost + penalty);

    last_chpts.push_back(i);                    //best last chpt for t
    mus1.push_back(mean1);                    //add means for (i,t)
    mus2.push_back(mean2);
    
    //second run: pruning 
    //type = 1 pruning "intersection"
    if (type == 1){
      it_list = list_geom.begin();
      ++it_list; //  pass: 1 element, it is new geom Dtt
      
      while (it_list != list_geom.end()){
        double r_new;
        Rect rect_new;
        Disk disk_new;
        Geom geom_update;
        
        geom_activ = *it_list;
        unsigned int lbl = geom_activ.get_label_t();
        
        cost_activ = Cost(lbl, t, s[lbl], s[t+1], m[lbl+1]);
        
        // find radius
        r_new = sqrt((m[t+2] - cost_activ.get_mi_1_p())/cost_activ.get_coef() - cost_activ.get_coef_Var());
        //build new disk
        disk_new = Disk(cost_activ.get_mu1(), cost_activ.get_mu2(), r_new);
        //intersection result
        rect_new = geom_activ.intersection(geom_activ.get_rect_t(), disk_new);
        geom_update = Geom(i,rect_new);
        //delete previous geom
        it_list = list_geom.erase(it_list);
        //if update geom isn't empty, add to the list
        if (!geom_update.empty_set(geom_update.get_rect_t())){ 
          list_geom.insert(it_list, geom_update);
          ++it_list;	
        } 
      }
    }
  }

  //forme result vectors
  globalCost = m[n+2];
  int chp = n-1;
  while (chp > 0){
    changepoints.push_back(chp + 1);
    means1.push_back( mus1[chp]);
    means2.push_back( mus2[chp]);
    chp = last_chpts[chp]-1;
  }
  
  reverse(changepoints.begin(), changepoints.end());
  reverse(means1.begin(), means1.end());
  reverse(means2.begin(), means2.end());
}