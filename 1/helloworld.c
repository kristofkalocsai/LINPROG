// hello world

#include <stdio.h> 
#include <unistd.h>

int main(int argv, char* argc[])
{
  printf("Hello World!");
  sleep(5);
  printf("\n"); // terminal output will only show up if a newline is sent too.
  return 0; // crucial, not like before

}