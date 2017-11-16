#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
void calculadora(pid_t pid,int status,int childpid);
void ficheros(pid_t pid,int status,int childpid,char **argv);
int main(int argc, char *argv[]){
  if(argc<2){
   printf("error, introduce los gedit\n");
   exit(-1);
   }
  else{
  pid_t pid;
  int status,childpid,i,j;
  pid=fork();
  calculadora(pid,status,childpid);
  pid=fork();
  ficheros(pid,status,childpid,argv);
  }
}
 
void calculadora(pid_t pid,int status,int childpid){
 switch(pid)
	{
		case -1: /* error del fork() */
			perror("fork error");
			printf("errno value= %d\n", errno);
			exit(-1); //exit(EXIT_FAILURE);
		case 0: /* proceso hijo */
			printf("Proceso hijo %d; padre = %d \n", getpid(), getppid());
			if(execlp("gnome-calculator","",NULL)==-1)
			{
				perror("Falla en la ejecucion exec de la calculadora");
				printf("errno value= %d\n", errno);
				exit(EXIT_FAILURE);
			}
		default: /* padre */
			printf("padre con pid: %ld\n", (long)getpid());
			childpid=wait(&status);	
			if(childpid>0)
			{
				if (WIFEXITED(status)) {
					printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
				} else if (WIFSIGNALED(status)) {
					printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
				} else if (WIFSTOPPED(status)) {
					printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
				}
			}
   }
}

void ficheros(pid_t pid,int status,int childpid,char **argv){
   switch(pid)
	{
		case -1: /* error del fork() */
			perror("fork error");
			printf("errno value= %d\n", errno);
			exit(-1); //exit(EXIT_FAILURE);
		case 0: /* proceso hijo */
			 
		if(execvp("gedit",argv)==-1)
			{
				perror("Falla en la ejecucion exec de ficheros gedit");
				printf("errno value= %d\n", errno);
				exit(EXIT_FAILURE);
			}
		default: /* padre */
			printf("padre con pid: %ld\n", (long)getpid());
			childpid=wait(&status);	
			if(childpid>0)
			{
				if (WIFEXITED(status)) {
					printf("child %d exited, status=%d\n",childpid, WEXITSTATUS(status));
				} else if (WIFSIGNALED(status)) {
					printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
				} else if (WIFSTOPPED(status)) {
					printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
				}
			}
   }
}
