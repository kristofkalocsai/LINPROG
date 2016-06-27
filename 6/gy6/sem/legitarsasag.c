#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "kozos.h"

int main()
{
  key_t key;
  int semid;
  union semun semopts;
  int i;

  key = ftok(".", 's');
  semid = semget(key, SEM_MAX, IPC_CREAT | IPC_EXCL | 0666);
  if(semid < 0)
  {
    perror("semget");
    return 1;
  }

  semopts.val = SEM_INIT;
  for(i = 0; i < SEM_MAX; i++)
  {
    semctl(semid, i, SETVAL, semopts);
    printf("%d. szemafor ertek: %d\n", i, 
      semctl(semid, i, GETVAL, 0));
  }
  printf("A legitarsasag kesz. Kulcs: %d\n", key);
  printf("Nyomj Entert a kilepeshez!\n");
  getchar();

  semctl(semid, 0, IPC_RMID, 0);
  printf("A legitarsasag bezart.\n");

  return 0;
}
