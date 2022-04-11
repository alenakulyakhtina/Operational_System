#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
  int    semid;        // IPC descriptor for an array of IPC semaphores
  char   pathname[]="Lab9_bonus1.c"; // The file name used to generate the key.
                               // A file with this name must exist in the current directory
  key_t  key;          // IPC key
  struct sembuf mybuf; // Structure for specifying operations on a semaphore.

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t create semaphore set\n");
    exit(-1);
  }

  mybuf.sem_num = 0;
  mybuf.sem_op  = -5;
  mybuf.sem_flg = 0;

  if (semop(semid, &mybuf, 1) < 0) {
    printf("Can\'t wait for condition\n");
    exit(-1);
  }

  printf("The condition is present\n");
  return 0;
}
