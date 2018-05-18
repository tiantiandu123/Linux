#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *thread_run(void*arg)
{
	char*a=(char*)arg;
	pthread_detach(pthread_self());
	printf("%s\n",a);
	return NULL;
}
int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,thread_run,"thread run");
	int code=0;
	sleep(1);
	int ret=pthread_join(tid,NULL);
	if(ret==0){
		printf("thread wait success\n");
		code=0;
	}else{
		printf("thread wait error\n");
		code=1;
	}
	return code;
}

