#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "sm.h"

int main()
{
  int shmid;
  char* shmptr;
  key_t key;
  key = ftok(".", 'n');
  
  shmid = shmget(key, MEMSIZE, IPC_CREAT | IPC_EXCL | 0666);
  if(shmid < 0)
  {
    perror("shmget");
    return 1;
  }
    
  shmptr = (char*)shmat(shmid, NULL, 0);
  if(shmptr == (char*)-1)
  {
    perror("shmat");
    shmctl(shmid, IPC_RMID, 0);
    return 1;
  }

  sprintf(shmptr, "Hello!");
  printf("Nyomj ENTER-t a folytatáshoz!\n");
  getchar();
  
  shmdt(shmptr);
  
  shmctl(shmid, IPC_RMID, 0);

  return 0;
}
