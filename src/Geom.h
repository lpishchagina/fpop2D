#ifndef GEOM_H
#define GEOM_H

#include <iostream>
#include <vector>
#include <list>

#include "Disk.h"
#include "Rect.h"
#include "Cost.h"

//################################################################################//
//############################### Class Geom #####################################//
class Geom{
public:
//------------------------------constructor-------------------------------------//
  Geom(){};
  Geom(unsigned int t, std::list<Disk> l_disk);
  Geom(double c1, double c2, double r, unsigned int t, std::list<Disk> l_disk);
  //------------------------------accessory-------------------------------------//
  unsigned int get_label_t();
  Rect get_rect_t();
  std::list<Disk> get_disks_t_1();
  void delete_disk(Disk d);
  //----empty, difference_rect_disk and intersection_rect_disk------------------// 
  bool empty_set(Rect R);         //checking for emptiness of an approximated set 
  void intersection_rect_disk(Disk disk);                //intersection approximation
  void difference_rect_disk(Disk disk);                    //difference approximation
private:
  unsigned int label_t;                                 //time moment 
  Rect rect_t;                                          //approx rectangle
  std::list<Disk> disks_t_1;//
};
//############################# End Class Geom ###################################//
#endif //GEOM_H
