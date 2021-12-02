#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
main(){
if(fork()){
	sleep(10);
	printf("i am parent\n");
	printf("\n%s\n",get_current_dir_name());
}else{
	printf("i am child\n");
	chdir("/home/phamnam99");
	printf("\n%s\n",get_current_dir_name());
}


}
