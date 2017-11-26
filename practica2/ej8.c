#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

void *consumidor(int *v);
void quitaritem(int* v);
void * productor(int *v);
void poneritem(int* v);
void imprimir(int *v,char *c);

int vacio=5,lleno=0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t si_vacio = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t si_lleno= PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t esperar_hilos= PTHREAD_MUTEX_INITIALIZER;

int main(){
  int *v;
  int i;
  srand(time(NULL));
  
  v=(int*)malloc(5*sizeof(int));
  pthread_t hilos[20],hilofinal;
  pthread_mutex_lock (&esperar_hilos); 
  pthread_mutex_lock (&si_vacio); 
   for(i=0;i<20;i++){
     printf("Hilo %d\n",i);
     if(rand()%2==0)pthread_create(&hilos[i],NULL,(void*)consumidor,v);
     else pthread_create(&hilos[i],NULL,(void*)productor,v);
    }
  pthread_mutex_unlock(&esperar_hilos);
  pthread_mutex_lock (&esperar_hilos);
   for(i=0;i<20;i++)
     pthread_join(hilos[i],NULL);
  pthread_mutex_unlock(&esperar_hilos);
  pthread_mutex_destroy(&mutex);
  pthread_mutex_destroy(&si_lleno);
  pthread_mutex_destroy(&si_vacio);
  pthread_mutex_destroy(&esperar_hilos);
}

void *consumidor(int *v){ 
 if(vacio==4||vacio==5)  pthread_mutex_lock (&si_vacio);
  pthread_mutex_lock (&mutex);
  quitaritem(v);
  if(lleno==4)pthread_mutex_unlock (&si_lleno);
  imprimir(v,"consumidor");
  pthread_mutex_unlock (&mutex);
}

void quitaritem(int* v){
  int i=0;
   while((v[i]!=0)&&(i<5)) i++;
  printf("soy consumidor y quite el valor %d\n" ,i-1);
  v[i-1]=0;
  vacio++;
  lleno--;
  printf("Consumidor: lleno:%d, vacio:%d\n",lleno,vacio);
  }





void * productor(int *v){
 if(lleno==4||lleno==5)  pthread_mutex_lock (&si_lleno); 
  pthread_mutex_lock (&mutex);   
  poneritem(v);
  if (vacio==4)pthread_mutex_unlock (&si_vacio); 
  imprimir(v,"productor");
  pthread_mutex_unlock (&mutex);
}



void poneritem(int* v){
  int i=0,k;
  while(v[i]!=0) i++;
  printf("Soy productor y puse en el valor %d\n",i);
  v[i]=rand()%5+1;
  lleno++;
  vacio--;
  printf("Productor: lleno:%d, vacio:%d\n",lleno,vacio);
  }

void imprimir(int *v,char *c){
  int i;
  printf("El %s \n",c);
  for(i=0;i<5;i++){
    printf("v[%d]=%d\n",i,v[i]);
   }
  }
