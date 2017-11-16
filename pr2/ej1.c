#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
void * imprime(char* cadena){  
 for(int i=0;i<strlen(cadena);i++){
  printf("%c",cadena[i]); 
  }
  }


int main(){
   pthread_t hilo1, hilo2;
   char *i1="Hola",*i2="Mundo";
   pthread_create(&hilo1,NULL ,(void*)imprime, i1);
   sleep (1);
   pthread_create(&hilo2,NULL ,(void*)imprime, i2);
   pthread_join(hilo1,NULL);
   pthread_join(hilo2,NULL);
   }

