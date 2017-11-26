#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <errno.h>

int* contador=NULL;


int main(){
  pid_t pid,childpid;
  int Id,i,j,status;
  printf("Cuantas hijos quieres crear: ");
 scanf("%d",&i);
  key_t Clave=ftok("/bin/cp",222);
  Id=shmget(Clave,sizeof(int)*2,0777|IPC_CREAT);
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
  contador[0]=0;
  contador[1]=0;
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
   if(contador[1]<j){
     while(contador[1]!=i) {
            printf("%d\n",i);
				usleep(100);
			}
           }
        for(j=0;j<100;j++){
        contador[0]++;
         }
        printf("proceso %d de padre %d, contador=%d\n",getpid(),getppid(),*contador);
        contador[1]++;
           shmdt ((char *)contador);
       exit(i);

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


}
