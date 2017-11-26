#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
void salir(char* nombre,int sum_ant);
int esperar();
int main(void){
   pid_t pid;
   int sum=0,sum1,sum2=0;
   pid=fork();
   if (pid==0)salir("hijo 1",0);
   sum1=esperar();
   pid=fork();
   if (pid==0){//hijo 2 
     pid=fork();//nieto 1
      if (pid==0) salir("nieto 1",0);
        sum2=esperar();
           
     pid=fork();//nieto 2
      if (pid==0){
        pid=fork();
        if (pid==0) salir("bisnieto",0);  
         sum=esperar();
            
        salir("nieto 2",sum);
        }
       sum=esperar();
           
      salir("hijo 2",sum+sum2);
       sum=esperar();
           
     }
    sum2=esperar();
   printf("La suma es %d\n",sum1+sum2);


}
void salir(char* nombre,int sum_ant){
   
   printf("Soy el %s %d y mi padre es %d, paso %d a mi padre\n",nombre,getpid(),getppid(),getpid()%10);
   exit((getpid()%10)+sum_ant);  
}

int esperar(){
 int s=0,status,childpid;
 childpid=wait(&status);

   if(WIFEXITED(status)) s=WEXITSTATUS(status);

return s;
}
