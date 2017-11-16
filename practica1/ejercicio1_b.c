#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int main(void) 
{
 pid_t pid;
 int i,j,childpid,status;
 printf("Cuantas hijos quieres crear: ");
 scanf("%d",&i);
 pid=fork();
 for(j=0;j<i-1;j++){
 switch(pid){
  case -1:
   perror("fork error");
   printf("errno value:%d\n",errno);
   exit(EXIT_FAILURE);
  case 0:
   pid=fork();
  }
}
   switch(pid){
   case -1:
   perror("fork error");
   printf("errno value:%d\n",errno);
   exit(EXIT_FAILURE);
   case 0: 
    exit(EXIT_SUCCESS);
   default:/* padre */
            printf("Proceso %d; padre = %d\n", getpid(), getppid());
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
exit(0);
}



