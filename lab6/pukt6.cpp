#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
void signal1(int sig_num){
	signal(sig_num,signal1);
        printf("signal %d from parant received \n", sig_num);
       	if(sig_num==SIGQUIT){
      exit(1);
      }
}
void signal2(int sig_num){
	signal(sig_num,signal2);
        printf("signal %d from child received \n", sig_num);
       	if(sig_num==SIGQUIT){
      exit(1);
      }
}
int main(){
void signal1(int);
void signal2(int);
struct sigaction sa;
sa.sa_flags = 0;
sigemptyset(&sa.sa_mask);

int childPid = fork();
int parentPid;

if (fork()==0){
	sa.sa_handler = signal1;
	parentPid = getppid();
	if(sigaction(SIGUSR1, &sa, NULL) == -1){
		printf("signal Parent not recieved\n");
		perror("sigQuit");
		exit(1);
	}
	while(true){
	sleep(2);
	kill(parentPid, SIGUSR1);
	}
}else {
	sa.sa_handler = signal2;
	if(sigaction(SIGUSR1, &sa, NULL) == -1){
		printf("signal Child  not recieved\n");
		perror("sigQuit");
		exit(1);
	}
	while(true){
	sleep(1);
	kill(childPid, SIGUSR1);
	}
}
return 0;

}
