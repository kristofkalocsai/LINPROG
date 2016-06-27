/* ceiling.c */
#include <stdio.h>

double ceil(double);

int main() 
{
  double x;
  printf("Kerem az x-et: ");
  scanf("%lf", &x);
  printf("ceil(x) = %6.4f\n", ceil(x));
  return 0;
}

