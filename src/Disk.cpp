#include < iostream >

# include "Disk.h"

Disk::Disk(double dc1, double dc2, double dr)
{
   c1 = dc1;    // coordinates of center
   c2 = dc2;
   r = dr;  
}

double Disk::get_r() {return r;}
double Disk::get_c1(){return c1;}
double Disk::get_c2(){return c2;}
std::list < Disk > Disk::get_list_disk(){return list_disk;}
  
std::list < Disk > Disk::add_disk(Disk* D) { list_disk.push_back(D);}
std::list < Disk > Disk::del_disk(Disk* D) { list_disk.erase(D);}
