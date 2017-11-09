#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct p{
  int *v;
  int tam;
   };
void rellena(int *v,int tam);
void lee(int *v,int tam);

int main(){
  int *v;
  int tam=10,part,i,j,k,l=0;
  scanf("%d",&part);
  v=(int*)malloc(10*sizeof(int));
  rellena(v,tam);
  lee(v,tam);
  j=tam/part;
  struct p p[part];
  for(i=0;i<part-1;i++){
   p[i].v=(int*)malloc(j*sizeof(int));
   p[i].tam=j;
    for(k=0;k<j;k++){
      p[i].v[k]=v[l];
      l++;
    }
   }
  j=j+tam%part;
  p[part-1].v=(int*)malloc(j*sizeof(int));
  p[part-1].tam=j;
  for(i=0;i<j;i++){
    p[part-1].v[i]=v[l];
    l++;
  }
 for(i=0;i<part;i++){
   lee(p[i].v,p[i].tam);
   }
 printf("Sin violacion de segmento, comemela dani\n");
 }

void rellena(int *v,int tam){
  int i;
  srand(time(NULL));
   for(i=0;i<tam;i++){
    v[i]=rand()%10;
     }
}

void lee(int *v,int tam){
   int i;
   for(i=0;i<tam;i++){
     printf("v[%d]=%d\n",i,v[i]);
     }
}

