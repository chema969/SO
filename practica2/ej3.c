#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


struct p{
   int *v;
   int tam; 
   };
void rellenavector(int* v);
int hilos(int tam,int rupt,int *v);
void muestra(int *v,int j);
void* suma(struct p *p);

int main(int argc,char **argv){
 if(argc==2){
   int *v,j;
   v=(int*)malloc(10*sizeof(int));
   rellenavector(v);
   muestra(v,10);
   printf("La suma es %d\n",    hilos(10,atoi(argv[1]),v));
   free(v);
   v=NULL;
  }
}

void rellenavector(int* v){
  int i;
  srand(time(NULL));
  for(i=0;i<10;i++){
   v[i]=rand()%21;
    }
  }
void muestra(int *v,int j){
  int i;
  for(i=0;i<j;i++){
    printf("v[%d]=%d\n",i,v[i]);
}
}

int hilos(int tam,int rupt,int *v){
  int sum=0,i,j,k,l=0;//j=tamaño de cada subvector;rupt=numero de subvectores
  pthread_t r[rupt];
  int *s;
    
/*j=10/rupt;
    struct p p[rupt];
    for(k=0;k<rupt;k++){
      p[k].tam=j;
      p[k].v=(int*)malloc(j*sizeof(int));
      for(i=0;i<j;i++){
       p[k].v[i]=v[l];
       l++;
       }
     }*/ j=tam/rupt;
  struct p p[rupt];
  for(i=0;i<rupt-1;i++){
   p[i].v=(int*)malloc(j*sizeof(int));
   p[i].tam=j;
    for(k=0;k<j;k++){
      p[i].v[k]=v[l];
      l++;
    }
   }
  j=j+tam%rupt;
  p[rupt-1].v=(int*)malloc(j*sizeof(int));
  p[rupt-1].tam=j;
  for(i=0;i<j;i++){
    p[rupt-1].v[i]=v[l];
    l++;
  }
    for(i=0;i<rupt;i++){
       pthread_create(&r[i],NULL,(void*) suma,&p[i]);
       usleep(10000);
       }
    for(i=0;i<rupt;i++){
       pthread_join(r[i],(void **) &s);
       sum=sum+*s;
       usleep(1000); 
       }

    return sum;
  
}


void* suma(struct p *p){
  int *sum;
  int i;
  sum=(int*)malloc(sizeof(int));
  *sum=0;
  muestra(p->v,p->tam);
  for(i=0;i<p->tam;i++){
    *sum=p->v[i]+*sum;
   }
   pthread_exit(sum); 
}
