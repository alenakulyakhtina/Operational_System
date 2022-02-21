#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
  int pfd;
  int size = 0;
  int state = 0;
  int fd[2];
  
  if ((pfd = pipe(fd)) < 0) {
      printf("ERROR");
      exit(-1);

  } else {
    while (state == 1) {
        if (write(fd[1], "p", 1) > 0) {
          size++;
        } else {
          state = 1;
        }
    }
  }
  printf("%d\n", size);
  
  return 0;
}
