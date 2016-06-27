#include <signal.h>
#include <unistd.h>
#include <stdio.h>


// program foszalaban sleep() helyett lehet ezt hasznalni!
int main()
{
  sigset_t alarmMask;

  sigemptyset(&alarmMask);
  sigaddset(&alarmMask, SIGALRM); // alarm mask

  sigprocmask(SIG_BLOCK, &alarmMask, NULL); // tiltsuk, hogy ne aszinkron modon kezelodjon le



  alarm(10); // 10 masodperc múlva SIGALRM jelzés

  if (sigwaitinfo(&alarmMask, NULL) < 0) {
      perror("sigwaitinfo");
  }
  else {
      printf("Megerkezett!\n");
  }

  return(alarm(0)); // Kikapcsoljuk az idozitot
}
