#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para fork()
#include <errno.h>

int main(void) {
 pid_t pid,childpid;
 int i,j,status;
 printf("Cuantas hijos quieres crear: ");
 scanf("%d",&i);
 for(j=0;j<i;j++){
   pid=fork();
   switch(pid){
   case -1:
    perror("fork error");
   printf("errno value:%d\n",errno);
   exit(EXIT_FAILURE);
   break;
  case 0:
   printf("Soy el hijo %d,mi pid:%d, mi padre:%d\n",j,getpid(),getppid());
  break;
  default:
   childpid=wait(&status);
    if(childpid>0){
      if (WIFEXITED(status)) {
       printf("child %d exited, status=%d\n",childpid, WEXITSTATUS   (status)); }
      else if(WIFSIGNALED(status)){
       printf("child %d killed (signal %d)\n", childpid, WTERMSIG(status)); }
      else if (WIFSTOPPED(status)) {
          printf("child %d stopped (signal %d)\n", childpid, WSTOPSIG(status)); }
}
exit(EXIT_SUCCESS);
}
}

}
