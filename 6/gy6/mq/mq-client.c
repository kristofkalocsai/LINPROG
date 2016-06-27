#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "mq.h"

int main(int argc, char* argv[])
{
  key_t key;
  int msgid;
  struct persmsg msg;
  
  key = ftok(".", 'm');
  msgid = msgget(key, 0);
  if(msgid < 0)
  {
    perror("msgget");
    return 1;
  }

  printf("Nev: ");
  scanf("%39[^\n]", msg.data.nev);
  printf("Neptun: ");
  scanf("%6s", msg.data.neptun);
  msg.mtype = MSG_TYPE;

  if(msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) < 0)
  {
    perror("msgsnd");
    return 1;
  }
  printf("A regisztracio megtortent.\n");
  
  return 0;
}
