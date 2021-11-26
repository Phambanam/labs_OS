#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
extern int etext, edata, end;
 
main(void) {
key_t key=15;
char *shm_1, *shm_2, *shm_3;
int shmid_1,shmid_2,shmid_3;
 
if ((shmid_1=shmget(key, 1023, 0644|IPC_CREAT)) == -1) {
perror("shmget shmid_1");
exit(1);
}
if ((shmid_2=shmget(key + 1, 1023, 0644|IPC_CREAT)) == -1) {
perror("shmget shmid_2");
exit(1);
}
if ((shmid_3=shmget(key + 2, 1023, 0644|IPC_CREAT)) == -1) {
perror("shmget shmid_3");
exit(1);
}
printf("Addresses in parent\n\n");
shm_1 = (char *) shmat(shmid_1, 0, 0);
printf("shared mem: %10p\n program text (etext): %10p\n initialized data (edata): %10p\n uninitialized data (end): %10p\n\n", shm_1, &etext, &edata, &end);
shm_2 = (char *) shmat(shmid_2, 0, 0);
printf("shared mem: %10p\n program text (etext): %10p\n initialized data (edata): %10p\n uninitialized data (end): %10p\n\n", shm_2, &etext, &edata, &end);
shm_3 = (char *) shmat(shmid_3, 0, 0);
printf("shared mem: %10p\n program text (etext): %10p\n initialized data (edata): %10p\n uninitialized data (end): %10p\n\n", shm_3, &etext, &edata, &end);
}
