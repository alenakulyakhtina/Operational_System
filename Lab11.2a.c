#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255 // Message type for termination of program 11-1b.c

int main(void)
{
  int msqid;      // IPC descriptor for the message queue
  char pathname[]="Lab11.2a.c"; // The file name used to generate the key.
  key_t  key;     // IPC key
  int i, j, len, len2;      // Cycle counter and the length of the informative part of the message

  struct mymsgbuf // Custom structure for the message
  {
    long mtype;
    struct {
      int int_inf;
    } info;
  } mybuf;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }
  //
  // Trying to get access by key to the message queue, if it exists,
  // or create it, with read & write access for all users.
  //
  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t get msqid\n");
    exit(-1);
  }

  /* Send information */

  for (i = 1; i <= 5; i++) {
    mybuf.mtype = 1;
    mybuf.info.int_inf = 11;
    len = sizeof(mybuf.info);
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
      printf("Can\'t send message to queue\n");
      msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
      exit(-1);
    }
  }

  for (j = 1; j <= 5; j++) {
    len2 = sizeof(mybuf.info);
    if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, len2, 2, 0) < 0) {
      printf("Can\'t receive message from queue\n");
      exit(-1);
    }
    printf("message type = %ld, int = %i\n", mybuf.mtype, mybuf.info.int_inf);
  }
  msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);


  return 0;
}
