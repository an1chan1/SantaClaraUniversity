//Akshay Nichani
//4/19/24
//Lab3 - Step 5
//This program implements a form of product-consumer message communication using pipes.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//main
int main(int argc, char *argv[]){
	int fds[2];
	char buff[60];
	int count;
	int i;
	pipe(fds);
	if(fork()==0){
		printf("\nWriter on the upstream end of the pipe -> %d arguments \n", argc);
		dup2(fds[1],1);
		close(fds[0]);
		//writer sends this message through the pipe using write()
		write(fds[1], "Message from producer: Our product is now available", sizeof(buff));
		exit(0);
	}
	else if(fork()==0){
		printf("\n***Reader on the downstream end of the pipe*** \n");
		close(fds[1]);
		//consumer says they acknoledge the message by printing it out from the pipe	
		printf("\nConsumer acknowledge receipt of message:\n\n");
		while((count=read(fds[0],buff,60))>0){
			for(i=0;i<count;i++){
				write(1,buff+i,1);
				write(1,"",1);
			}
			printf("\n");
		}
		exit(0);
	}
	else{//parent closes the pipe
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}

