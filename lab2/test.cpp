

/*
 *   Displaying process group ID information
 */
#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
main(){
printf("hi%d\n",getpid());
int  pid = fork();
if((int) pid > 0) 

{
	fork();
	printf("hello %d\n", getpid());
}else {
	fork();
}
printf("bye%d\n", getpid());
}

