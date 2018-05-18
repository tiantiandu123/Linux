#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int ticket=100;

void*thread_run(void*arg)
{
	int a=(int)arg;
	while(1){
		if(ticket>0){
			usleep(10000);
			printf("%d sells ticket:%d\n",a ,ticket);
			ticket--;
		}else{
			break;
		}
	}
}
int main()
{
	pthread_t t1,t2,t3,t4;
	void*ret1;
	void*ret2;
	void*ret3;
	void*ret4;
	pthread_create(&t1,NULL,thread_run,(void*)1);
	pthread_create(&t2,NULL,thread_run,(void*)2);
	pthread_create(&t3,NULL,thread_run,(void*)3);
	pthread_create(&t4,NULL,thread_run,(void*)4);

	pthread_join(t1,&ret1);
	pthread_join(t2,&ret2);
	pthread_join(t3,&ret3);
	pthread_join(t4,&ret4);
}
