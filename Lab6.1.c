#define _GNU_SOURCE
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
  int pfd;
  int size = 0;
  int state = 0;
  int fd[2];
  
  if ((pfd = pipe(fd)) < 0) {
      printf("ERROR");
      exit(-1);
    
  } else {
     mkfifo("./some-fifo", 0644);
     fd[1] = open("./some-fifo", O_RDWR);
  }
  printf("\nPipe size: %d", fcntl(fd[1], F_GETPIPE_SZ));
  
  return 0;
}
