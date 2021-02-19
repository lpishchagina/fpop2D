#include "Geom.h"
#include "Disk.h"
#include "Rect.h"
#include "Cost.h"
#include <iostream>
#include <math.h>
using namespace std;

#include <Rcpp.h>
using namespace Rcpp;

//############################## constructor #####################################//
Geom::Geom(unsigned  int t){
  label_t = t;
  rect_t = Rect();
}
Geom::Geom(double c1, double c2, double r, unsigned int  t){ // start geom
  label_t = t;
  rect_t = Rect(c1-r, c2-r, c1+r, c2+r);
}

//############################## accessory #######################################//
unsigned int Geom::get_label_t(){return label_t;}
Rect Geom::get_rect_t(){return rect_t;}


//############################## empty_set #######################################//
bool Geom::empty_set(Rect rect){        //checking for emptiness of an approximated set 
  if (rect.get_rectx0() >= rect.get_rectx1() || rect.get_recty0() >= rect.get_recty1()){
    return true;
    }
  else {return false;} 
}

//############ intersection-rect_disk and difference_rect_disk ###################//
void Geom::intersection_rect_disk(Disk disk){rect_t.intersection(disk);}

void Geom::difference_rect_disk(Disk disk){rect_t.difference(disk);}



//############################### End ############################################//