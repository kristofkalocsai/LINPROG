#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
  sigset_t alarmMask;
  
  sigemptyset(&alarmMask);
  sigaddset(&alarmMask, SIGALRM);
  
  // Az SIGALRM letiltása
  sigprocmask(SIG_BLOCK, &alarmMask, NULL);
  
  alarm(10); // 10 masodperc múlva SIGALRM jelzés
  
  if(sigwaitinfo(&alarmMask, NULL) < 0)
  {
    perror("sigwaitinfo");
  }
  else
  {
    printf("Megerkezett\n");
  }
  
  return(alarm(0)); // Kikapcsoljuk az idozitot
}

