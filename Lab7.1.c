#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// 1
int main()
{
  char    *array;
  int     shmid;
  int     new = 0;
  char    pathname[] = "07-1a.c";
  key_t   key;

  
  FILE *file = fopen("Lab7.txt","r");
  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((shmid = shmget(key, 5000*sizeof(char), 0666|IPC_CREAT)) < 0) {
      printf("Can\'t create shared memory\n");
      exit(-1);
    
  }

  if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }
  // Читаем пока не закончится файл.
    while (!feof(file) & new < 5000) {
    array[new] = fgetc(file);
    new++;
  }
  printf("OK");
  if (shmdt(array) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }
  fclose(file);

  return 0;
}
