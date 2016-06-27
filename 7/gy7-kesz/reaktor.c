#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int value = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cvar = PTHREAD_COND_INITIALIZER;

void* alarm_thr(void* data)
{
  int new_value;
  int old_value = 0;
  while(1)
  {
    pthread_mutex_lock(&mutex);
    while(value == old_value) pthread_cond_wait(&cvar, &mutex);
    new_value = value;
    pthread_mutex_unlock(&mutex);
    
    if((new_value >= 90) && (old_value < 90))
    {
      printf("Bumm, the end!\n");
    }
    else if((new_value >= 60) && (old_value < 60))
    {
      printf("Meleg a helyzet!\n");
    }
    else if((new_value >= 30) && (old_value < 30))
    {
      printf("Érdemes lenne odafigyelni!\n");
    }
    old_value = new_value;
  }
  return NULL;
}

void* measure_thr(void* data)
{
  int i;
  for(i = 0; i <= 100; i += 10)
  {
    pthread_mutex_lock(&mutex);
    value = i;
	pthread_cond_broadcast(&cvar);    
    pthread_mutex_unlock(&mutex);

    sleep(1);

  }
  return NULL;
}

int main()
{
  pthread_t th_m;
  pthread_t th_a;
  
  printf("Program indul...\n");
  if(pthread_create(&th_a, NULL, alarm_thr, NULL))
  {
    fprintf(stderr, "pthread_create (alarm)");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&th_m, NULL, measure_thr, NULL))
  {
    fprintf(stderr, "pthread_create (measure)");
    exit(EXIT_FAILURE);
  }
  pthread_join(th_m, NULL);
  printf("Program vége.\n");
  exit(EXIT_SUCCESS);
}
