#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main(int argc,char **argv){
if(argc==2){
   int status,childpid;
   pid_t pid;
   FILE *f;
   f=fopen(argv[1],"w");
   
   pid=fork();
switch(pid){
   case -1:
    perror("fork error");
    printf("error name:%d\n",errno);
    exit(EXIT_FAILURE);
   case 0:
     fprintf(f,"------\n");
    sleep(1); 
     exit(EXIT_SUCCESS);
   default:
    childpid=wait(&status);
     fprintf(f,"++++++\n");
    sleep(1);
    if(childpid>0){
      if (WIFEXITED(status))
        printf("Proccess exited,status %d",WEXITSTATUS(status));
      else if (WIFSIGNALED(status)) 
                    printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status));
                else if (WIFSTOPPED(status)) 
                    printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status));
                
    
              }
     
}
fclose(f);
}
}



