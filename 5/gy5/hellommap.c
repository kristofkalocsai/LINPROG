// fajl tartalmat lekepezi a memoriaba, igy nem kell olvasgatni, csokken a memoriafelhasznalas, igeny szerint lapozhatunk
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
  int fd;
  char* mem;

  if(argc != 2)
  {
    printf("Használat: %s állomány\n", argv[0]);
    return EXIT_FAILURE;
  }

  if((fd = open(argv[1], O_RDONLY)) < 0)
  {
    perror("open");
    return EXIT_FAILURE;
  }

  if ((mem = mmap(0, 256, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED) {
      perror("mmap");
      return EXIT_FAILURE;
  }

  write(STDOUT_FILENO, mem, 256); // kezelni kene hogy mennyit sikerult kiirni, ciklust csinalni ra


  munmap(mem, 256); // igazabol a close is megcsinalja, de igy a korrekt
  close(fd);
  return EXIT_SUCCESS;
}
