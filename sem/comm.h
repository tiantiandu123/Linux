#pragma once
#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PATHNAME "."
#define PROJ_ID 0x6666

union semun {
         int              val; 
	  struct semid_ds *buf;  
	   unsigned short  *array;
	      struct seminfo  *__buf;  
	};

int commSemset(int nsems,int flags);
int createSemset(int nsems);
int getSemset(int nsems);
int commPV(int semid,int who,int op);
int initSemset(int semid,int semnum,int initval);
int P(int semid,int who);
int V(int semid,int who);
int destroySemset(int semid,int semum);
