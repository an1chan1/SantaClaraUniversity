//Akshay Nichani
//4/19/24
//Lab3 - Step 2
//This program implements a writer that writes into a pipe, and the reader reads from the pipe and outputs it.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
//main
int main(int argc, char *argv[]){
	int fds[2];
	char buff[60];
	int count;
	int i;
	pipe(fds);
	if(fork()==0){
		printf("\nWriter on the upstream end of the pipe -> %d arguments \n", argc);
		close(fds[0]);
		//writes into pipe using fds[1], sends arguments included during execution of this file
		for(i = 0; i < argc; i++){
			write(fds[1], argv[i], strlen(argv[i]));
		}
		exit(0);
	}
	else if(fork()==0){
		printf("\nReader on the downstream end of the pipe \n");
		close(fds[1]);
		//reads using fds[0] and stores in a buffer. Then reads the buffer and includes space between each character
		while((count=read(fds[0],buff,60))>0){
			for(i=0;i<count;i++){
				write(1,buff+i,1);
				write(1," ",1);
			}
			printf("\n");
		}
		exit(0);
	}
	//finally, closes the pipe
	else{
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}

