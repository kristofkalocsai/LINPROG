#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <values.h>
#include "kozos.h"

int semlocknowait(int semid, int member);
int semlockwait(int semid, int member);
int semunlock(int semid, int member);

int main()
{
    key_t key;
    int semid;
    int i;
    int semCntMin = MAXINT;
    int semCnt;
    int semMinQueue = 0;
    int locked = -1;


    key = ftok("." , 's');
    semid = semget(key, 0, 0);

    if (semid < 0) {
        perror("semget");
        return 1;
    }

    for (i = 0; i < SEM_MAX; i++) {
        int ret = semlocknowait(semid, i);
        if(ret == 0){
            // seikeres lock
            locked = i;
            break;
        }
        else if (ret < 0){
            // foglalt
            semCnt = semctl(semid, i, GETNCNT, 0);
            if (semCnt < semCntMin) {
                semCntMin = semCnt;
                semMinQueue = i;
            }
            printf("A %d. pultnal %d utas varakozik.\n", i,semCnt);
        }
    }
    if (locked < 0) {
        printf("Mindenhol allnak. A legrovidebb sor a %d. pultnal van %d utassal\n", semMinQueue, semCntMin);
        if (semlockwait(semid, semMinQueue) < 0) {
                return 1;
        }
        locked = semMinQueue;
    }

    // valamelyik semafor lockolva
    printf("Kiszolgalnak minket a %d. pultnal\n", locked);
    printf("Nyomj entert a pult elhagyasahoz!\n");

    getchar();
    if (semunlock(semid, locked) < 0) {
        return 1;
    }

    return 0;
}

int semlocknowait(int semid, int member)
{
  struct sembuf sem_lock = { 0, -1, IPC_NOWAIT };
  sem_lock.sem_num = member;

  if(semop(semid, &sem_lock, 1) < 0)
  {
    return -1;
  }

  printf("A %d. pult szabad.\n", member);
  return 0;
}

int semlockwait(int semid, int member)
{
  struct sembuf sem_lock = { 0, -1, 0 };
  sem_lock.sem_num = member;

  if(semop(semid, &sem_lock, 1) < 0)
  {
    return -1;
  }

  printf("A %d. pult szabad.\n", member);
  return 0;
}

int semunlock(int semid, int member)
{
  struct sembuf sem_lock = { 0, 1, 0 };
  sem_lock.sem_num = member;

  if(semop(semid, &sem_lock, 1) < 0)
  {
    return -1;
  }

  printf("A %d. pultot elhagyta az utas.\n", member);
  return 0;
}
