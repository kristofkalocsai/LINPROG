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
  int len;
  char buf[1024];

  sigemptyset(&alarmMask);
  sigaddset(&alarmMask, SIGALRM); // alarm mask osszeallitasa

  sigprocmask(SIG_BLOCK, &alarmMask, NULL); // tiltsuk, hogy ne aszinkron modon kezelodjon le

  fd = signalfd(-1, &alarmMask, SFD_NONBLOCK); // igy csinalunk signalbol file leirot

  pollset[0].fd = STDIN_FILENO;
  pollset[0].events = POLLIN;

  pollset[1].fd = fd;
  pollset[1].events = POLLIN;


  alarm(20); // 10 masodperc múlva SIGALRM jelzés

  printf("MY PID: %d\n", getpid());

  if (poll(pollset, 2, -1) > 0) {
      if (pollset[0].revents & POLLIN) {
          len = read(pollset[0].fd, buf, sizeof(buf));
          if (len > 0) write(STDOUT_FILENO, buf, len);
      }

      if (pollset[1].revents & POLLIN) {
          if (read(fd, &info, sizeof(struct signalfd_siginfo)) > 0) {
              printf("GETTING SIGNAL FROM PROCESS %d\n", info.ssi_pid);
          }
      }
  }
  else {
      perror("poll");
  }

  printf("Megerkezett vagy megnyomtak.\n");

  close(fd);

  return(alarm(0)); // Kikapcsoljuk az idozitot
}
