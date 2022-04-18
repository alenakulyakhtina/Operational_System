#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>

/* for in range N {
  *check* {
  Parent process:
  A
  Z
  reading
  } 
  else {
  Child process:
  D
  reading
  writting
  D
  }
}
closing and exit
 */

int main()
{
  int     fd[2], result;

  size_t size;
  char  resstring[14];

  char    pathname[] = "Lab10.c";
  key_t   key;
  long    i;
  int    semid;
  struct sembuf mybuf;

  int N;
  scanf("%d", &N);

  if (pipe(fd) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }
  if ((key = ftok(pathname,0)) < 0) {
      printf("Can\'t generate key\n");
      exit(-1);
  }

  if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
      printf("Can\'t create semaphore set\n");
      exit(-1);
  }
  
  result = fork();

  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } 
  
  for (int i = 0; i < n; i++) {
    if (result > 0) {
       /* Parent process */
      size = write(fd[1], "Hello, world! It's parent:)", 14);
      if (size != 14) {
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }
      
      /* A */
      mybuf.sem_num = 0;
      mybuf.sem_op = 2;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }
      /* Z */
      mybuf.sem_num = 0;
      mybuf.sem_op = 0;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }

      /* read */
      size = read(fd[0], resstring, 14);
      if (size != 14) {
        printf("Can\'t read string from pipe.\n");
        exit(-1);
      }
      printf("Parent process read - successful; resstring: %s\n", resstring);
    } else {
      /* Child process */
      /* D */
      mybuf.sem_num = 0;
      mybuf.sem_op = -1;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }
      /* read */
      size = read(fd[0], resstring, 14);
      if (size != 14) {
        printf("Can\'t read string from pipe\n");
        exit(-1);
      }
      printf("Child process read - successful; resstring: %s\n", resstring);
      
      /* write */
      size = write(fd[1], "Hello, world! It's child:)", 14);
      if (size != 14) {
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }
      /* D */
      mybuf.sem_num = 0;
      mybuf.sem_op = -1;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }
    }
  }
  if (close(fd[0]) < 0) {
      printf("child: Can\'t close reading side of pipe\n"); exit(-1);
    }
  if (close(fd[1]) < 0) {
      printf("child: Can\'t close writing side of pipe\n"); exit(-1);
    }
  printf("Exit - successful\n");

  return 0;
}
