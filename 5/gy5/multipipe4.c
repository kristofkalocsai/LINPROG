#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
  int fds[2];
  char buf[256];
  int len;
  int fdix;

  fds[0] = open("pipe1", O_RDONLY | O_NONBLOCK);
  if(fds[0] < 0)
  {
    perror("open pipe1");
    return EXIT_FAILURE;
  }

  fds[1] = open("pipe2", O_RDONLY | O_NONBLOCK);
  if(fds[1] < 0)
  {
    perror("open pipe2");
    return EXIT_FAILURE;
  }

  fdix = 0;
  while(1)
  {
    len = read(fds[fdix], buf, sizeof(buf));
    if(len == 0)
    {
      printf("A pipe%d lezarult!\n", fdix + 1);
      break;
    }
    else if((len < 0) && (errno != EAGAIN))
    {
      perror("read");
      return EXIT_FAILURE;
    }
    else
    {
      write(STDOUT_FILENO, buf, len);
    }
    fdix = (fdix + 1) % 2;
    usleep(10);
  }

  close(fds[0]);
  close(fds[1]);

  return EXIT_SUCCESS;
}
