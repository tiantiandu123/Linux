#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
typedef struct Node{
	struct Node*next;
	int data;
}node_t,*pNode,**ppNode;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;	
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pNode allocNode(int x)
{
	pNode n=(pNode)malloc(sizeof(node_t));
	if(n==NULL){
		perror("malloc");
		return NULL;
	}
	n->data=x;
	n->next=NULL;
	return n;
}
int isEmpty(pNode head)
{
	return head->next==NULL?1:0;
}
void initList(ppNode head)
{
	*head=allocNode(0);
}
void listpush(pNode head,int x)//head push
{
	pNode n=allocNode(x);
	n->next=head->next;
	head->next=n;
}
void listpop(pNode head,int*x)
{	
	if(!isEmpty(head)){
		pNode n=head->next;
		head->next=n->next;
		if(x!=NULL){
		*x=n->data;
		}
		free(n);
	}
}
void showList(pNode head)
{
	if(!isEmpty(head)){
		head=head->next;
		while(head){
			printf("%d ",head->data);
			head=head->next;
		}
		printf("\n");
	}
}
void destroyList(pNode head)
{
	while(head){
		listpop(head,NULL);
	}
	free(head);
}
void *runp(void*arg)
{
	pNode hp=*((ppNode)arg);
	int data=0;
	while(1){
		data=rand()%100+1;
		pthread_mutex_lock(&lock);
	 	listpush(hp,data);//head push
		printf("producter data is :%d\n",data);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);
		sleep(5);
	}
}
void *runc(void*arg)
{	
	pNode hp=*((ppNode)arg);
	int data=0;
	while(1){
	pthread_mutex_lock(&lock);
		while(isEmpty(hp)){
			printf("list is empty,no data to read!\n");
			pthread_cond_wait(&cond,&lock);
		}
			listpop(hp,&data);
			printf("consumer data is :%d\n",data);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
}
int main()
{
    	
	pNode head=NULL;
	initList(&head);
	srand((unsigned long)time(NULL));
	pthread_t c,p;
	pthread_create(&p,NULL,runp,(void*)&head);
	pthread_create(&c,NULL,runc,(void*)&head);
	pthread_join(p,NULL);
	pthread_join(c,NULL);
//	int i=0;
//	int x=0;
//	for(;i<10;i++){
//		listpush(head,i);
//		showList(head);
//	}
//	for(;i>5;i--){
//		listpop(head,&x);
//		showList(head);
//	}
	destroyList(head);
	return 0;
}

                                
