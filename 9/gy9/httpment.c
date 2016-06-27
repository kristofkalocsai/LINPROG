/* httpment.c
 * 
 * TCP kliens, amely a magas szintű állománykezelő függvények használatát
 * mutatja be.
 * A program kapcsolódik a paraméterként megadott webszerverhez és lekéri
 * a megadott oldalt HTTP/0.9 protokollon keresztül. A megkapott oldalt
 * lementi egy állományba.
 * Megj.: Bár a HTTP/0.9 protokoll nagyon régi, a szerverek többsége támogatja.
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
  struct addrinfo hints;
  struct addrinfo* res;
  struct addrinfo* p;
  int err;
  char ips[INET6_ADDRSTRLEN];
  int csock;
  char buf[1024];
  FILE* fpsock;
  FILE* fpfile;
  int len;
  
  if(argc != 4)
  {
    printf("Használat: %s <szerver> <oldal> <fájl>\n", argv[0]);
    return 1;
  }

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  err = getaddrinfo(argv[1], "http", &hints, &res);
  if(err != 0)
  {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
    return -1;
  }

  fpfile = fopen(argv[3], "w");
  if(fpfile == NULL)
  {
    perror("fopen");
    return -1;
  }
  
  for(p = res; p != NULL; p = p->ai_next)
  {
    if(getnameinfo(p->ai_addr, p->ai_addrlen,
      ips, sizeof(ips), NULL, 0, NI_NUMERICHOST) == 0)
    {
      printf("Kapcsolódás: %s\n", ips);
    }
    
    csock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if(csock < 0) continue;
    
    if(connect(csock, p->ai_addr, p->ai_addrlen) == 0)
    {
      printf("Sikeres kapcsolódás.\n");
      fpsock = fdopen(csock, "r+");
      // HTTP 0.9 oldal lekérés
      fprintf(fpsock, "GET %s\r\n", argv[2]);
      fflush(fpsock);
      printf("Adatok mentése.\n");
      
      while((len = fread(buf, 1, sizeof(buf), fpsock)) > 0)
      {
	fwrite(buf, 1, len, fpfile);
      }
      printf("Kapcsolat bontása.\n");
      fclose(fpsock);
      break;
    }
    else
    {
      perror("connect");
    }
    
    close(csock);
  }

  fclose(fpfile);
  freeaddrinfo(res);

  return 0;
}
