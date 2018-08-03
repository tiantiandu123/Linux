#include"comm.h"
int commSemset(int nsems,int flags)
{
	key_t key=ftok(PATHNAME,PROJ_ID);
	if(key<0){
		perror("ftok");
		return -1;
	}
	int semid=semget(key,nsems,flags);
	if(semid<0){
		perror("semget");
		return -1;
	}
	return semid;
}
int createSemset(int nsems)
{
	return commSemset(nsems,IPC_CREAT|IPC_EXCL|0666);
}
int getSemset(int nsems)
{
	return commSemset(nsems,IPC_CREAT);
}
int initSemset(int semid,int semnum,int initval)
{
	union semun un;
	un.val=initval;
	int ret=semctl(semid,semnum,SETVAL,un);
	if(ret<0){
		perror("semctl");
		return -1;
	}
	return 0;//sucess
}
int commPV(int semid,int who,int op)
{
	struct sembuf buf;
	buf.sem_num=who;
	buf.sem_flg=0;
	buf.sem_op=op;
	if(semop(semid,&buf,1)<0){
		perror("semop");
		return -1;
	}
	return 0;
}
int P(int semid,int who)
{
	return commPV(semid,who,-1);
}
int V(int semid,int who)
{
	return commPV(semid,who,1);
}
int destroySemset(int semid,int semnum)
{
	int ret=semctl(semid,semnum,IPC_RMID);
	if(ret<0){
		perror("semctl");
		return -1;
	}
}





