#include < iostream >
#include < math.h >

#include "Rect.h"
#include "Disk.h"
//--------------constructor------------------------------------
Rect::Rect(double dx0, double dy0, double dx1, double dy1)
{
  x0 = dx0;    
  y0 = dy0;
  x1 = dx1;
  y1 = dy1;
}
//--------------accessory------------------------------------
double Rect::get_x0(){return x0;}
double Rect::get_y0(){return y0;}
double Rect::get_x1(){return x1;}
double Rect::get_y1(){return y1;}
//--------------sqr_dist------------------------------------
double Rect::sqr_dist(double a1, double a2, double b1,double b2){return((a1-b1) * (a1-b1) + (a2-b2) * (a2-b2));}
//--------------empty_set------------------------------------
bool Rect::empty_set(Rect R, Disk D)
{ 
  bool empty = true;    //true -> empty set, false -> intersection
  
  double dr = D.get_r();            //parameters of the disk
  double dc1 = D.get_c1();
  double dc2 = D.get_c2();
  
  double rx0 = R.get_x0();        //parameters of the rectangle 
  double rx1 = R.get_x1();
  double ry0 = R.get_y0();
  double ry1 = R.get_y1();
  
  double dx0 = dr * dr + (rx0 - dc1) * (rx0 - dc1);  //discriminant/2
  double dx1 = dr * dr + (rx1 - dc1) * (rx1 - dc1);  //if  dxi < 0 - no intersection points with a line x = xi
  double dy0 = dr * dr + (ry0 - dc2) * (ry0 - dc2);  //if  dxi = 0 - one point with a line x = xi 
  double dy1 = dr * dr + (ry1 - dc2) * (ry1 - dc2);  //if  dxi > 0 - two points with a line x = xi
  
  //the center of the disk inside the rectangle
  if ((dc1 >= rx0) && (dc1 <= rx1) && (dc2 > ry0) && (dc2 <= ry1)) {empty = false;}
  else{
  //left half-plane 
  if (dc1 < rx0){ 
    if ((dx0 >= 0) && ((dy1 >= 0) || (dy0 >= 0))){empty = false;}
  }
  //right half-plane
  if (dc1 > rx1){ 
    if ((dx1 >= 0) && ((dy1 >= 0) || (dy0 >= 0))){empty = false;}
  }
  //top half-plane
  if (dc2 > ry1){ 
    if ((dy1 >= 0) && ((dx0 >= 0) || (dx1 >= 0))){empty = false;}
  }
  //bottom half-plane
  if (dc2 < ry0){
    if ((dy0 >= 0) && ((dx0 >= 0) || (dx1 >= 0))){empty = false;}
  }
  }
  return empty;
}
//--------------intersection------------------------------------
Rect Rect::intersection (Rect R, Disk D)
{ 
  double dr = D.get_r();         //parameters of the disk
  double dc1 = D.get_c1();
  double dc2 = D.get_c2();
  
  double rx0 = R.get_x0();       //parameters of the rectangle 
  double rx1 = R.get_x1();  
  double ry0 = R.get_y0();
  double ry1 = R.get_y1();
  
  double t1 = INFINITY;         //intersection points 
  double t2 = INFINITY;  
  
  double dx0 = dr * dr + (rx0 - dc1) * (rx0 - dc1); //discriminant/2
  double dx1 = dr * dr + (rx1 - dc1) * (rx1 - dc1); //if  dxi < 0 - no intersection points with a line x = xi
  double dy0 = dr * dr + (ry0 - dc2) * (ry0 - dc2); //if  dxi = 0 - one intersection point (t1) with a line x = xi
  double dy1 = dr * dr + (ry1 - dc2) * (ry1 - dc2); //if  dxi > 0 - two intersection points(t1, t2) with a line x = xi
  
  Rect newR = Rect(rx0, ry0, rx1, ry1); // intersection approximation
//approximation//
  // the center of the disk inside the rectangle
  if ( (dc1 >= rx0) && (dc1 <= rx1) && (dc2 >= ry0) && (dc2 <= ry1) ){   
    if (dc1 - dr > rx0) {rx0 = dc1 - dr;}
    if (dc2 - dr > ry0) {ry0 = dc2 - dr;}
    if (dc1 + dr < rx1) {rx1 = dc1 + dr;}
    if (dc2 + dr < ry1) {ry1 = dc2 + dr;}
  }
  //one intersection point 
  if ((dc1 < rx0) && ( dx0 == 0)) {rx1 = rx0; ry0 = dc2; ry1 = dc2;} //point (x0,c2)
  if ((dc1 > rx1) && ( dx1 == 0)) {rx0 = rx1; ry0 = dc2; ry1 = dc2;} //point (x1,c2)
  if ((dc2 < ry0) && ( dy0 == 0)) {ry1 = ry0; rx0 = dc1; rx1 = dc1;} //point (c1,y0)
  if ((dc2 > ry1) && ( dy1 == 0)) {ry0 = ry1; rx0 = dc1; rx1 = dc1;} //point (c1,y1)
  //two intersection points
    //bottom half-plane and top half of the disk 
  if ((dc2 < ry0) && (dy0 > 0)){
    t1 = dc1 - sqrt(dy0); //intersection points with a line y = y0
    t2 = dc1 + sqrt(dy0);
    if(t1 > rx0 && t1 < rx1){ rx0 = t1;}
    if(t2 > rx0 && t2 < rx1){ rx1 = t2;}
    if((dc1 >= rx0) && (dc1 <= rx1)) {if ((dc2 + dr) < ry1) {ry1 = dc2 + dr;}}  //boundary point of the disk in the rectangle 
    else {
      if (dx0 > 0){ t1 = dc2 + sqrt(dx0);} else {t1 = dc2 + sqrt(dx1);}  //intersection only with x=x1 
      if (dx1 > 0){
        t2 = dc2 + sqrt(dx1);   //intersection  with x = x0 and x = x1 
        if(t2 > t1) {t1 = t2;}  //max {t1,t2}
      }
      if (t1 < ry1){ry1 = t1;}  //min {y1, max{t1,t2}}
    }
  }
  //top half-plane and bottom half of the disk 
  if ((dc2 > ry1) && (dy1 > 0)){
    t1 = dc1 - sqrt(dy1);
    t2 = dc1 + sqrt(dy1);
    if(t1 > rx0 && t1 < rx1){ rx0 = t1;}
    if(t2 > rx0 && t2 < rx1){ rx1 = t2;}
    if((dc1 >= rx0) && (dc1 <= rx1)) {if ((dc2 - dr) > ry0) {ry0 = dc2 - dr;}}//&& or if?
    else {
      if (dx0 > 0){ t1 = dc2 - sqrt(dx0);} else {t1 = dc2 - sqrt(dx1);}  //intersection only with x = x1 
      if (dx1 > 0){
        t2 = dc2 - sqrt(dx1);
        if(t2 < t1) {t1 = t2;} //min {t1,t2}
      }
      if (t1 > ry0){ry0 = t1;} //max{y0, min{t1,t2}}
    }
  }
  //left half-plane and right half of the disk 
  if ((dc1 < rx0) && (dx0 > 0)){
    t1 = dc2 - sqrt(dx0);
    t2 = dc2 + sqrt(dx0);
    if(t1 > ry0 && t1 < ry1){ ry0 = t1;}
    if(t2 > ry0 && t2 < ry1){ ry1 = t2;}
    if((dc2 >= ry0) && (dc2 <= ry1)) {if ((dc1 + dr) < rx1) {rx1 = dc1 + dr;}}//&& or if?
    else {
      if (dy0 > 0){ t1 = dc1 + sqrt(dy0);} else {t1 = dc1 + sqrt(dy1);}//intersection only with y = y1 
      if (dy1 > 0){
        t2 = dc1 + sqrt(dy1);
        if(t2 > t1) {t1 = t2;} //max{t1,t2}
      }
      if (t1 < rx1){rx1 = t1;} //min{x1, max{t1,t2}}
    }
  }
  //right half-plane and left half of the disk
  if ((dc1 > rx1) && (dx1 > 0)){
    t1 = dc2 - sqrt(dx1);
    t2 = dc2 + sqrt(dx1);
    if(t1 > ry0 && t1 < ry1){ ry0 = t1;}
    if(t2 > ry0 && t2 < ry1){ ry1 = t2;}
    if((dc2 >= ry0) && (dc2 <= ry1)) {if ((dc1 - dr) > rx0) {rx0 = dc1 - dr;}}//&& or if?
    else {
      if (dy0 > 0){ t1 = dc1 - sqrt(dy0);} else {t1 = dc1 - sqrt(dy1);}//intersection only with y = y1 
      if (dy1 > 0){
        t2 = dc1 - sqrt(dy1);
        if(t2 < t1) {t1 = t2;} //min{t1,t2}
      }
      if (t1 > rx0){rx0 = t1;} //max{x0, min{t1,t2}}
    }
  }
  newR = Rect(rx0, ry0, rx1, ry1);
  return newR;
}
 

