#include "Geom.h"
#include "Disk.h"
#include "Rect.h"
#include "Cost.h"
#include <iostream>
#include "math.h"

using namespace std;

//--------------constructor------------------------------------
Geom::Geom(double c1, double c2, double r, double t, Cost cst){ // start geom
  label_t = t;
  rect_t = Rect(c1-r, c2-r, c1+r, c2+r);
  cost_t = cst;
}

Geom::Geom(double m_ipen, int t){
  label_t = t;
  rect_t = Rect();
  cost_t = Cost(m_ipen);
}

Geom::Geom(double lbl, Cost cst, Rect rct){
  label_t = lbl;
  rect_t = rct;
  cost_t = cst;
}
//--------------accessory------------------------------------
unsigned int Geom::get_label_t(){return label_t;}
Rect Geom::get_rect_t(){return rect_t;}
Cost Geom::get_cost_t(){return cost_t;}
//--------------min max------------------------------------
double Geom::min_ab(double a, double b){
 if (a < b) {return a;} else {return b;}
}
double Geom::max_ab(double a, double b){
  if (a > b) {return a;} else {return b;}
}
//--------------empty_set------------------------------------
bool Geom::empty_set(Rect rect){        //checking for emptiness of an approximated set 
  double x0 = rect.get_rectx0();        //parameters of the rectangle 
  double x1 = rect.get_rectx1();
  double y0 = rect.get_recty0();
  double y1 = rect.get_recty1();
  if (x0 >= x1 || y0 >= y1){return true;} else {return false;} 
}
  //--------------intersection------------------------------------  
Rect Geom::intersection(Rect rect, Disk disk){//// intersection approximation
  double r = disk.get_radius();         //parameters of the disk
  double c1 = disk.get_center1();
  double c2 = disk.get_center2();
  
  double x0 = rect.get_rectx0();       //parameters of the rectangle 
  double x1 = rect.get_rectx1();  
  double y0 = rect.get_recty0();
  double y1 = rect.get_recty1();
  bool fl = true;// empty set
  
  //approximation//
  
  // horizontal direction: boundary y0, y1
  if (c1 >= x0 && c1 <= x1){  //boundary point is inside [x0,x1]
    y0 = max_ab(y0, c2 - r);
    y1 = min_ab(y1, c2 + r);
    fl = false;
  }
  else{
    //discriminant/4 if  dxi =< 0 - no intersection points with a line x = xi,
    //if  dxi > 0 - two intersection points with a line x = xi
    double dl = r * r - (x0 - c1) * (x0 - c1);//x = x0
    double dr = r * r - (x1 - c1) * (x1 - c1);//x = x1
    if(dl > 0 || dr > 0){ 
      double l1 = INFINITY; // intersection points 
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
      y0 = max_ab(y0, min_ab(l1, r1));//y0 = max{y0, min{l1, r1}}
      y1 = min_ab(y1, max_ab(l2, r2));//y1 = min{y1, max{l2, r2}}
      fl = false;
    }
  }
  // vertical direction:boundary x0, x1 
  if (c2 >= y0 && c2 <= y1){  //boundary point is inside [y0,y1]
    x0 = max_ab(x0, c1 - r);  //x0 = max{x0, c1-r}
    x1 = min_ab(x1, c1 + r);  //x1 = min{x1, c1+r}
    fl = false;
  }
  else{ 
    double db = r * r - (y0 - c2) * (y0 - c2);//y = y0
    double dt = r * r - (y1 - c2) * (y1 - c2);//y = y1
    if(db > 0 || dt > 0){ 
      double b1 = INFINITY; // intersection points
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
      x0 = max_ab(x0, min_ab(b1, t1)); //x0 = max{x0, min{b1, t1}}
      x1 = min_ab(x1, max_ab(b2, t2)); //x1 = min{x1, max{b2, t2}}
      fl = false;
      }
    }
    if (fl) {x0 = x1;}  //empty set
  Rect rect_approx = Rect(x0, y0, x1, y1); // intersection approximation
  return rect_approx;
}
//--------------difference------------------------------------  
Rect Geom::difference(Rect rect, Disk disk){// difference approximation
  double r = disk.get_radius();         //parameters of the disk
  double c1 = disk.get_center1();
  double c2 = disk.get_center2();

  double x0 = rect.get_rectx0();       //parameters of the rectangle 
  double x1 = rect.get_rectx1();  
  double y0 = rect.get_recty0();
  double y1 = rect.get_recty1();
  //approximation//
  
  // horizontal direction: boundary y0, y1
  
  //discriminant/4 if  dxi =< 0 - no intersection points with a line x = xi,
  //if  dxi > 0 - two intersection points with a line x = xi
  double dl = r * r - (x0 - c1) * (x0 - c1);//x = x0
  double dr = r * r - (x1 - c1) * (x1 - c1);//x = x1
  if(dl > 0 && dr > 0){ 
    double l1 = INFINITY;  // intersection points
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
    y0 = max_ab(y0, min_ab(l2, r2));  //y0 = max{y0, min{l2, r2}}
    y1 = min_ab(y1, max_ab(l1, r1));  //y1 = min{y1, max{l1, r1}}
  }
  
  // vertical direction:boundary x0, x1 
  
  //discriminant/4 if  dyi =< 0 - no intersection points with a line y = yi,
  //if  dyi > 0 - two intersection points with a line y = yi
  double db = r * r - (y0 - c2) * (y0 - c2);//y = y0
  double dt = r * r - (y1 - c2) * (y1 - c2);//y = y1
  if(dt > 0 && db > 0){ 
    double b1 = INFINITY; // intersection points
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
    x0 = max_ab(x0, min_ab(b2, t2));//x0 = max{x0, min{b2, t2}}
    x1 = min_ab(x1, max_ab(b1, t1));//x1 = min{x1, max{b1, t1}}
  }
  Rect rect_approx = Rect(x0, y0, x1, y1); // difference approximation
  return rect_approx;
}
