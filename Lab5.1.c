#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
  int     fd;
  size_t  size;
  char    string[14];
  
  if ((fd = open("myfile", O_RDONLY, 0666)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }

  size = read(fd, string, 14);
  printf("%s", string);

  if (close(fd) < 0) {
    printf("Can\'t close file\n");
  }

  return 0;
}
