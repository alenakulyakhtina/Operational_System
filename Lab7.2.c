#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// 2
int main()
{
  char    *array;   
  int     shmid;     
  int     new = 0;   
  char    pathname[] = "07-1a.c"; 
                                  
  key_t   key;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((shmid = shmget(key, 5000*sizeof(char), 0666|IPC_CREAT)) < 0) { 
      printf("Can\'t find shared memory\n");
      exit(-1);
    
  }

  if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
    printf("Can't attach shared memory\n");
    exit(-1);
  }
  // Печатаем пока не закончатся строки.
  while(array[new] != '\0') {
    printf("%c", array[new]);
    new++;
  }
  printf("OK\n");
  if (shmdt(array) < 0) {
    printf("Can't detach shared memory\n");
    exit(-1);
  }

  return 0;
}
