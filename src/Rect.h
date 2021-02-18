#ifndef RECT_H
#define RECT_H

#include "math.h"
#include "Disk.h"

//################################################################################//
//############################### Class Rect #####################################//
class Rect{
public:
//------------------------------constructor-------------------------------------//
  Rect();
  Rect(double x0, double y0, double x1, double y1);
  Rect(double c1, double C2, double r);
//------------------------------accessory---------------------------------------//
  double get_rectx0();
  double get_recty0();
  double get_rectx1();
  double get_recty1();
//--------------------------------min max---------------------------------------//
  double min_ab(double a, double b);
  double max_ab(double a, double b);
//-------------------difference and intersection--------------------------------// 
  void difference(Disk disk);
  void intersection(Disk disk);

private:
  double rectx0;                        // coordinates of the bottom left vertex 
  double recty0;
  double rectx1;                        // coordinates of the top right vertex
  double recty1;
};
//############################# End Class Cost ###################################//
#endif //RECT_H