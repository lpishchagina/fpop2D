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

//############################## constructor #####################################//
OP::OP(std::vector<double>& y1, std::vector<double>& y2, double beta){
  penalty = beta;
  n = y1.size();
  sy12 = new double*[n+1]; 
  for(unsigned int i = 0; i < n+1; i++) {sy12[i] = new double[4];}
  m = new double[n + 1];        // "globalCost" = m[n+1] - changepoints.size()*penalty
}

//############################## destructor ######################################//
OP::~OP(){
  for(unsigned int i = 0; i < n+1; i++) {delete(sy12[i]);}
  delete [] sy12;
  sy12 = NULL;
  delete [] m;
  m = NULL;
}

//############################## accessory #######################################//
std::vector< unsigned int > OP::get_changepoints() const {return changepoints;}
std::vector< double > OP::get_means1() const{return means1;}
std::vector< double > OP::get_means2() const{return means2;}
double OP::get_globalCost() const {return globalCost;}
unsigned int OP::get_n() const {return n;}
double** OP::get_sy12() {return sy12;}
Geom OP::get_geom_activ() const {return geom_activ;}
std::list<Geom> ::iterator OP::get_it_list() const {return it_list;}

//############################## intersection_geom_disk ##########################//
void OP::intersection_geom_disk(Disk disk){
    geom_activ.intersection_rect_disk(disk);
    
    Rcpp::Rcout << "___________coord rect t in OP inret geom disk_______________" << std::endl;
    Rcpp::Rcout << geom_activ.get_rect_t().get_rectx0() << std::endl;
    Rcpp::Rcout << geom_activ.get_rect_t().get_recty0() << std::endl;
    Rcpp::Rcout << geom_activ.get_rect_t().get_rectx1() << std::endl;
    Rcpp::Rcout << geom_activ.get_rect_t().get_recty1() << std::endl;
    Rcpp::Rcout << "-------end coord rect t in OP inret geom disk------------" << std::endl;
}

//############################## difference_geom_disk ##########################//
void OP::difference_geom_disk(Disk disk){
  geom_activ.difference_rect_disk(disk);
  
  Rcpp::Rcout << "_______________coord rect t in OP dif geom disk________________" << std::endl;
  Rcpp::Rcout << geom_activ.get_rect_t().get_rectx0() << std::endl;
  Rcpp::Rcout << geom_activ.get_rect_t().get_recty0() << std::endl;
  Rcpp::Rcout << geom_activ.get_rect_t().get_rectx1() << std::endl;
  Rcpp::Rcout << geom_activ.get_rect_t().get_recty1() << std::endl;
  Rcpp::Rcout << "-------end coord rect t in OP diff geom disk------------" << std::endl;
}

//############################## vect_sy12 #######################################//
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
/*
//############################### algoFPOP #######################################//
void OP::algoFPOP(std::vector<double>& y1, std::vector<double>& y2, int type){
  //-------------------------preprocessing-------------------------------------
  n = y1.size();
  sy12 = vect_sy12(y1, y2);           
   
  m[0] = 0;
  double** last_chpt_mean = new double*[3];         // vectors of best last changepoints, mean1 and mean2
  for(unsigned int i = 0; i < 3; i++) {last_chpt_mean[i] = new double[n];}
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
      it_list = list_geom.begin();
      while (it_list != list_geom.end()){
        Disk disk_new;
        geom_activ = *it_list;
        lbl = geom_activ.get_label_t();
        cost_activ = Cost(lbl, t, sy12[lbl], sy12[t + 1], m[lbl]);
        double r2 = (m[t + 1] - m[lbl] - cost_activ.get_coef_Var())/cost_activ.get_coef(); //find radius^2
        if (r2 <= 0){it_list = list_geom.erase(it_list);}                 //PELT
        else{                                                             //FPOP
          disk_new = Disk(cost_activ.get_mu1(), cost_activ.get_mu2(), sqrt(r2));
          intersection_geom_disk(disk_new);
          it_list = list_geom.erase(it_list);
          it_list = list_geom.insert(it_list, geom_activ);
          if (geom_activ.empty_set(geom_activ.get_rect_t())){ it_list = list_geom.erase(it_list);}
        }
        ++it_list;
      }// while (it_list != list_geom.end())
    } //if (type == 1) 
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
  for(unsigned int i = 0; i < 3; i++) {delete(last_chpt_mean[i]);}
  delete [] last_chpt_mean;
  last_chpt_mean = NULL;
}

//############################# End ##############################################//


*/


//############################### algoFPOP #######################################//
void OP::algoFPOP(std::vector<double>& y1, std::vector<double>& y2, int type){
  Rcpp::Rcout << "___________1____________________" << std::endl;
  //-------------------------preprocessing-------------------------------------
  n = y1.size();
  sy12 = vect_sy12(y1, y2);           
  m[0] = 0;
  double** last_chpt_mean = new double*[3];         // vectors of best last changepoints, mean1 and mean2
  for(unsigned int i = 0; i < 3; i++) {last_chpt_mean[i] = new double[n];}
  
  list_disk.clear();
  
  //-------------------------Algorithm------------------------------------------
  // type = 0 PELT; type = 1 FPOP INTER; type = 2 FPOP DIF
  if (type >= 0){
    for (unsigned int t = 0; t < n ; t++){
      Rcpp::Rcout << "___________2____________________" << std::endl;
      double min_val = INFINITY;                      //min value of cost
      double mean1;                                   //means for (lbl, t)
      double mean2; 
      unsigned int lbl;                               //best last position for t
      

      ////////////////////////////check////////////////////////////////////
      Rcpp::Rcout << "___________3____________________" << std::endl;
      Rcpp::Rcout << "___________list of active disks for t-1__________________" << std::endl;
      it_disk = list_disk.begin();
      while(it_disk != list_disk.end()){
        unsigned int i = *it_disk;
        Rcpp::Rcout << i << std::endl;
        ++it_disk;
      }
      Rcpp::Rcout << "___________end list of active disks for t-1______________" << std::endl;
      ////////////////////////////check////////////////////////////////////
      
      
      
      //-----------------------new geom D_tt--------------------------------------
      geom_activ = Geom(t); 
      list_geom.push_back(geom_activ);
      std::list<unsigned int> list_activ_disk;//!!!!!!list of active disks for t
      Rcpp::Rcout << "___________4____________________" << std::endl;
      //-----------------First run: search min------------------------------------
      it_list = list_geom.begin();
      while(it_list != list_geom.end()){
        geom_activ = *it_list;
        unsigned int u = geom_activ.get_label_t();
        Cost cost_activ = Cost(u, t, sy12[u], sy12[t + 1], m[u]);
        if(cost_activ.get_min() < min_val){
          lbl = u;
          min_val = cost_activ.get_min();
          mean1 = cost_activ.get_mu1();
          mean2 = cost_activ.get_mu2();  
        }
        ++it_list;
      }
      m[t + 1] = min_val + penalty;     // new min 
      Rcpp::Rcout << "___________5____________________" << std::endl;
      //-----------------best last changepoints and means-------------------------
      last_chpt_mean[0][t] = lbl;       //last_chpt_mean[0] - vector of best last chpt
      last_chpt_mean[1][t] = mean1;     //last_chpt_mean[1] - vector of means (lbl,t) for y1
      last_chpt_mean[2][t] = mean2;     //last_chpt_mean[2] - vector of means (lbl,t) for y2
      
      //------------------Second run: pruning-------------------------------------
      // type = 0 PELT; type = 1 FPOP INTER; type = 2 FPOP DIF
      
      ///////////////////////////////check///////////////////////////////////////
      it_list = list_geom.begin();
      Rcpp::Rcout << "___________all rect_t for t____________________" << std::endl;
      while( it_list != list_geom.end() ){
        geom_activ = *it_list;
        Rcpp::Rcout << geom_activ.get_label_t() << std::endl;
        Rcpp::Rcout << "coord rect t" << std::endl;
        Rcpp::Rcout << geom_activ.get_rect_t().get_rectx0() << std::endl;
        Rcpp::Rcout << geom_activ.get_rect_t().get_recty0() << std::endl;
        Rcpp::Rcout << geom_activ.get_rect_t().get_rectx1() << std::endl;
        Rcpp::Rcout << geom_activ.get_rect_t().get_recty1() << std::endl;
        Rcpp::Rcout << "-------end coord rect t------------" << std::endl;
        ++it_list;
      }
      ////////////////////////////end check//////////////////////////////////////
      Rcpp::Rcout << "___________6____________________" << std::endl;
      
      //-------------------------PELT-------------------------------------------
      it_list = list_geom.begin();      
      while (it_list != list_geom.end()){
        geom_activ = *it_list;
        lbl = geom_activ.get_label_t();
        Cost cost_inter = Cost(lbl, t, sy12[lbl], sy12[t + 1], m[lbl]);
        double r2_inter = (m[t + 1] - m[lbl] - cost_inter.get_coef_Var())/cost_inter.get_coef();
        //------------------------condition  PELT-------------------------------
        if (r2_inter <= 0){it_list = list_geom.erase(it_list);}   //delete geom PELT 
        //-------------------------------FPOP-----------------------------------
        if (type >= 1){
          if (r2_inter > 0){
            Disk disk_inter = Disk(cost_inter.get_mu1(), cost_inter.get_mu2(), sqrt(r2_inter));
            //-----------------------intersection-------------------------------
            intersection_geom_disk(disk_inter);
            it_list = list_geom.erase(it_list);
            it_list = list_geom.insert(it_list, geom_activ);//update list element
            //------------------------condition  FPOP INTER---------------------
            if (geom_activ.empty_set(geom_activ.get_rect_t())){ it_list = list_geom.erase(it_list);//delete geom, intersection is empty
              
              Rcpp::Rcout << "____________delete intersectoin________________________" << std::endl;
            }
            else {list_activ_disk.push_back(geom_activ.get_label_t());}
            if (type = 2){
              if (!geom_activ.empty_set(geom_activ.get_rect_t())){ //intersection isn't empty
                //------------------FPOP DIF------------------------------------
                it_disk = list_disk.begin();
                unsigned int j = *it_disk;
                Rcpp::Rcout << "____________attention________________________" << std::endl;
                while( j < lbl){
                  Rcpp::Rcout << "j =" << std::endl;
                  Rcpp::Rcout << j << std::endl;
                  Rcpp::Rcout << "lbl=" << std::endl;
                  Rcpp::Rcout << lbl << std::endl;
                  Rcpp::Rcout << "____________end attention________________________" << std::endl;
                  
                  Cost cost_dif = Cost(j, lbl-1, sy12[j], sy12[lbl], m[j]);
                  double r2_dif = (m[lbl] - m[j] - cost_dif.get_coef_Var())/cost_dif.get_coef();
                  Rcpp::Rcout << "____________r2_dif________________________" << std::endl;
                  Rcpp::Rcout << r2_dif << std::endl;
                  //------------------difference--------------------------------
                  if(r2_dif > 0){  
                    Disk disk_dif = Disk(cost_dif.get_mu1(), cost_dif.get_mu2(), sqrt(r2_dif));
                    difference_geom_disk(disk_dif);
                    it_list = list_geom.erase(it_list);
                    it_list = list_geom.insert(it_list, geom_activ);//update geom
                    //------------------condition  FPOP DIF---------------------
                    if (geom_activ.empty_set(geom_activ.get_rect_t())){ it_list = list_geom.erase(it_list);//delete geom, difference is empty
                      Rcpp::Rcout << "____________delete difference________________________" << std::endl;
                    }
                  }//if (r2_dif > 0)
                  ++it_disk;
                  j = *it_disk;
                }//while( j < lbl)
              }//if (!geom_activ.empty_set(geom_activ.get_rect_t())
            }//if (type = 2)
          }//if (r2_inter > 0)
        }//if (type >= 1)
        ++it_list;
      }//while (it_list != list_geom.end())
      list_disk.swap(list_activ_disk);
    }//for (unsigned int t = 0; t < n ; t++)
  }//if (type >= 0)
  //-----------------------result vectors---------------------------------------
  Rcpp::Rcout << "___________10____________________" << std::endl;
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
  for(unsigned int i = 0; i < 3; i++) {delete(last_chpt_mean[i]);}
  delete [] last_chpt_mean;
  last_chpt_mean = NULL;
}
//############################# End ##############################################//