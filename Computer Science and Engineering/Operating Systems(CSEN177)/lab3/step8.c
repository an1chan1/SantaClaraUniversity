//Akshay Nichani
//4/19/24
//Lab3 - Step 8
//After fixing the bug in step 7, this program successfully implements a way to pass multiple threads at the same time

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main(){
	int i;
	//create 10 threads but and a sleep() after each creation to avoid duplicate iteration numbers
	for(i = 0; i < NTHREADS; i++){
		pthread_create(&threads[i], NULL, go, &i);
		sleep(2);
	}
	//join the 10 threads
	for(i = 0; i < NTHREADS; i++){
		printf("Thread %d returned\n", i);
		pthread_join(threads[i], NULL);
	}
	//confirmation message of main thread done
	printf("Main thread done.\n");
	return 0;
}
void *go (void *arg){
	//print each thread and its iteration number and id
	printf("Hello from thread %d with iteration %d\n", (int)(unsigned long)pthread_self(), *(int*)arg);
	return 0;
}
