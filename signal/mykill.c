#include<stdio.h>
#include<signal.h>
#include<sys/types.h>

int main(int argc,char*argv[])
{
	int count=0;
	alarm(1);
	while(1){
//	printf("hello %d\n",count++);
//    if(count>=1000){
//    	//raise(2);
//    	abort();
//		}
//	}
		count++;
		printf("count=%d\n",count);
	}
//	if(argc!=3){
//	printf("Usage:%s signo pid\n",argv[0]);
//	return 1;
//	}
//	int signo=atoi(argv[1]);
//	int pid=atoi(argv[2]);
//
//	kill(pid,signo);
//	return 0;
}
	
