#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf ("User PID: %d\n", getpid());
    printf ("User PPID: %d\n\n", getppid());
    return 0;
}
