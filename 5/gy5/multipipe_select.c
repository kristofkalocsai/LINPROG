#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>

int main(int argc, char* argv[])
{
  int fds[2];
  char buf[256];
  int len;
  int fdix;

  struct pollfd pollset[2];

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

  pollset[0].fd = fds[0];
  pollset[0].events = POLLIN;

  pollset[1].fd = fds[1];
  pollset[1].events = POLLIN;


  while(1)
  {
      if( poll(pollset, 2, -1) < 0){
          perror("poll");
          return EXIT_FAILURE;
      }

      for (fdix = 0; fdix < 2; fdix++) {
          if (pollset[fdix].revents & POLLHUP) {
              printf("A pipe%d lezarult!\n", fdix + 1);
              return EXIT_SUCCESS;
          }

          if (pollset[fdix].revents & (POLLERR | POLLINVAL)) {
              printf("read error!\n"); // nem tudunk perrort hasznalni, mert errnoban nincs benne h mi a hiba
              return EXIT_FAILURE;
          }

          if (pollset[fdix].revents & POLLIN) {
              len = read(fds[fdix], buf, sizeof(buf));

              if((len < 0) && (errno != EAGAIN)){
                  write(STDOUT_FILENO, buf, len);
              }

          }

      }

  }

  close(fds[0]);
  close(fds[1]);

  return EXIT_SUCCESS;
}
