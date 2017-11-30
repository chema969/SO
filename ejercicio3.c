#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NPROC 5
#define QUANTUM 3
typedef struct params
{
    char nombre[10];
    int t_ejec;  // Se introducen
    int t_lleg;  
    int t_com;   // Se calculan
    int t_fin;
    int t_ret;
    int t_esp;
    int t_rest;
} parametros;
int FIFOvive(parametros *FIFO));
void entraFINAL(parametros *FIFO,parametros p,int tam);
void main(){
    
    int i,cicloreloj=0,q,tam;
    // Inicialización de los datos de procesos
    parametros procesos[NPROC];    
    parametros *FIFO;
    strcpy(procesos[0].nombre, "A");
    procesos[0].t_ejec = 8;
    procesos[0].t_lleg = 0;
    procesos[0].t_com = 0;
    procesos[0].t_rest = 8;

    strcpy(procesos[1].nombre, "B");
    procesos[1].t_ejec = 4;
    procesos[1].t_lleg = 1;
    procesos[1].t_rest = 4;

    strcpy(procesos[2].nombre, "C");
    procesos[2].t_ejec = 9;
    procesos[2].t_lleg = 2;
    procesos[2].t_rest = 9;

    strcpy(procesos[3].nombre, "D");
    procesos[3].t_ejec = 5;
    procesos[3].t_lleg = 3;
    procesos[3].t_rest = 5;

    strcpy(procesos[4].nombre, "E");
    procesos[4].t_ejec = 2;
    procesos[4].t_lleg = 4;
    procesos[4].t_rest = 2;

    printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera\n");
    printf("-------------------------------------------------------\n");
    FIFO=(parametros*)malloc(sizeof(parametros));
    tam=0;
    while(FIFOvive(FIFO)){
      q=3;
      while((q)&&(FIFO[0].t_rest)){
        q--;
        FIFO[0].t_rest--; 
        cicloreloj++;
        for (i=1;i<NPROC;i++){ 
          if(cicloreloj==procesos[i].t_lleg)    {tam++;FIFO=entraFINAL(FIFO,procesos[i],tam);}
        }
      


    }
}

int FIFOvive(parametros *FIFO)){
    if(FIFO==NULL) return 0;
    else return 1;
    }

void entraFINAL(parametros *FIFO,parametros p,int tam){
     parametros *PIPO;
     PIPO = (parametros*) realloc (FIFO, sizeof(parametros))
     PIPO[tam]=p;
     return PIPO;
}
