#include "rounder2.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <dlfcn.h>

using namespace std;

const char* pluginPath = "./libuprounder.so.1";

int main(int argc, char **argv)
{
  void *handle;
  
  create_t createFuncPtr;
  destroy_t destroyFuncPtr;
  
  char *error;
  
  // Megnyitjuk a konyvtarat.
  handle = dlopen(pluginPath, RTLD_LAZY);
  if(!handle)
  {
    fputs(dlerror(), stderr);
    exit(1);
  }
  
  // Hozzaferunk a create szimbolumhoz.
  createFuncPtr = (create_t) dlsym(handle, "create");
  if((error = dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }
  
  // Hozzaferunk a destroy szimbolumhoz.
  destroyFuncPtr = (destroy_t)dlsym(handle, "destroy");
  if((error = dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }
  
  double x = 4.2;
  
  // Letrehozunk egy Rounder tipusu objektumot
  Rounder* r = (*createFuncPtr)();
  cout << r->Round(x)<<endl;
  
  // Felszabaditjuk a Rounder objektumot
  (*destroyFuncPtr)(r);
  
  // Felszabaditjuk a konyvtarat
  dlclose(handle);
  
  return 0;
}
