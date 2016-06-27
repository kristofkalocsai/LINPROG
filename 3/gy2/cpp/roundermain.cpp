#include "rounder.h"
#include <iostream>

using namespace std;

int main()
{
  double x = 4.2;
  
  Rounder r;
  cout << r.Round(x) << endl;
  
  return 0;
}
