#ifndef DISK_H
#define DISK_H

#include < math.h >

class Disk{
public:
  //--------------constructor------------------------------------
  Disk();
  Disk(double c1, double c2, double r);
  //--------------accessory------------------------------------
  double get_radius();
  double get_center1();
  double get_center2();
  
private:
  double center1;    // coordinates of center
  double center2;
  double radius;     // radius
};

#endif //DISK_H