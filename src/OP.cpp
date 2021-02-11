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
  last_changepoints.push_back(0);
  m.push_back(-penalty); //стоит добавлять или нет
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
      mean1tT = (sy12[chpt_temp][0] - sy12[last_changepoints[chpt_temp]][0]) / (chpt_temp - last_changepoints[chpt_temp]);
      mean2tT = (sy12[chpt_temp][1] - sy12[last_changepoints[chpt_temp]][1]) / (chpt_temp - last_changepoints[chpt_temp]);
      means1.push_back(mean1tT);
      means2.push_back(mean2tT);
      chpt_temp = last_changepoints[chpt_temp];
    }
    reverse(changepoints.begin(), changepoints.end());
    reverse(means1.begin(), means1.end());
    reverse(means2.begin(), means2.end());
  }
}
//--------------algoFPOP------------------------------------
void OP::algoFPOP(std::vector< double >& y1, std::vector< double >& y2, int type)
{
  n = y1.size();
  Cost cost;
  double cost_temp = 0;
  double m_temp = 0;
  int chpt_temp = 0;
  Disk disk_t;
  
  std::list <Geom> list_geom;
  std::list<Geom> ::iterator it_list_geom;
  
  Geom geom = (y1[0], y2[0], sqrt(penalty), 0);// start: rectangle 
  list_geom.push_back(geom); // list contains  1 geom
  sy12 = vect_sy12(y1, y2);
  Geom geom_temp;
  Rect geom_rect;
  
  //cycle 
  for(unsigned int t = 1; t < n; t++){
    m_temp = INFINITY;
    chpt_temp = 0;
    it_list_geom = list_geom.begin();
    
    while(it_list_geom != list_geom.end())
    {
      geom_temp = *it_list_geom;
      unsigned int i = geom_temp.get_label_t();
      cost = Cost();//(i, t, sy12, m[i-1]);//подумать здесь точно ошибка m[i-1] может стоит еще положить пенальти
      cost_temp = cost.get_min();
        if (m_temp > cost_temp){
          m_temp =cost_temp;
          chpt_temp = i;
        }
        ++it_list_geom;
    }
    m[t] = m_temp;
    last_changepoints[t] = chpt_temp;
    /*
    //pruning "intersection" type = 1
    if (type == 1){
      disk_t = Disk(); //сделать новый диск правильно
      it_list_geom = list_geom.begin();
      while(it_list_geom != list_geom.end()){
        geom_temp = *it_list_geom;
        geom_rect = geom_temp.get_rect_t();
        //сделать пересечение
        geom_rect = geom_rect.intersection(geom_rect,disk_t); //геометрия а не прямоугольник,  исправить
        if (geom_rect.empty_set()){ //геометрия а не прямоугольник,  исправить
          it_list_geom = list_geom.erase(it_list_geom);//удалили пустую геометрию
        }
        else {++it_list_geom;}
      }
      list_geom.push_back(geom_temp);//отследить , корректно задать геометрию
    }
     */
}