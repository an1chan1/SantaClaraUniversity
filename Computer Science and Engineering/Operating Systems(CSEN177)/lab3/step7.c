//Akshay Nichani
//4/19/24
//Lab3 - Step 7
//This program implements a way to pass multiple threads at the same time

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main(){
	int i;
	//create 10 threads and call the function go() for each
	for(i = 0; i < NTHREADS; i++)
		pthread_create(&threads[i], NULL, go, &i);
	//join each thread and confirm the joining
	for(i = 0; i < NTHREADS; i++){
		printf("Thread %d returned\n", i);
		pthread_join(threads[i], NULL);
	}
	//confirmation at the end
	printf("Main thread done.\n");
	return 0;
}
void *go (void *arg){
	//for each thread print its id and the iteration number
	printf("Hello from thread %d with iteration %d\n", (int)(unsigned long)pthread_self(), *(int*)arg);
	return 0;
}
