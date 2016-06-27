#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

int main(int argc, char* argv[])
{
  int i;
  
  if(daemon(0, 0) < 0)
  {
    perror("daemon");
    return EXIT_FAILURE;
  }

  openlog("hello", LOG_PID, LOG_DAEMON);
  for(i = 0; i < 10; i++)
  {
    syslog(LOG_INFO, "Hello daemon: %d\n", i);
    sleep(1);
  }
  closelog();
  
  return EXIT_SUCCESS;
}
