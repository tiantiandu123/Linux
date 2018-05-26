#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include<semaphore.h>
#define PRODUCER_NUM 5 //生产者数目  
#define CONSUMER_NUM 5 //消费者数目 
int ring[11];
sem_t semBlank;
sem_t semData;
int i;
int j;
pthread_mutex_t mutex;


void *runp(void*arg)
{
	while(1){
		sem_wait(&semBlank);
		pthread_mutex_lock(&mutex);
		ring[i]=rand()%1234+1;
		int data=ring[i];
		i++;
		i%=11;
		printf("%d product done,data is:%d\n",(int)arg,data);
		pthread_mutex_unlock(&mutex);
		sem_post(&semData);
		sleep(1);	
	}
}

void *runc(void*arg)
{
	while(1){
		sem_wait(&semData);
		  pthread_mutex_lock(&mutex);
		int data=ring[j];
		j++;
		j%=11;
		printf("%d consumer done,data is:%d\n",(int)arg,data);
		  pthread_mutex_unlock(&mutex);
		sem_post(&semBlank);
	}
}
int main()
{
	pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
		//pthread_mutex_init(&mutex, NULL);  
	pthread_t producer_id[PRODUCER_NUM];  
	pthread_t consumer_id[CONSUMER_NUM];
	sem_init(&semBlank,0,11);
	sem_init(&semData,0,0);
	srand((unsigned long)time(NULL));
	int i=0;
	for(;i<PRODUCER_NUM;i++){
		int ret=pthread_create(&producer_id[i],NULL,runp,(void*)i);
		 if (ret != 0){  
		 	 printf("producer_id error"); 					    		exit(0);
			 }
		int ret1=pthread_create(&consumer_id[i],NULL,runc,(void*)i);
		 if (ret1!= 0){  
		 	 printf("consumer_id error"); 					    		exit(0);
			 }
		}
		int j=0;
		 for(;j<PRODUCER_NUM;j++){  
	 	pthread_join(producer_id[j],NULL);  
		pthread_join(consumer_id[j],NULL);  
		}
	sem_destroy(&semBlank);
	sem_destroy(&semData);
	return 0;
} 
