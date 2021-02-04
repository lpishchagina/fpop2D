#ifndef GEOMETRY_H
#define GEOMETRY_H

#include < math.h >
#include < vector >
#include < list >
#include < iterator >

# include "Rect.h"
# include "Disk.h"
# include "Cost.h"

class Geometry{
public:
  Geometry(){};
  
  Rect intersection (Disk D, Rect R);
  std::list < Geometry > get_list_geometry();
  
  
  
  bool empty_set(Rect R, Disk D);
  
private:
  std::list < Geometry > list_geometry;
};

#endif //GEOMETRY_H