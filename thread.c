#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_function();
char message[] = "Hello World";
int run_now = 1; //1 when the main function is executing and 2 when the new thread is executing

int main()
{
	int res;
	pthread_t a_thread,b_thread;
	void *thread_result;

	res = pthread_create(&a_thread,NULL,thread_function,NULL);
	if(res!=0)
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	int print_count1=0;
	while(print_count1++ < 20)
	{
		if(run_now == 1)
		{
			printf("1");
			run_now = 2;
		}
		else
		{
			sleep(1);
		}
		
	}
	printf("Waiting for thread to finish...\n");
	res = pthread_join(a_thread,&thread_result);
	if(res!=0)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void *thread_function()
{	
	int print_count2 = 0;
	while(print_count2++ < 20)
	{
		if(run_now == 2)
		{
			printf("2");
			run_now = 1;
		}
		else
		{
			sleep(1);
		}
	}
	printf("thread_function is running.");
}
