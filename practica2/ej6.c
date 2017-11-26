#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void* cien(int *contador){
int j;
 for(j=0;j<100;j++){
        (*contador)++;
         }
}

int main(){
 int i,contador=0;
 pthread_t t[3];
  for(i=0;i<3;i++){
   pthread_create(&t[i],NULL ,(void*)cien, &contador);
   }
  for(i=0;i<3;i++){
   pthread_join(t[i],NULL);
  }
  printf("%d\n",contador);
 }
