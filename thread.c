#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_function(void *arg);
void *thread_function2(void *arg);
char message[] = "Hello World";

int main()
{
	int res;
	pthread_t a_thread,b_thread;
	void *thread_result;

	res = pthread_create(&a_thread,NULL,thread_function,(void *)message);
	if(res!=0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	res = pthread_create(&b_thread,NULL,thread_function2,(void *)message);
	if(res!=0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for 1st thread to finish...\n");
	res = pthread_join(a_thread,&thread_result);
	if(res!=0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined, it returned %s\n",(char *)thread_result);
	printf("Message is now %s\n",message);
	printf("Waiting for 2nd thread to finish...\n");
	res = pthread_join(b_thread,&thread_result);
	printf("Thread joined, it returned %s\n",(char *)thread_result);
	printf("Message is now %s\n",message);
	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
	printf("thread_function is running.Argument was %s\n",(char *) arg);
	sleep(3);
	strcpy(message,"Bye!");
	pthread_exit("Thank you for the CPU time");
}

void *thread_function2(void *arg)
{
	printf("thread_function2 is running.\n");
	sleep(10);
	strcpy(message,"Bye from 2nd thread\n");
	pthread_exit("Thank you for the CPU time also\n");
}

