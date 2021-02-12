#include "OP.h"
#include "Geom.h"
#include "Disk.h"
#include "Rect.h"
#include "Cost.h"

#include <iostream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

//--------------constructor------------------------------------
OP::OP(std::vector<double>& y1, std::vector<double>& y2, double beta){
  penalty = beta;
  n = y1.size();
  last_chpts.push_back(0);
  m.push_back(0);
}
//--------------accessory------------------------------------
std::vector< int > OP::get_changepoints() const {return changepoints;}
std::vector< double > OP::get_means1() const{return means1;}
std::vector< double > OP::get_means2() const{return means2;}
double OP::get_globalCost() const {return globalCost;}
unsigned int OP::get_n() const {return n;}
std::vector<std::vector<double>> OP::get_sy12() {return sy12;}
//--------------preprocessing------------------------------------
std::vector<std::vector<double>> OP::vect_sy12(std::vector<double>& y1, std::vector<double>& y2){
  unsigned int n = y1.size();
  sy12[0][0] = 0;
  sy12[0][1] = 0;
  sy12[0][2] = 0;
  sy12[0][3] = 0;
  for (unsigned int j = 1; j < (n + 1); j++){
    sy12[j][0] = sy12[j-1][0] + y1[j-1];
    sy12[j][1] = sy12[j-1][1] + y2[j-1];
    sy12[j][2] = sy12[j-1][2] + y1[j-1] * y1[j-1];
    sy12[j][2] = sy12[j-1][2] + y2[j-1] * y2[j-1];
  }
  return(sy12);
}
//--------------backtracking------------------------------------
void OP::backtracking(unsigned int ndata){
  {
    globalCost = m[n-1];
    int chpt_temp = n-1;
    double mean1tT;
    double mean2tT;
    while (chpt_temp > 0)
    {
      changepoints.push_back(chpt_temp);
      mean1tT = (sy12[chpt_temp][0] - sy12[last_chpts[chpt_temp]][0]) / (chpt_temp - last_chpts[chpt_temp]);
      mean2tT = (sy12[chpt_temp][1] - sy12[last_chpts[chpt_temp]][1]) / (chpt_temp - last_chpts[chpt_temp]);
      means1.push_back(mean1tT);
      means2.push_back(mean2tT);
      chpt_temp = last_chpts[chpt_temp];
    }
    reverse(changepoints.begin(), changepoints.end());
    reverse(means1.begin(), means1.end());
    reverse(means2.begin(), means2.end());
  }
}
//--------------algoFPOP------------------------------------
void OP::algoFPOP(std::vector< double >& y1, std::vector< double >& y2, int type){
  n = y1.size();
  sy12 = vect_sy12(y1, y2);
  
  double m_new = 0;   // variables for finding minimum value of cost 
  double m_temp;
  int chpt_new = 0;   // argument of minimum 
  Cost cost_new;
 
  std::list <Geom> list_geom; // list of geom, every geom has 3 elements: label_t, rect_t, cost_t
  std::list<Geom> ::iterator it_list;
  
  Geom geom_new = Geom(y1[0], y2[0], sqrt(penalty), 0, penalty);// initialization of first geom
  list_geom.push_back(geom_new); // list contains  1 geom
  
  //algoFPOP 
  for(unsigned int t = 1; t < n; t++){ //the  position "0" is filled
    m_new = INFINITY;                 
    chpt_new = 0;
    
    //first run: search m_new
    it_list = list_geom.begin();
    while(it_list != list_geom.end()){// finding m_new
      geom_new = *it_list;
      cost_new = geom_new.get_cost_t();
      m_temp = cost_new.get_min();
      if (m_temp < m_new){
          m_new = m_temp;
          chpt_new = geom_new.get_label_t();
      }
      ++it_list;
    }
    m[t] = m_new;                 // m[n-1] - globalCost
    last_chpts[t] = chpt_new;     // save arg min
    
    //second run: pruning 
    //type = 1 pruning "intersection" 
    Disk disk_new;
    Rect rect_new;
    double r_new;
    Geom geom_update;
    
    if (type == 1){
      it_list = list_geom.begin();
      while(it_list != list_geom.end()){
        geom_new = *it_list;
        cost_new = geom_new.get_cost_t();
        r_new = sqrt((m_new - cost_new.get_mi_1_p())/cost_new.get_coef() - cost_new.get_coef_Var());
        disk_new = Disk(cost_new.get_mu1(), cost_new.get_mu2(), r_new);
        geom_update = Geom(geom_new.get_label_t(), geom_new.get_cost_t(), geom_new.intersection(geom_new.get_rect_t(), disk_new));
        it_list = list_geom.erase(it_list);// delete previous geom
        if (!geom_update.empty_set(geom_update.get_rect_t())){ //if  empty => delete else update geom
         list_geom.insert(it_list,geom_update);
          ++it_list;
        }
      }
      geom_new = Geom(y1[t], y2[t], sqrt(m_new-m[t-1]), t, m[t-1]);// geom_tt
      list_geom.push_back(geom_new);
    }
    
   /* //type = 2 pruning "intersection\union"
    if (type == 2){}
    */
  }
}