/* recordlock.c – Egyszeru pelda a record lock hasznalatara. */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* Megjeleniti az uzenetet, es var az enter billentyu 
   lenyomasara. */
void waitforuser(char* uzenet)
{
  printf("%s", uzenet);
  fflush(stdout);
  getchar();
  printf("\n");
}

/* Megszerzi az adott tipusu lockot az allomanyra. A tipus 
   ertekei az alabbiak lehetnek: F_RDLCK, F_WRLCK, vagy F_UNLCK */
void getlock(int fd, int type)
{
  struct flock lockinfo;
  char uzenet[128];

  /* Az egesz allomanyt lockoljuk. */
  lockinfo.l_whence = SEEK_SET;
  lockinfo.l_start = 0;
  lockinfo.l_len = 0;

  /* Addig probaljuk, amig sikerul. */
  while (1)
  {
    lockinfo.l_type = type;

    /* Ha sikerult megszerezni, akkor visszaterunk. */
    if(fcntl(fd, F_SETLK, &lockinfo) == 0) return;

    /* Megnezzuk ki tartja maganal. */
    fcntl(fd, F_GETLK, &lockinfo);

    /* Van ra egy kis esely, hogy az allitas es az olvasas 
       kozott a lock felszabadul. Ezert levizsgaljuk ezt az 
       esetet. */
    if(lockinfo.l_type != F_UNLCK)
    {
      sprintf(uzenet, "Konfliktus van a %d processzel... "
        "Nyomj entert!", lockinfo.l_pid);
      waitforuser(uzenet);
    }
  }
}

int main(void)
{	
  int fd;

  /* Letrehozunk egy lockolando allomanyt. */
  fd = open("testlockfile", O_RDWR | O_CREAT, 0666);
  if(fd < 0)
  {
    perror("open");
    return 1;
  }

  printf("Olvasasra lockoljuk.\n");
  getlock(fd, F_RDLCK);
  printf("A lockolas sikeres.\n");

  waitforuser("\nNyomj entert a folytatashoz!");
  
  printf("Elengedjuk a lockot.\n");
  getlock(fd, F_UNLCK);

  printf("Irasra lockoljuk\n");
  getlock(fd, F_WRLCK);
  printf("A lock-olas sikeres.\n");

  waitforuser("\nNyomj entert a kilepeshez!");

  /* Az allomany lezarasakor a lock is felszabadul. */
  close(fd);

  return 0;
}
