#include <stdio.h>
#include <string.h>

#define NPROC 5

typedef struct params
{
    char nombre[10];
    int t_ejec;  // Se introducen
    int t_lleg;  
    int t_com;   // Se calculan
    int t_fin;
    int t_ret;
    int t_esp;
    
} parametros;



int main(){
  parametros procesos[NPROC];
    int cicloreloj=0,i;    
    strcpy(procesos[0].nombre, "A");
    procesos[0].t_ejec = 8;
    procesos[0].t_lleg = 0;
    procesos[0].t_com = 0;
    procesos[0].t_fin = procesos[0].t_ejec;
    procesos[0].t_ret = procesos[0].t_fin;
    procesos[0].t_esp = 0;

    strcpy(procesos[1].nombre, "B");
    procesos[1].t_ejec = 4;
    procesos[1].t_lleg = 1;

    strcpy(procesos[2].nombre, "C");
    procesos[2].t_ejec = 9;
    procesos[2].t_lleg = 2;

    strcpy(procesos[3].nombre, "D");
    procesos[3].t_ejec = 5;
    procesos[3].t_lleg = 3;

    strcpy(procesos[4].nombre, "E");
    procesos[4].t_ejec = 2;
    procesos[4].t_lleg = 4;

    printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera\n");
    printf("-------------------------------------------------------\n");
    for(i=0; i< NPROC; i++)
    { 
      cicloreloj=cicloreloj+procesos[i].t_ejec;
      int j=99999999,k;
     while(j==99999999){
      for(k=i+1;k<NPROC;k++){
        if(procesos[k].t_lleg<cicloreloj){
          if(procesos[k].t_ejec<j)j=procesos[k].t_ejec;
          }
       }
       if(i==NPROC-1) j=procesos[k].t_ejec;
      for(k=i+1;k<NPROC;k++){
        if(procesos[k].t_ejec==j){  
           parametros aux;
           aux=procesos[i+1];
           procesos[i+1]=procesos[k];
           procesos[k]=aux;}
         }
       if(j==99999999)cicloreloj++;
      }
  if(i!=NPROC-1){
  procesos[i+1].t_com=cicloreloj;
  procesos[i+1].t_fin=procesos[i+1].t_com+procesos[i+1].t_ejec;
  procesos[i+1].t_ret=procesos[i+1].t_fin-procesos[i+1].t_lleg;
  procesos[i+1].t_esp=procesos[i+1].t_ret-procesos[i+1].t_ejec;}
    
 printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[i].nombre,procesos[i].t_com, procesos[i].t_fin, procesos[i].t_ret, procesos[i].t_esp);
}
}
