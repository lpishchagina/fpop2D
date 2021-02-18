#include "Disk.h"
#include "math.h"
#include<iostream>

using namespace std;

//############################## constructor #####################################//
Disk::Disk(){
  center1 = 0;                                          // coordinates of center
  center2 = 0;
  radius = 0;  
}
Disk::Disk(double c1, double c2, double r){
  center1 = c1;                                          // coordinates of center
  center2 = c2;
  radius = r;  
}

//############################## accessory #######################################//
double Disk::get_radius() {return radius;}
double Disk::get_center1(){return center1;}
double Disk::get_center2(){return center2;}
//################################## End #########################################//
