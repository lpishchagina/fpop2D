#ifndef DISK_H
#define DISK_H

#include < math.h >
#include < list >
#include < iterator >

class Disk{
public:
  Disk(double dc1, double dc2, double dr);
  double get_r();
  double get_c1();
  double get_c2();
  
  std::list < Disk > add_disk(Disk* D);
  
  std::list < Disk > del_disk(Disk* D);
  
  std::list < Disk > get_list_disk();
  
private:
  double c1;    // coordinates of center
  double c2;
  double r;     // radius
  std::list < Disk > list_disk;   //set of disks
};

#endif //DISK_H