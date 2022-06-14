#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sendpid;
int num = 0b11111111111111111111111111111111;
int step = 0;

void zero() {
  num = num ^ (1 << step);
  step++;
  if (step == 32) {
    printf("Get number: %d\n", num);
    exit(0);
  } else {
    printf("Get %d bit: %d\n", step, 0);
    kill(sendpid, SIGUSR1);
  }
}

void one() {
  step++;
  if (step == 32) {
    printf("Get number %d\n", num);
    exit(0);
  } else {
    printf("Get %d bit: %d\n", step, 1);
    kill(sendpid, SIGUSR1);
  }
}

int main(void) {
  (void)signal(SIGUSR1, zero);
  (void)signal(SIGUSR2, one);

  printf("PID: %d\n", getpid());
  printf("Input: ");
  scanf("%d", &sendpid);

  while(1) {};
  return 0;
}
