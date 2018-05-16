#include"common.h"
int commonshm(int size,int flags)
{
	key_t key=ftok(PATHNAME,PROJ_ID);
	if(key<0){
		perror("ftok()");
		return -1;
	}
	int shmid=shmget(key,size,flags);
	if(shmid<0){
		perror("shmget()");
	}
	return shmid;
}
int createshm(int size)
{
	return commonshm(size,IPC_CREAT|IPC_EXCL|0666);
}
int getshm(int size)
{
	return commonshm(size,IPC_CREAT);
}
int destoryshm(int shmid)
{	
	if(shmctl(shmid,IPC_RMID,NULL)<0){
		perror("shmctl");
		return -1;
	}
	return 0;
}
