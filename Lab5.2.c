#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int fd[2], fd2[2], result;
  size_t size;
  char  resstring[14], resstring2[14];

  pipe(fd); 
  pipe(fd2);

  result = fork();

  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (result > 0) {

   /* Parent process */

    if (close(fd[0]) < 0) {
      printf("parent: Can\'t close reading side of pipe\n"); exit(-1);
    }    
    size = write(fd[1], "Hello, world!", 14);

    if (size != 14) {
      printf("Can\'t write all string to pipe\n");
      exit(-1);
    }

    if (close(fd[1]) < 0) {
      printf("parent: Can\'t close writing side of pipe\n"); exit(-1);
    }

    printf("Parent exit\n");

  } else {
    if (close(fd2[0]) < 0) {
      printf("child: Can\'t close writing side of pipe\n"); exit(-1);
    }
    close(fd[1]);
    size = read(fd[0], resstring, 14);

    if (size < 0) {
      printf("Can\'t read string from pipe\n");
      exit(-1);
    }
    close(fd[0]);
    printf("Child exit, resstring:%s\n", resstring);
    size = write(fd2[1], "World, hello!", 14); 
    if (close(fd2[1]) < 0) {
      printf("child: Can\'t close reading side of pipe\n"); exit(-1);
    }
  }

  sleep(2);

  if (result > 0) { 
    close(fd2[1]);
    size = read(fd2[0], resstring2, 14); 
    printf("%s\n", resstring2); 
    if (close(fd2[0]) < 0) {
      printf("child: Can\'t close reading side of pipe\n"); exit(-1);
    }
    printf("Parent exit\n"); 
}

  return 0;
}
