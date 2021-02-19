#include "Rect.h"
#include "Disk.h"
#include "math.h"
#include<iostream>

using namespace std;

//############################## constructor #####################################//
Rect::Rect(){
  rectx0 = -INFINITY;    
  recty0 = -INFINITY;
  rectx1 = INFINITY;
  recty1 = INFINITY;
}
Rect::Rect(double x0, double y0, double x1, double y1){
  rectx0 = x0;    
  recty0 = y0;
  rectx1 = x1;
  recty1 = y1;
}

Rect::Rect(double c1, double c2, double r){
  rectx0 = c1 - r;    
  recty0 = c2 - r;
  rectx1 = c1 + r;
  recty1 = c2 + r;
}

//############################## accessory #######################################//
double Rect::get_rectx0(){return rectx0;}
double Rect::get_recty0(){return recty0;}
double Rect::get_rectx1(){return rectx1;}
double Rect::get_recty1(){return recty1;}

//############################## min max #########################################//
double Rect::min_ab(double a, double b){if (a < b) {return a;} else {return b;}}
double Rect::max_ab(double a, double b){if (a > b) {return a;} else {return b;}}

//############################## intersection ####################################//  
void Rect::intersection(Disk disk){
  double r = disk.get_radius();        
  double c1 = disk.get_center1();                       //parameters of the disk
  double c2 = disk.get_center2();
  
  bool fl = true;                                       // empty set
  //----------------------------------------------------------------------------
  //----------------------approximation-----------------------------------------
  
  //--------------------horizontal direction: boundary y0, y1-------------------
  if (c1 >= rectx0 && c1 <= rectx1){ 
    recty0 = max_ab(recty0, c2 - r);          //boundary point is inside [x0,x1]
    recty1 = min_ab(recty1, c2 + r);
    fl = false;
  }
  else{
    //discriminant/4 if  dxi =< 0 - no intersection points with a line x = xi,
    //if  dxi > 0 - two intersection points with a line x = xi
    double dl = r * r - (rectx0 - c1) * (rectx0 - c1);    //x = x0
    double dr = r * r - (rectx1 - c1) * (rectx1 - c1);    //x = x1
    if(dl > 0 || dr > 0){ 
      double l1 = INFINITY;                               // intersection points 
      double r1 = INFINITY;
      double l2 = -INFINITY;
      double r2 = -INFINITY;
      if (dl > 0){
        l1 = c2 - sqrt(dl);
        l2 = c2 + sqrt(dl);
      }
      if (dr > 0){
        r1 = c2 - sqrt(dr);
        r2 = c2 + sqrt(dr);
      }
      recty0 = max_ab(recty0, min_ab(l1, r1));//y0 = max{y0, min{l1, r1}}
      recty1 = min_ab(recty1, max_ab(l2, r2));//y1 = min{y1, max{l2, r2}}
      fl = false;
    }
  }
  //--------------------vertical direction:boundary x0, x1---------------------- 
  if (c2 >= recty0 && c2 <= recty1){                  //boundary point is inside [y0,y1]
    rectx0 = max_ab(rectx0, c1 - r);                        //x0 = max{x0, c1-r}
    rectx1 = min_ab(rectx1, c1 + r);                        //x1 = min{x1, c1+r}
    fl = false;
  }
  else{ 
    double db = r * r - (recty0 - c2) * (recty0 - c2);              //y = y0
    double dt = r * r - (recty1 - c2) * (recty1 - c2);              //y = y1
    if(db > 0 || dt > 0){ 
      double b1 = INFINITY;                                 //intersection points
      double t1 = INFINITY;
      double b2 = -INFINITY;
      double t2 = -INFINITY;
      if (db > 0){
        b1 = c1 - sqrt(db);
        b2 = c1 + sqrt(db);
      }
      if (dt > 0){
        t1 = c1 - sqrt(dt);
        t2 = c1 + sqrt(dt);
      }
      rectx0 = max_ab(rectx0, min_ab(b1, t1)); //x0 = max{x0, min{b1, t1}}
      rectx1 = min_ab(rectx1, max_ab(b2, t2)); //x1 = min{x1, max{b2, t2}}
      fl = false;
    }
  }
  if (fl) {rectx0 = rectx1;}  //empty set
}

//##############################difference######################################//
void Rect::difference(Disk disk){
  double r = disk.get_radius();                         //parameters of the disk
  double c1 = disk.get_center1();
  double c2 = disk.get_center2();
  
  //----------------------------------------------------------------------------
  //----------------------approximation-----------------------------------------
  
  //--------------------horizontal direction: boundary y0, y1-------------------
  
  //discriminant/4 if  dxi =< 0 - no intersection points with a line x = xi,
  //if  dxi > 0 - two intersection points with a line x = xi
  double dl = r * r - (rectx0 - c1) * (rectx0 - c1);      //x = x0
  double dr = r * r - (rectx1 - c1) * (rectx1 - c1);      //x = x1
  if(dl > 0 && dr > 0){ 
    double l1 = INFINITY;                                 //intersection points
    double r1 = INFINITY;
    double l2 = -INFINITY;
    double r2 = -INFINITY;
    if (dl > 0){
      l1 = c2 - sqrt(dl);
      l2 = c2 + sqrt(dl);
    }
    if (dr > 0){
      r1 = c2 - sqrt(dr);
      r2 = c2 + sqrt(dr);
    }
    recty0 = max_ab(recty0, min_ab(l2, r2));            //0 = max{y0, min{l2, r2}}
    recty1 = min_ab(recty1, max_ab(l1, r1));            //y1 = min{y1, max{l1, r1}}
  }
  
  //------------------vertical direction:boundary x0, x1------------------------ 
  
  //discriminant/4 if  dyi =< 0 - no intersection points with a line y = yi,
  //if  dyi > 0 - two intersection points with a line y = yi
  
  double db = r * r - (recty0 - c2) * (recty0 - c2);    //y = y0
  double dt = r * r - (recty1 - c2) * (recty1 - c2);    //y = y1
  if(dt > 0 && db > 0){ 
    double b1 = INFINITY;                               //intersection points
    double t1 = INFINITY;
    double b2 = -INFINITY;
    double t2 = -INFINITY;
    if (db > 0){
      b1 = c1 - sqrt(db);
      b2 = c1 + sqrt(db);
    }
    if (dt > 0){
      t1 = c1 - sqrt(dr);
      t2 = c1 + sqrt(dr);
    }
    rectx0 = max_ab(rectx0, min_ab(b2, t2));          //x0 = max{x0, min{b2, t2}}
    rectx1 = min_ab(rectx1, max_ab(b1, t1));          //x1 = min{x1, max{b1, t1}}
  }
}
//############################## End #############################################//



