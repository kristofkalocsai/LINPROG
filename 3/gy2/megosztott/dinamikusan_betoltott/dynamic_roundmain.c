// dynamic_roundmain.c
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> //dinamic library functions
#include "round.h"

int errorCode;
const char* pluginPath = "./libround.so.1";

int main(int argc, char **argv)
{
  void *handle;
  double (*round)(double);
  int* roundingMethod;
  char *error;

  /* Megnyitjuk a konyvtarat. */
  handle = dlopen(pluginPath, RTLD_LAZY);
  if(!handle)
  {
    fputs(dlerror(), stderr);
    exit(1);
  }
  /* Hozzaferunk a round szimbolumhoz. */
  round = dlsym(handle, "round");
  if((error = dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }
  /* Hozzaferunk a roundingMethod szimbolumhoz. */
  roundingMethod = dlsym(handle, "roundingMethod");
  if((error = dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }
  double x= 4.2;
  *roundingMethod =0;
  printf("%lf\n", round(x));
  *roundingMethod =1;
  printf("%lf\n", round(x));
  *roundingMethod =2;
  printf("%lf\n", round(x));
  *roundingMethod =3;
  round(x);
  printf("%d\n",errorCode);
  /* felszabaditjuk a konyvtarat */
  dlclose(handle);

  return 0;
}
