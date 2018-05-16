#include"common.h"
int main()
{
	int shmid=getshm(1024);
	char*ptr=(char*)shmat(shmid,NULL,0);
	int offset=0;
	//while(1){
	//	printf("server# %s\n",ptr);}
	while(1){
		printf("server# %s\n",ptr);
		int count=0;
		char*cur=ptr;
		for(;count<10;++count){
			*cur++='A'+offset;
			sleep(1);
		}
		*cur='\0';
		++offset;
		offset%=26;
	}
	sleep(1);
	shmdt(ptr);
	return 0;
}
