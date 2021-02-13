#ifndef GEOM_H
#define GEOM_H

#include <iostream>
#include <vector>

#include "Disk.h"
#include "Rect.h"
#include "Cost.h"

class Geom{
public:
  //--------------constructor------------------------------------
  Geom(){};
  Geom(double c1, double c2, double r, double t, Cost cst);
  Geom(double m_ipen, int t);
  Geom(double lbl, Cost cst, Rect rct);
  //--------------accessory------------------------------------
  unsigned int get_label_t();
  Rect get_rect_t();
  Cost get_cost_t();
  //--------------min max------------------------------------
  double min_ab(double a, double b);
  double max_ab(double a, double b);
  //--------------set------------------------------------
  bool empty_set(Rect R);   //checking for emptiness of an approximated set 
  Rect intersection(Rect rect, Disk disk); // intersection approximation
  Rect difference(Rect rect, Disk disk); // difference approximation
  //-----------------------------------------------------
private:
  unsigned int label_t;// time moment 
  Cost cost_t;
  Rect rect_t;
};

#endif //GEOM_H