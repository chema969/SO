#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int main(void){
 pid_t pid; 
 int childpid,status;
 pid=fork();
 switch(pid){
  case -1:
    perror("fork error");
    printf("error name:%d\n",errno);
    exit(EXIT_FAILURE);
  case 0: 
    printf("Pid mio=%d, mi patriarca:%d\n",getpid(),getppid());
    exit(EXIT_SUCCESS);
  default:
    system("ps -a");
    sleep(20);
    childpid=wait(&status);
     if(childpid>0){
       if(WIFEXITED(status)){
         printf("status %d exited:%d\n",childpid,WEXITSTATUS(status));
        }
       else if (WIFSIGNALED(status)) {
                    printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
        }
  } else if (WIFSTOPPED(status)) {
                    printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
                } 
            }
         
            //return 0;
    
  
}
