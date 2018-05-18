#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *thread_run(void *arg)
{
	printf("thread is running,pid:%d,thread:%d\n",getpid(),pthread_self());
	sleep(3);
}
int main()
{
	pthread_t t;
	pthread_create(&t,NULL,thread_run,NULL);
	printf("main thread is running!pid:%d,thread:%d\n",getpid(),pthread_self());
	pthread_cancel(t);
	void *code;
	int ret=pthread_join(t,&code);
	if(ret==0){
	printf("wait new thread sucess,%d\n",(int)code);
	}
}
