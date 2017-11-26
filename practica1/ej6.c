#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int contador=0;
int main(){
  int n,i;
  scanf("%d",&n);
  pid_t pid;
    int status, childpid;

   for(i=0;i<n;i++){ 
    pid = fork(); 
    
    switch(pid)
    {
        case -1:
            perror("fork error");
            printf("errno value= %d\n", errno); exit(EXIT_FAILURE); 
            //return (-1);
            
        case 0: /* proceso hijo */
            contador++;	
            printf("Proceso hijo %d; padre = %d,contador=%d \n", getpid(), getppid(),contador); 
            exit(EXIT_SUCCESS);
      }
     }      
        if(pid!=0){ /* padre */
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
         
            //return 0;
    }
   exit(EXIT_SUCCESS);
  
}
