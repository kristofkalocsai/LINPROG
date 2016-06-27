#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* „A C programnyelv nem olyan bonyolult. Például a void (*(*f[])())() 
 * definiálja f-et, mint ismeretlen méretű tömböt, amely függvényekre mutató 
 * pointereket tartalmaz, amelyek visszatérési értéke void visszatérési értékű 
 * függvényekre mutató pointer.”
 * (a szerző ismeretlen)
 */

void* thread_function(void* arg)
{
	int i;
	printf("A szal indul... \n");
	for(i = 1; i <= 20; i++)
	{
		printf("%d. Hello szal vilag!\n",i);
		sleep(1);
	}
	printf("A szal kilep... \n");
	return NULL;
}

int main(void)
{
	pthread_t mythread;
	if(pthread_create(&mythread, NULL, thread_function, NULL))
	{
		fprintf(stderr,"Hiba a szal letrehozasaban.\n");
		exit(EXIT_FAILURE);
	}
	
	sleep(5);
	
	printf("Letelt az ot masodperc, varjuk meg a hatterszalat\n");
	pthread_join(mythread, NULL);
	
	printf("A foszal kilep... \n");
	exit(EXIT_SUCCESS);
}
