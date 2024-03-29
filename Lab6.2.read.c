#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// reading (pseudo_child)
int main()
{
  int     fd;

  size_t  size;
  char    resstring[14];
  char    name[] = "aaa.fifo";
  
    /* pseudo_child process */

    if ((fd = open(name, O_RDONLY)) < 0) {
      printf("Can\'t open FIFO for reading\n");
      exit(-1);
    }

    size = read(fd, resstring, 14);

    if (size < 0) {
      printf("Can\'t read string from FIFO\n");
      exit(-1);
    }

    printf("pseudo_child exit, resstring:%s\n", resstring);

    if (close(fd) < 0) {
      printf("pseudo_child: Can\'t close FIFO\n"); exit(-1);
    }

  return 0;
}
