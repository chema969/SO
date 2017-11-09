#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> //Para estructura pid_t 
#include <sys/wait.h> 
#include <errno.h>

#define Clave (key_t) 235


int main(){
  pid_t pid,childpid;
  int contador=0,Id,i,j,status;
  Id=shmget(Clave,sizeof(int),IPC_CREAT|144);
   if(Id==-1){
    printf("No se ha podido acceder a memoria comprartida,patata\n");
    exit(0);
    } 
  scanf("%d",&i);
  for(j=0;j<i;j++){
   pid=fork();
   switch(pid){
     case -1:
        perror("fork error");
        printf("errno value= %d\n", errno); exit(EXIT_FAILURE);
     case 0:
        Id=shmget(Clave,sizeof(int),144); 
        if(Id==-1){
         printf("No se ha podido acceder a memoria comprartida\n");
         exit(0);
        } 
        contador=(int)shmat(Id,(char *)1,0);
        contador++;
        printf("proceso %d de padre %d, contador=%d\n",getpid(),getppid(),contador);
       exit(EXIT_SUCCESS);
      default: 
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

 printf("contador final=%d\n",contador);
}
