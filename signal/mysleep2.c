#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handler()
{}
int mysleep(int timeout)
{
	struct sigaction act,oact;
	sigset_t newmask,oldmask,suspmask;
	act.sa_handler=handler;
	act.sa_flags=0;
	sigemptyset(&act.sa_mask);//init;
	sigaction(14,&act,&oact);//handler 14 signal
	//block SIGALRM
	sigemptyset(&newmask);
	sigaddset(&newmask,14);
	//set sig_set
	sigprocmask(SIG_BLOCK,&newmask,&oldmask);
	alarm(timeout);

	suspmask=oldmask;
	sigdelset(&suspmask,14);
	sigsuspend(&suspmask);
	int unsleep=alarm(0);//empty
	sigaction(14,&oact,NULL);
	sigprocmask(SIG_SETMASK,&oldmask,NULL);
	return unsleep;
}
int main()
{
	while(1){
		mysleep(2);
		printf("two seconds passed\n");
	}
	return 0;
}
