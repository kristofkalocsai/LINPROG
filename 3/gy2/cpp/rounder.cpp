#include <math.h>
#include <stdio.h>
#include "rounder.h"

int Rounder::Round(double x)
{
  double ix;
  ix = (int)x;
  return ix < x ? ix+1 : ix;
}

