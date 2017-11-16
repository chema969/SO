#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
struct p{
  int *v;
  int *v_m;
   };
void rellena(int **m);
void imprime(int **m);
void rellena_v(int* v);
void imprime_v(int* v);
void* mult(struct p *p);

int main(){
  int **m,*v,*sum,*v_final;
  pthread_t v_hilo[3];
  int i;
  struct p p;
    srand(time(NULL));

   m=(int**)malloc(sizeof(int*)*3);
    for (i=0;i<3;i++) {
       m[i]=(int*)malloc(sizeof(int)*3);
   }
  v=(int*)malloc(sizeof(int)*3);
  rellena(m);
  imprime(m);
  rellena_v(v);
  printf("Vector por el que se multiplica: ");
  imprime_v(v);
  imprime_v(v);
  p.v=v;
  for(i=0;i<3;i++){
    p.v_m=m[i];
    pthread_create(&v_hilo[i],NULL,(void*) mult,&p);
    sleep(1);
   }
  v_final=(int*)malloc(sizeof(int)*3);
  for(i=0;i<3;i++){
      pthread_join(v_hilo[i],(void**)&sum);
      v_final[i]=*sum;
  }
  printf("Vector final: ");
  imprime_v(v_final);
}











void rellena(int **m){
  int i,j;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){ 
      m[i][j]=rand()%10;
      }
   }
}

void imprime(int **m){
  int i,j;
  for(i=0;i<3;i++){
   printf("(");
    for(j=0;j<3;j++){ 
      printf(" %d ",m[i][j]);
      }
    printf(")\n");
   }
}

void rellena_v(int* v){
  int i;
  for(i=0;i<3;i++){
    v[i]=rand()%10;
    }
  }

void imprime_v(int* v){
    int i;
   printf("(");
  for(i=0;i<3;i++){
    printf(" %d ",v[i]);
    }
  printf(")\n");
  }

void* mult(struct p *p){
  int i;
  int *sum=NULL;
  sum=(int*)malloc(sizeof(int));
    if(sum==NULL){
      printf("Error al reservar memoria");
      exit(-1);
      }
  *sum=0;
  printf("Vector v_m: ");
  imprime_v(p->v_m);
    printf("Vector v: ");
  imprime_v(p->v);
  
   for(i=0;i<3;i++){
     *sum=(p->v[i])*(p->v_m[i])+*sum;
    }
  printf("La multiplicacion de esta fila es %d\n",*sum);
  pthread_exit(sum);
}
