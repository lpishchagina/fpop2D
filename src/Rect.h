#ifndef RECT_H
#define RECT_H

#include "math.h"

class Rect{
public:
  //--------------constructor------------------------------------
  Rect();
  Rect(double x0, double y0, double x1, double y1);
  //--------------accessory------------------------------------
  double get_rectx0();
  double get_recty0();
  double get_rectx1();
  double get_recty1();

private:
  double rectx0;  // coordinates of the bottom left vertex 
  double recty0;
  double rectx1;  // coordinates of the top right vertex
  double recty1;
};

#endif //RECT_H