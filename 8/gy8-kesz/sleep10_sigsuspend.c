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
  
  // timer_handler regisztrálása a SIGALRM jelzésre
  sigemptyset(&sa.sa_mask);
  sa.sa_flags=0;
  sa.sa_handler = timer_handler;
  sigaction(SIGALRM, &sa, &saold);
  
  // Az SIGALRM letiltása
  sigprocmask(SIG_BLOCK, &alarmMask, &suspendMask);
  
  // Mask összeállítása
  sigdelset(&suspendMask, SIGALRM);
  
  alarm(10); // 10 masodperc múlva SIGALRM jelzés
  while(!timer)
  {
    // Kritikus szekció vége – SIGALRM engedélyezése, várakozás
    sigsuspend(&suspendMask); // Az átadott jelzés a SIGALRM
    // Visszatérés után a hívás előtti állapotot állítja vissza
  }
  
  printf("Megerkezett\n");
  
  sigaction(SIGALRM, &saold, 0);
  return(alarm(0)); // Kikapcsoljuk az idozitot
}

