#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <signal.h>

int main(void) {
  (void)signal(SIGINT, isSignal);
  (void)signal(SIGQUIT, isSignal);

  while(1);

  return 0;
}

void isSignal(int signl) {
  if (signl == 2)
    printf("It's CTRL-C: %d\n", signl);
  else if (signl == 3)
    printf("It's CTRL-4: %d\n", signl);
}
