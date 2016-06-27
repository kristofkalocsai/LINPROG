/* chatszerver.c
 *
 * Egyszálú, poll alapú TCP szerver példa.
 * A példaprogram egy csevegő szervert valósít meg, amely fogadja a
 * kliensek kapcsolódásait, majd az egyik kapcsolaton érkező szöveget
 * szétküldi a többi kapcsolatra.
 * Tesztelés: telnet <hoszt> 3344
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

#define PORT 3344
#define MAXCONNS 5
#define FULLMSG "Megtelt!"

int ssock;
struct pollfd poll_list[MAXCONNS + 1];

void handle_new_connection()
{
  // TODO: bejövő kapcsolat kezelése
  // Ha van üres hely a tömbben, akkor oda tesszük egyébként visszautasítjuk.
  int csock, i;

  // csock = accept(ssock, NULL, NULL);
  if ((csock = accept(ssock, NULL, NULL)) < 0) {
      return;
  }
  printf("INCOMING CONNECTION\n");
  for (i = 0; i < MAXCONNS; i++) {
      if (poll_list[i].fd < 0) {
          // van ures hely
          printf("ASSIGNING %d. PLACE TO CLIENT %d\n", i, csock);
          poll_list[i].fd = csock;
          return;
      }
  }

  // nincs ures hely
  printf("SRVR FULL\n");
  send(csock, FULLMSG, strlen(FULLMSG), 0);
  close(csock);

}

void process_read(int csock)
{
  // TODO: beolvassuk a szöveget és szétküldjük a többieknek
  char buf[256];
  int len;
  int i;

  len = recv(csock, buf, sizeof(buf), 0);
  // printf("RECEIVED %d CHAR\n", len);
  if (len > 0) {
      for (i = 1; i <= MAXCONNS ; i++) {
          // send only for connected clients, do not send message back to sender
          if ((poll_list[i].fd != -1) && (poll_list[i].fd != csock)) {
              if(send(poll_list[i].fd, buf, len , 0) < 0){
                  perror("send");
              }

          }
      }
  }
}

int main()
{
  struct sockaddr_in6 addr;
  int reuse;
  int i;
  int ii;

  if((ssock = socket(PF_INET6, SOCK_STREAM, 0)) < 0)
  {
   perror("socket");
   return 1;
  }

  reuse = 1;
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

  poll_list[0].fd = ssock;
  poll_list[0].events = POLLIN;

  for(i = 1; i <= MAXCONNS; i++)
  {
    poll_list[i].fd = -1;
    poll_list[i].events = POLLIN;
  }

  while(1)
  {
    // TODO: poll
    if (poll(poll_list, MAXCONNS+1, -1) > 0) {
        // TODO: az események feldolgozása és a lekezelő függvények meghívása
        // jott esemeny
        if (poll_list[0].revents & POLLIN) {
            handle_new_connection();
        }
        for (ii = 0; ii < MAXCONNS; ii++) {
            if (poll_list[ii].revents & (POLLERR | POLLHUP)) {
                close(poll_list[ii].fd);
                poll_list[ii].fd = -1;
            }
            else if(poll_list[ii].revents & POLLIN) {
                process_read(poll_list[ii].fd);
            }
        }

    }



  }

  return 0;
}
