#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static volatile sig_atomic_t timer;

static void timer_handler()
{
  timer = 1;
}

int main()
{
  sigset_t alarmMask, suspendMask;
  struct sigaction sa, saold;
  timer = 0;

  sigemptyset(&alarmMask);
  sigaddset(&alarmMask, SIGALRM);

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = timer_handler;
  sigaction(SIGALRM, &sa, &saold);

  sigprocmask(SIG_BLOCK, &alarmMask, &suspendMask);
  sigdelset(&suspendMask, SIGALRM);


  alarm(10); // 10 masodperc múlva SIGALRM jelzés

  while (!timer) {
      sigsuspend(&suspendMask);

  }

  printf("Megerkezett\n");

  return(alarm(0)); // Kikapcsoljuk az idozitot
}
