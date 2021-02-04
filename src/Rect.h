#ifndef RECT_H
#define RECT_H

#include < math.h >
#include "Disk.h"

class Rect{
public:
  Rect(double dx0, double dy0, double dx1, double dy1);
  double get_x0();
  double get_y0();
  double get_x1();
  double get_y1();
  double sqr_dist(double a1, double a2, double b1,double b2); // the square of the distance between two points (a1,a2) (b1,b2) 
  bool empty_set(Rect R, Disk D); //intersection check 
  Rect intersection (Rect R, Disk D); // intersection disk and rectangle, creating a new rectangle 
  
private:
  double x0;  // coordinates of the bottom left vertex 
  double y0;
  double x1;  // coordinates of the top right vertex
  double y1;
};

#endif //RECT_H