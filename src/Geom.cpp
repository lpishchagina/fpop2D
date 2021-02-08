#include "Geom.h"
#include "Disk.h"
#include "Rect.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//--------------accessory------------------------------------
unsigned int Geom::get_label(){return label;}
//Rect Geom::get_rect(){return rectangle;}

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
  
  //approximation//
  if ((c1 >= x0) && (c1 <= x1) && (c2 >= y0) && (c2 <= y1)){        // the center of the disk inside the rectangle
    if (c1-r > x0){x0 = c1-r;}
    if (c2-r > y0){y0 = c2-r;}
    if (c1+r < x1){x1 = c1+r;}
    if (c2+r < y1){y1 = c2+r;}
  }
  else{
    //discriminant/4 if  dxi =< 0 - no intersection points with a line x = xi,
    //if  dxi > 0 - two intersection points with a line x = xi
    double dl = r * r + (x0 - c1) * (x0 - c1);//x = x0
    double dr = r * r + (x1 - c1) * (x1 - c1);//x = x1
    double db = r * r + (y0 - c2) * (y0 - c2);//y = y0
    double dt = r * r + (y1 - c2) * (y1 - c2);//y = y1
    
    if (dl <= 0 && dr <= 0 && db <= 0 && dt <= 0){
      x1 = x0;      //empty set
    }
    else{  
      if(dl > 0 || dr > 0){ // horizontal direction: boundary y0, y1 
        if (c1 >= x0 && c1 <= x1){  //boundary point is inside [x0,x1]
          if(y0 < c2-r){y0 = c2-r;} //y0 = max{y0, c2-r}
          if(y1 > c2+r){y1 = c2+r;} //y1 = min{y1, c2+r}
        }
        else{ 
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
          if(l1 > r1){l1 = r1;} //min{l1, r1}
          if(l2 < r2){l2 = r2;} //max{l2, r2}
          
          if(y0 < l1){y0 = l1;} //y0 = max{y0, min{l1, r1}}
          if(y1 > l2){y1 = l2;} //y1 = min{y1, max{l2, r2}}
          
        } //else
      } //if(dl > 0 || dr > 0)
      
      if(dt > 0 || db > 0){ // vertical direction:boundary x0, x1 
        if (c2 >= y0 && c2 <= y1){  //boundary point is inside [y0,y1]
          if(x0 < c1-r){x0 = c1-r;} //x0 = max{x0, c1-r}
          if(x1 > c1+r){x1 = c1+r;} //x1 = min{x1, c1+r}
        }
        else{ 
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
          if(b1 > t1){b1 = t1;} //min{b1, t1}
          if(b2 < t2){b2 = t2;} //max{b2, t2}
          
          if(x0 < b1){x0 = b1;} //x0 = max{x0, min{b1, t1}}
          if(x1 > b2){x1 = b2;} //x1 = min{x1, max{b2, t2}}
        }//else
      }//if(dt > 0 || db > 0)
    }//else
  }//else
  Rect rect_approx = Rect(x0, y0, x1, y1); // intersection approximation
  return rect_approx;
}
//--------------substraction------------------------------------  
Rect Geom::substraction(Rect rect, Disk disk){// substraction approximation
  double r = disk.get_radius();         //parameters of the disk
  double c1 = disk.get_center1();
  double c2 = disk.get_center2();

  double x0 = rect.get_rectx0();       //parameters of the rectangle 
  double x1 = rect.get_rectx1();  
  double y0 = rect.get_recty0();
  double y1 = rect.get_recty1();

  //discriminant/4 if  dxi =< 0 - no intersection points with a line x = xi,
  //if  dxi > 0 - two intersection points with a line x = xi
  double dl = r * r + (x0 - c1) * (x0 - c1);//x = x0
  double dr = r * r + (x1 - c1) * (x1 - c1);//x = x1
  double db = r * r + (y0 - c2) * (y0 - c2);//y = y0
  double dt = r * r + (y1 - c2) * (y1 - c2);//y = y1

  //approximation//
  if(dl > 0 && dr > 0 && db > 0 && dt > 0){x0 = x1;}// // the rectangle is inside the disk =>  substraction = empty set
  else{
    if(dl > 0 || dr > 0){ // horizontal direction: boundary y0, y1 
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
      if(r1 > l1){l1 = r1;} //max{l1, r1}
      if(l2 > r2){l2 = r2;} //min{l2, r2}
      
      if(y0 < l2){y0 = l2;} //y0 = max{y0, min{l2, r2}}
      if(y1 > l1){y1 = l1;} //y1 = min{y1, max{l1, r1}}
    } //if(dl > 0 || dr > 0)
  
    if(dt > 0 || db > 0){ // vertical direction:boundary x0, x1 
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
      if(t1 > b1){b1 = t1;} //max{b1, t1}
      if(b2 > t2){b2 = t2;} //min{b2, t2}
      
      if(x0 < b2){x0 = b2;} //x0 = max{x0, min{b2, t2}}
      if(x1 > b1){x1 = b1;} //x1 = min{x1, max{b1, t1}}
    }//if(dt > 0 || db > 0)
  }//else
  Rect rect_approx = Rect(x0, y0, x1, y1); // substraction approximation
  return rect_approx;
}
