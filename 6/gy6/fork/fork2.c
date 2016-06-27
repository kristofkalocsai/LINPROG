#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int child(int fd)
{
    char buf[64];
    int len;
    printf("Ez a gyerek. PID: %d (A szulo: %d)\n", getpid(), getppid());
    len = read(fd, buf, sizeof(buf));
    if (len > 0) {
        write(STDOUT_FILENO, "Ez a gyerek: ", 13);
        write(STDOUT_FILENO, buf, len);
    }
    printf("Gyerek vege.\n");
    return 0;
}

int main(int argc, char* argv[])
{
  int pid;
  // unnamed pipe a kommunikaciohoz
  int fds[2];

  printf("A program elindul...\n");
  // meg a fork elott hozzuk letre!
  pipe(fds);
  // gyerek is orokli!

  pid = fork();
  if(pid < 0)
  {
    perror("fork");
    return 1;
  }
  else if(pid == 0)
  {
    // gyerek
    close(fds[1]);
    return child(fds[0]);
  }

  // szulo
  close(fds[0]);
  printf("Ez a szulo. PID: %d (A gyerek: %d)\n", getpid(), pid);
  write(fds[1], "Hello kisfiam!\n", 15);

  wait(NULL);

  printf("Szulo vege.\n");
  return 0;
}
