#include <math.h>

int roundingMethod = 0;
extern int errorCode; // nem itt van deklaralva, itt csak hasznaljuk -> lib ben is lehet globalis valtozo!

double round(double x)
{
  double ix;
  int sign = x < 0 ? -1 : 1;;

  if((roundingMethod < 0) || (roundingMethod > 2))
  {
        errorCode = -1;
        return 0;
  }
  else
  {
        errorCode = 0;
  }
  ix = (int)x;
  switch(roundingMethod)
  {
   case 0: // felkerekit
          return x - ix <= 0 ? ix : ix+1;
   case 1: // lekerekit
          return x - ix >= 0 ? ix: ix-1;
   case 2: // kerekites
          if(fabs(x-ix) >0.5)
          {
                return ix + sign;
          }
          else
          {
                return ix;
          }
   }
   return 0;
}
