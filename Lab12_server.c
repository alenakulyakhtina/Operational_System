#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define LAST_MESSAGE 255

int main(void)
{
  int msqid;                  // IPC descriptor for the message queue
  char pathname[]="Lab12_server.c";  // The file name used to generate the key.
  key_t  key;                 // IPC key
  int i, j, len, maxlen;       // Cycle counter and the length of the informative part of the message

  struct mymsgbuf // Custom structure for the message
  {
    long mtype;
    struct {
      double ind;
      pid_t pid;
    } info;
  } mybuf;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t get msqid\n");
    exit(-1);
  }

  /* Send information */

  while (1) {
    maxlen = sizeof(mybuf.info);
    if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0) < 0) {
      printf("Can\'t send message!\n");
      exit(-1);
    }
    mybuf.mtype = mybuf.info.ind;
    mybuf.info.ind = mybuf.info.ind * mybuf.info.ind;
    len = sizeof(mybuf.info);
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
          printf("Can't send message!\n");
          msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
          exit(-1);
  }
  return 0;
}
