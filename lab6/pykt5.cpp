#include<stdio.h>
#include <errno.h>
#include <time.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void sigusr_handler(int sig) {
    
         switch (sig) {

                 case 10: // SIGUSR1
                           fprintf(stderr, "Received SIGUSR1 from parent\n"); 
                           break;
              
                case 12: // SIGUSR2
                         fprintf(stderr, "Received SIGUSR2 from child\n"); 
                         break;
        }
         }


          int main() {

          struct timespec time1, time2, time3, time4; 
          struct sigaction sa;

          time1.tv_sec = 2;
          time1.tv_nsec = 1000000;
          time3.tv_sec = 2;
          time3.tv_sec = 1000000;

          sigemptyset(&sa.sa_mask);
          sa.sa_flags = 0;
              sa.sa_handler = sigusr_handler;
              sigaction(SIGUSR1, &sa, NULL);
              sigaction(SIGUSR2, &sa, NULL);
              
              pid_t pid;
              if(pid = fork()==0) {
                   pid = getppid();
                   while(true) {
                             nanosleep(&time1, &time1);
                                    if (errno == EINTR) nanosleep(&time1, &time1); 
                                    kill(pid, 10);
                                    fprintf(stderr, "Sent SIGUSR1 to child\n");
      
                       }

		} else {

                      while(true) {

                                   nanosleep(&time3, &time3);

                                  if (errno == EINTR) nanosleep(&time3, &time3); 
                                  kill(pid, 12);
                                  fprintf(stderr, "Sent SIGUSR2 to parent\n");
                    }
           }
}
