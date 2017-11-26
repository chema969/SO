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
    printf("Pid mio=%d, mi padre:%d\n",getpid(),getppid());
  default:
    system("ps -a");
    sleep(20);
    exit(EXIT_SUCCESS);
         
            //return 0;

}
}
