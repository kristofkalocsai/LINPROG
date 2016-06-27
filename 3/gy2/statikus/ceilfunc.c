/* ceilfunc.c */
double ceil(double x) 
{
  double ix=(int)x;
  return ix<x?ix+1:ix;
}

