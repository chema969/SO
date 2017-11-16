#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <errno.h>

int* contador;


int main(){
  pid_t pid,childpid;
  int Id,i,j,status;
  printf("Cuantas hijos quieres crear: ");
 scanf("%d",&i);
  key_t Clave=ftok("/bin/cp",222);
  Id=shmget(Clave,sizeof(int),0777|IPC_CREAT);
   if(Id==-1){
    printf("No se ha podido acceder a memoria comprartida\n");
    exit(0);
    } 
 contador=(int*)shmat(Id,0,0);
         if ((char*)contador == NULL)
	{
		printf("No consigo memoria compartida\n");
		exit (0);
	}
  *contador=0;
  for(j=0;j<i;j++){
   pid=fork();
   switch(pid){
     case -1:
        perror("fork error");
        printf("errno value= %d\n", errno); exit(EXIT_FAILURE);
     case 0:
        contador=(int*)shmat(Id,0,0);
         if ((char*)contador == NULL)
	{
		printf("No consigo memoria compartida\n");
		exit (0);
	}
        for(j=0;j<100;j++){
        (*contador)++;
         }
        printf("proceso %d de padre %d, contador=%d\n",getpid(),getppid(),*contador);
           shmdt ((char *)contador);
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
    printf("contador final=%d\n",*contador);
   shmctl (Id, IPC_RMID, (struct shmid_ds *)NULL);

}
