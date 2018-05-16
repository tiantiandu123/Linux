#pragma once
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

#define PATHNAME "."
#define PROJ_ID 0x6666

int commonshm(int size,int flags);
int createshm(int size);
int getshm(int size);
int destoryshm(int shmid);
