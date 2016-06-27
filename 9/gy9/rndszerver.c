/* rndszerver.c
 *
 * Többszálú TCP szerver példa.
 * Az alkalmazás megadott számú szálat indít, amelyek között szétosztja
 * a bejövő kapcsolatokat. A szálak generálnak egy véletlen számot és
 * kis várakozás után elküldik a kliensnek.
 * Tesztelés: nc <hoszt> 2233
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 2233
#define THREAD_NUM 3

int ssock;
pthread_mutex_t smutex = PTHREAD_MUTEX_INITIALIZER;

void* comth(void* arg)
{
  int ix;
  int csock;
  char buf[64];
  int len;

  ix = *((int*)arg);
  free(arg);

  while(1)
  {
    // TODO: feladatok szétosztása, kapcsolat fogadása, véletlen szám visszaküldése
    pthread_mutex_lock(&smutex);
    csock = accept(ssock, NULL, NULL);
    pthread_mutex_unlock(&smutex);

    sleep(3);

    len = sprintf(buf, "%d. szal: %d\n", ix, rand()%10 );
    send(csock, buf, len, 0);

    close(csock);

  }
  return NULL;
}

int main()
{
  struct sockaddr_in6 addr;
  pthread_t th[THREAD_NUM];
  int i;

  int reuse;
  int* pix;

  // ipv6 os socket
  if((ssock = socket(PF_INET6, SOCK_STREAM, 0)) < 0)
  {
    perror("socket");
    return 1;
  }

  reuse = 1;
  // reuse parameter
  setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

  memset(&addr, 0, sizeof(addr));
  addr.sin6_family = AF_INET6;
  addr.sin6_addr = in6addr_any;
  addr.sin6_port = htons(PORT);

  if(bind(ssock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
  {
    perror("bind");
    return 1;
  }

  if(listen(ssock, 5) < 0)
  {
    perror("listen");
    return 1;
  }

  srand(time(NULL));

  for(i = 0; i < THREAD_NUM; i++)
  {
    pix = malloc(sizeof(int));
    *pix = i;
    pthread_create(&th[i], NULL, comth, pix);
  }

  while(1) sleep(1);

  return 0;
}
