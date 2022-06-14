#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int received = 1;
void wait() { received = 1; }

int main(void) {
  (void)signal(SIGUSR1, wait);
  printf("PID: %d\n", getpid());

  int recpid, num; 
  printf("Enter receiver\'s PID: ");
  scanf("%d", &recpid);

  printf("Input: ");
  scanf("%d", &num);

  for (int i = 0; i < 32; ++i) {
    if ((num & (1 << i)) == 0) {
      kill(recpid, SIGUSR1);
    } else {
      kill(recpid, SIGUSR2);
    }
    received = 0;
    while (i != 31 && received == 0) {}
  }

  printf("Send: %d\n", num);
  return 0;
}
