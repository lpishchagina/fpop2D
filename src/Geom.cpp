#include "Geom.h"
#include "Disk.h"
#include "Rect.h"
#include "Cost.h"
#include <iostream>
#include <math.h>
using namespace std;

//##############################constructor#####################################//
Geom::Geom(unsigned  int t){
  label_t = t;
  rect_t = Rect();
}
Geom::Geom(double c1, double c2, double r, unsigned int  t){ // start geom
  label_t = t;
  rect_t = Rect(c1-r, c2-r, c1+r, c2+r);
}

//##############################accessory#######################################//
unsigned int Geom::get_label_t(){return label_t;}
Rect Geom::get_rect_t(){return rect_t;}

//##############################empty_set#######################################//
bool Geom::empty_set(Rect rect){        //checking for emptiness of an approximated set 
  double x0 = rect.get_rectx0();        //parameters of the rectangle 
  double x1 = rect.get_rectx1();
  double y0 = rect.get_recty0();
  double y1 = rect.get_recty1();
  if (x0 >= x1 || y0 >= y1){return true;} else {return false;} 
}

//###################intersection_disk and difference_disk######################//
void Geom::intersection_disk(Disk disk){rect_t.intersection(disk);}
void Geom::difference_disk(Disk disk){rect_t.difference(disk);}

//###############################End############################################//