/* The program  cmdpipe.cpp */
/* Using the popen and pclose I/O commands */
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
//#include<sys/types.h>
#include<limits.h>
main(int argc, char *argv[])
{
FILE	*fin, *fout, *fout1;
char	buffer[PIPE_BUF];
int	n, i;
    if(argc<3){
	fprintf(stderr, "Usage %s cmd1 cmd2\n", argv[0]);
	exit(1);
	}
	for (i = 1; i + 1 < argc; i++) {
	if ((fin  = popen(argv[1], "r")) == NULL) {fprintf(stderr, "error"), exit(1);}
	if ((fout = popen(argv[2], "w")) == NULL) {fprintf(stderr, "error"), exit(1);}
	if ((n = read(fileno(fin), buffer, PIPE_BUF)) == -1) {fprintf(stderr, "error: can't read"), exit(1);}
	if (write(fileno(fout), buffer, n) == -1) {fprintf(stderr, "error"), exit(1);}
	if (pclose(fin) == -1){fprintf(stderr, "error"), exit(1);}
	if (pclose(fout) == -1) {fprintf(stderr, "error"), exit(1);}
	}
exit(0);
}
