// kb soha nem hasznalatos, csak megnezzuk hogy ilyen is van
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

#define F_SETSIG       10

void sigread(int sig, siginfo_t* info, void* data)
{
  static int res;
  static char buf[256];

  //if(info->si_code != SI_SIGIO) return;

  res = read(info->si_fd, buf, sizeof(buf));
  if(res < 0)
  {
    perror("read");
  }
  else if(res == 0)
  {
    close(info->si_fd);
    exit(0);
  }
  else
  {
    write(STDOUT_FILENO, buf, res);
  }
}

int main(int argc, char* argv[])
{
  int fd;
  struct sigaction sigio;  // erre a signalra hivodjon meg ez a fv

  if(argc < 2)
  {
    printf("Usage: %s file\n", argv[0]);
    return -1;
  }

  if((fd = open(argv[1], O_RDONLY)) < 0)
  {
    perror("open");
    return -1;
  }

  bzero(&sigio, sizeof(sigio));
  sigio.sa_sigaction = sigread;
  sigio.sa_flags = SA_SIGINFO;  // kiterjesztett struktura hogy tobb fajlt is kezelni tudjunk
  sigaction(SIGIO,&sigio,NULL);  // SIGIO signalra allitsa be a sigio strukturat ~callback

  /* Beállítjuk, hogy az állomány SIGIO szignáljai hozzánk érkezzenek. */
  fcntl(fd, F_SETOWN, getpid());
  /* Átállítjuk a SIGIO szignált, hogy használhassuk a SIGINFO kiterjesztést. */
  fcntl(fd, F_SETSIG, SIGIO);
  /* Bekapcsoljuk a SIGIO szignálok generálását. */
  fcntl(fd, F_SETFL, O_ASYNC);

  while(1)
  {
    sleep(1);
  }

  return 0;
}
