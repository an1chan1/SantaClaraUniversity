//Akshay Nichani
//4/19/24
//Lab3 - Step 5
//This program implements a form of product-consumer message communication using a shared memory segment.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <error.h>

#define KEY 123

//main
int main(){
	//variables
	int id;
	char *str;
	char *v;
	
	//Create shared key
	key_t key = KEY;	
	if(fork()==0){
		//parent process creates id of shared memory
		if((id=shmget(key, sizeof(str), IPC_CREAT|0666)) < 0){
			perror("shared memory not created");
			exit(1);
		}
		//accesses the shared memory segment
		v = (char *) shmat(id,0,0);
		//gets user input and writes to segment
		fgets(v, 60, stdin);
		sleep(1);
		printf("\n");
		exit(0);
	}
	else{
		sleep(5);
		//child gets teh id of teh segment
		if((id=shmget(key,sizeof(str),0)) < 0){
			perror("shared memory not accessed");
			exit(1);
		}
		//attaches to shared memory
		str = (char *) shmat(id,0,0);
		if(str <= (char *) (0)){
			perror("shared memory not attached");
			exit(1);
		}

		printf("Text read from shared memory:  ");
		//prints the string to stdout using puts()
		
		puts(str);
		printf("\n");
		exit(0);
	}
	//detach shared memory
	if(shmdt(str)==-1){
		perror("shmdt");
		exit(1);
	}
	//remove the segemnt
	if (shmctl(id, IPC_RMID, NULL) == -1) {
        	perror("shmctl");
        	exit(1);
    	}
	//free(str);
	return 0;
}

