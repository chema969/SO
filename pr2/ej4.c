#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void *leeLineas(char* fichero){ 
  FILE *f;
  char j[1000];
  int *i;
  f=fopen(fichero,"r");
	if (f==NULL){
		printf("El archivo %s no existe\n", fichero);
		exit(-1);
	}
  i=(int*)malloc(sizeof(int));
  while(fgets(j,1000,f)){
    *i=*i+1;
  }
  printf("%s:%d\n",fichero,*i);
  pthread_exit(i);
  }

int main(int argc, char **argv){
 if(argc>1){
  int i,*s,sum=0;
  pthread_t t[argc-1];
  for(i=0;i<argc-1;i++){
    pthread_create(&t[i],NULL,(void*) leeLineas,argv[i+1]);

    }
  s=(int*)malloc(sizeof(int));
  for(i=0;i<argc-1;i++){
     pthread_join(t[i],(void **) &s);
     sum=sum+*s; 
     usleep(1000);
    }
  printf("suma total:%d\n",sum);
}
}
