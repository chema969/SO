#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static pthread_mutex_t sem = 
PTHREAD_MUTEX_INITIALIZER;
void rellena(int *camisetas);
void *cliente(int *v);
void *proveedor(int *v);
void imprime(int *v);
int main(){
   int *camisetas,i;
   pthread_t a[6];
   srand(time(NULL));
   camisetas=(int*)malloc(5*sizeof(int));
   rellena(camisetas);
   imprime(camisetas);
    for(i=0;i<6;i++){
     if(i%2==0)pthread_create(&a[i],NULL,(void*)cliente,camisetas);
     else pthread_create(&a[i],NULL,(void*)proveedor,camisetas);
     }
    for(i=0;i<6;i++)pthread_join(a[i],NULL);
pthread_mutex_destroy(&sem);
}


void rellena(int *camisetas){
  int i;
  for(i=0;i<5;i++){
    camisetas[i]=rand()%50;
   }
}

void imprime(int *v){
  int i;
  for(i=0;i<5;i++){
    printf("v[%d]=%d\n",i,v[i]);
   }
}
void *cliente(int *v){
   int i=rand()%5,j,k=rand()%50;
   pthread_mutex_lock (&sem);
   for(j=0;j<k;j++){
    v[i]--;
    }
    printf("Soy un cliente,disminui el %d %d veces\n\n",i,k);
    imprime(v);
    pthread_mutex_unlock (&sem);
    
 }

void *proveedor(int *v){
   int i=rand()%5,j,k=rand()%50;
   for(j=0;j<k;j++){
    pthread_mutex_lock (&sem);
    v[i]++;
    pthread_mutex_unlock (&sem);
    }
    pthread_mutex_lock (&sem); 
    printf("Soy un proveedor,aumente el %d %d veces\n\n",i,k);
    imprime(v);
    pthread_mutex_unlock (&sem);
 }
