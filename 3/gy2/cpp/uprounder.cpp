#include <math.h>
#include <stdio.h>
#include "rounder2.h"

class UpRounder: public Rounder
{
  int Round(double);
};

int UpRounder::Round(double x)
{
  double ix;
  ix = (int)x;
  return ix < x ? ix+1 : ix;
}

extern "C" Rounder* create()
{
  return new UpRounder();
}

extern "C" void destroy(Rounder* object)
{
  delete object;
}


