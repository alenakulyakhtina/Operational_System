#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main(void)
{
  int msqid;
  char pathname[]="Lab11.2a.c";
  key_t  key;
  int len, maxlen, i, j;

  struct mymsgbuf
  {
    long mtype;
    //char mtext[81];
    struct {
      int int_inf;
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

 for (i = 1; i <= 5; i++) {
    maxlen = sizeof(mybuf.info);
    if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0) < 0) {
      printf("Can\'t receive message from queue\n");
      exit(-1);
    }
    printf("message type = %ld, int = %i\n", mybuf.mtype, mybuf.info.int_inf);
  }

  for (j = 1; j <= 5; j++) {
    mybuf.mtype = 2;
    mybuf.info.int_inf = 22;
    len = sizeof(mybuf.info);
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
      printf("Can\'t send message to queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
      exit(-1);
    }
  }

  return 0;
}

