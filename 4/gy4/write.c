#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    int fd;

  if(argc < 2)
  {
    printf("usage: %s filename\n", argv[0]);
    return 1;
  }
  fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
  if(fd < 0){
      perror("open");
      return 1;
  }

  if(write(fd, "HELLO WORLD!\n", 13) != 13){
      perror("write");
      return 1;
  }

  close(fd); // igazabol nem is szukseges, ha vege a processnek, bezarodik
  return 0;
}
