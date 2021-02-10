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
  Geom(unsigned int t);
  Geom(double c1, double c2, double r, double t);
  //--------------accessory------------------------------------
  unsigned int get_label_t();
  Rect get_rect_t();
  //--------------min max------------------------------------
  double min_ab(double a, double b);
  double max_ab(double a, double b);
  //--------------disk_it------------------------------------
  Disk disk_it(Cost newcost);
  //--------------set------------------------------------
  bool empty_set(Rect R);   //checking for emptiness of an approximated set 
  Rect intersection(Rect rect, Disk disk); // intersection approximation
  Rect difference(Rect rect, Disk disk); // difference approximation
  //-----------------------------------------------------
private:
  unsigned int label_t;// time moment 
  Rect rect_t;
};

#endif //GEOM_H