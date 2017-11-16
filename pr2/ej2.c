#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void *numerosrand(){
   int i,j;
   int *sum;
   sum=(int*)malloc(sizeof(int));

     j=rand()%10;
     printf("%d\n",j);
     i=rand()%10;
     printf("%d\n",i);
     *sum=i+j;
     printf("sum=%d\n",*sum);
     pthread_exit(sum);  
   }

int main(){
  int i,j,sum=0;
  int *s;
  srand(time(NULL));
  printf("Introduce numero de hilos: ");
  scanf("%d",&i);
  pthread_t rand[i];
  for(j=0;j<i;j++){
     pthread_create(&rand[j],NULL,(void*) numerosrand,NULL);
     usleep(100000);

    }
  for(j=0;j<i;j++){
     pthread_join(rand[j],(void **) &s);
     sum=sum+*s;
     usleep(1000);
    }
  printf("la suma es %d",sum);
  }
