#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/signalfd.h>
#include <fcntl.h>
#include <poll.h>

int main()
{
  sigset_t alarmMask;
  int fd;
  struct pollfd pollset[2];
  struct signalfd_siginfo info;
  
  sigemptyset(&alarmMask);
  sigaddset(&alarmMask, SIGALRM);
  
  // Az SIGALRM letiltása
  sigprocmask(SIG_BLOCK, &alarmMask, NULL);
  
  fd = signalfd(-1, &alarmMask, SFD_NONBLOCK);
  
  alarm(10); // 10 masodperc múlva SIGALRM jelzés
  
  // A select az stdinnre es a jelzes leirojara figyel
  pollset[0].fd = STDIN_FILENO;
  pollset[0].events = POLLIN;
  pollset[1].fd = fd;
  pollset[1].events = POLLIN;
  
  if(poll(pollset, 2, -1) > 0)
  {
    if(pollset[1].revents & POLLIN)
    {		
      if(read(fd, &info, sizeof(struct signalfd_siginfo)) > 0)
      {
	printf("%d processz jelzest kuldott.\n", info.ssi_pid);
      }
    }
  }
  
  close(fd);
  
  printf("Megerkezett vagy megnyomtak.\n");
  
  return(alarm(0)); // Kikapcsoljuk az idozitot
}

