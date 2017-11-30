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
int FIFOvive(parametros *FIFO);
void entraFINAL(parametros *FIFO,parametros p,int tam);
void ponevalores(parametros *FIFO,parametros *procesos,int cicloreloj,int * tam);
void reordenar(parametros *FIFO,int tam);
void imprime(parametros *FIFO, int tam);
void main(){
    
    int i,cicloreloj=0,q,tam,j;
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
    FIFO[0]=procesos[0];
    tam=0;
    while(tam!=-1){  
      q=0;
      if(FIFO[0].t_rest==FIFO[0].t_ejec){  
       for (j=0;j<NPROC;j++){ 
        if(strcmp(FIFO[0].nombre,procesos[j].nombre)==0) procesos[j].t_com=cicloreloj; 
         }
       }
      while((q!=QUANTUM)&&(FIFO[0].t_rest)){
        q++;
        FIFO[0].t_rest--; 
        cicloreloj++;
        for (i=1;i<NPROC;i++){ 
          if(cicloreloj==procesos[i].t_lleg)    {tam++;entraFINAL(FIFO,procesos[i],tam);}
        }
       }
      if(FIFO[0].t_rest==0) ponevalores(FIFO,procesos,cicloreloj,&tam);
      else reordenar(FIFO,tam);
    }

   for(i=0; i< NPROC; i++)
    {
        procesos[i].t_ret = procesos[i].t_fin - procesos[i].t_lleg;
        procesos[i].t_esp = procesos[i].t_ret - procesos[i].t_ejec;

        printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[i].nombre,procesos[i].t_com, procesos[i].t_fin, procesos[i].t_ret, procesos[i].t_esp);
    }    
}

int FIFOvive(parametros *FIFO){
    if(FIFO==NULL) return 0;
    else return 1;
    }

void entraFINAL(parametros *FIFO,parametros p,int tam){
     FIFO = (parametros*) realloc (FIFO, sizeof(parametros)*(tam+1));
     FIFO[tam]=p;
}

void ponevalores(parametros *FIFO,parametros *procesos,int cicloreloj,int * tam){
    int j;
     for (j=0;j<NPROC;j++){ 
        if(strcmp(FIFO[0].nombre,procesos[j].nombre)==0) procesos[j].t_fin=cicloreloj;
       }
    int i;
      for(i=0;i<(*tam);i++) FIFO[i]=FIFO[i+1];
      FIFO=(parametros*) realloc (FIFO, sizeof(parametros)*(*tam));
       *tam=*tam-1;
} 

void reordenar(parametros *FIFO,int tam){
     int i;
     parametros aux=FIFO[0];     
     for(i=0;i<tam;i++) FIFO[i]=FIFO[i+1];
     FIFO[i]=aux;
}

void imprime(parametros *FIFO, int tam){
     int i;
     for(i=tam;i>-1;i--) printf(" %s ",FIFO[i].nombre);
     printf("%d\n",tam);
    }
