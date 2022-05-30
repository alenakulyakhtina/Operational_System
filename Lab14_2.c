#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <signal.h>

int main(void) {
  (void)signal(SIGINT, my_handler);
  (void)signal(SIGQUIT, my_handler);

  while(1);

  return 0;
}

void my_handler(int nsig) {
  if (nsig == 2)
    printf("It's CTRL-C: %d\n", nsig);
  else if (nsig == 3)
    printf("It's CTRL-4: %d\n", nsig);
}
