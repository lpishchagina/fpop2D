#ifndef GEOM_H
#define GEOM_H

#include <iostream>
#include <math.h>
#include <vector>

#include "Disk.h"
#include "Rect.h"
#include "Cost.h"

class Geom{
public:
  //--------------constructor------------------------------------
  Geom(){};
  Geom(double K, unsigned int t);
  //--------------accessory------------------------------------
  unsigned int get_label_t();
  Rect get_rect_t();
  Cost get_m_t();

  //--------------disk_it------------------------------------
  Disk disk_it(double new_m_t);
  //--------------set------------------------------------
  bool empty_set(Rect R);   //checking for emptiness of an approximated set 
  Rect intersection(Rect rect, Disk disk); // intersection approximation
  Rect difference(Rect rect, Disk disk); // difference approximation
  //-----------------------------------------------------
private:
  unsigned int label_t;// time moment 
  Rect rect_t;
  Cost m_t; // m_t = min_it{mi_1 + penalty + coef*(Var(y1_it) + Var(y2_it))} = min_it(mi_1 + penalty) = Cost(mi_1 + penalty, t)
};

#endif //GEOM_H