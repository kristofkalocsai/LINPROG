#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  char* path;
  int mode = 0644;
  int major = 0, minor = 0;
  char* end;
  int args;

  if(argc < 3)
  {
    fprintf(stderr, "Hasznalat: %s <path> b|c|u|p <major> <minor>\n", argv[0]);
    return 1;
  }
  path = argv[1];
  if(strcmp(argv[2], "p") == 0)
  {
    mode |= S_IFIFO;
    args = 3;
  }
  else if(strcmp(argv[2], "b") == 0)
  {
    mode |= S_IFBLK;
    args = 5;
  }
  else if((strcmp(argv[2], "c") == 0) || (strcmp(argv[2], "u") == 0))
  {
    mode |= S_IFCHR;
    args = 5;
  }

  if(argc < args)
  {
    fprintf(stderr, "Hasznalat: %s <path> b|c|u|p <major> <minor>\n", argv[0]);
    return 1;
  }
  if(args == 5)
  {
    major = strtol(argv[3], &end, 0);
    if(*end)
    {
      fprintf(stderr, "Rossz major szam\n");
      return 1;
    }

    minor = strtol(argv[4], &end, 0);
    if(*end)
    {
      fprintf(stderr, "Rossz minor szam\n");
      return 1;
    }
  }

  if(mknod(path, mode, makedev(major,minor)) < 0){
      perror("mknod");
      return 1;
  }

  return 0;
}
