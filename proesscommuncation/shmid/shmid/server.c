#include"common.h"
int main()
{
	int shmid=createshm(1024);
	char*ptr=(char*)shmat(shmid,NULL,0);
	int i=0;
	while(1){
		printf("client# %s\n",ptr);
		ptr[i]='A';
		ptr[++i]='\0';
		sleep(1);
	sleep(1);
	}
	shmdt(ptr);
	sleep(1);
	destroyshm(shmid);
	return 0;
}
