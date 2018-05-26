#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<semaphore.h>
int ring[32];
sem_t semBlank;
sem_t semData;
void *runp(void*arg)
{	
	int i=0;
	while(1){
		sem_wait(&semBlank);
		ring[i]=rand()%1234+1;
		int data=ring[i];
		i++;
		i%=32;
		printf("product done,data is:%d\n",data);
		sem_post(&semData);
		sleep(1);
		
	}
}

void *runc(void*arg)
{
	int data=0;
	int i=0;
	while(1){
		sem_wait(&semData);
		data=ring[i];
		i++;
		i%=32;
		printf("consumer done,data is:%d\n",data);
		//sleep(1);
		sem_post(&semBlank);
	//	sleep(1);
	}
}
int main()
{
	sem_init(&semBlank,0,32);
	sem_init(&semData,0,0);
	srand((unsigned long)time(NULL));
	pthread_t t1,t2;
	pthread_create(&t1,NULL,runc,NULL);
	pthread_create(&t2,NULL,runp,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	sem_destroy(&semBlank);
	sem_destroy(&semData);
}

