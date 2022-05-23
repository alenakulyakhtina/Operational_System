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
  int msqid;
  char pathname[]="Lab12_server.c";
  key_t  key;
  int len, maxlen, i, j;
  double inf;

  struct mymsgbuf
  {
    long mtype;
    struct {
      double ind;
      pid_t pid;
    } info;
  } mybuf;

  scanf("%lf", &inf);


  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t get msqid\n");
    exit(-1);
  }

  mybuf.mtype = 1;
  mybuf.info.pid = getpid();
  mybuf.info.ind = inf;
  len = sizeof(mybuf.info);

  printf("Sending message to server\n");
  
  if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
        printf("Can't send message!\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
  }
  
  printf("Sent message\n");
  
  maxlen = sizeof(mybuf.info);
  if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, getpid(), 0) < 0) {
      printf("Can't recive message!\n");
      exit(-1);
  }

  printf("Success! %ld, %lf\n", mybuf.info.pid, mybuf.info.ind);


  return 0;
}
