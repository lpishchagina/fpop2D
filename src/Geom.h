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
  //--------------accessory------------------------------------
 // Rect get_rectangle();
  unsigned int get_label();
  //--------------a------------------------------------
  bool empty_set(Rect R);   //checking for emptiness of an approximated set 
  Rect intersection(Rect rect, Disk disk); // intersection approximation
  Rect substraction(Rect rect, Disk disk); // substraction approximation
  
private:
  unsigned int label;// 
  Rect rectangle = Rect();
};

#endif //GEOM_H