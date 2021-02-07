#include "Rect.h"

#include<math.h>
#include<iostream>

using namespace std;

//--------------constructor------------------------------------
Rect::Rect(){
  rectx0 = 0;    
  recty0 = 0;
  rectx1 = 0;
  recty1 = 0;
}
Rect::Rect(double x0, double y0, double x1, double y1){
  rectx0 = x0;    
  recty0 = y0;
  rectx1 = x1;
  recty1 = y1;
}
//--------------accessory------------------------------------
double Rect::get_rectx0(){return rectx0;}
double Rect::get_recty0(){return recty0;}
double Rect::get_rectx1(){return rectx1;}
double Rect::get_recty1(){return recty1;}

