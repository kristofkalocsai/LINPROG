#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>

sem_t szemafor;

void* utas_szal(void*arg)
{
	int sorszam=*(int*)arg;
	free(arg);

	printf("A %d. utas sorban all...\n",sorszam);

	sem_wait(&szemafor);
	printf("A %d. utas sorra kerult...\n",sorszam);
	sleep(3);
	printf("A %d. utas tavozott...\n",sorszam);

	sem_post(&szemafor);
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t th[10];
	int i;

	sem_init(&szemafor,0 , 4);
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for (i=0; i < 10; ++i) {
		int* param;
		param=(int*)malloc(sizeof(int));
		(*param) = i;		
		if(pthread_create(&th[i], &attr, utas_szal, param)) {  
			fprintf(stderr, "pthread_create (alarm)");
			exit(EXIT_FAILURE);
		}
		
	}

	pthread_attr_destroy(&attr);

	for (i=0; i < 10; ++i) {
		printf("\t join %d\n", i);
		pthread_join(th[i], NULL);
	}

	exit(EXIT_SUCCESS);
}
