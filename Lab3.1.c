#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // PID - запущенный процесс
    // PPID - номер процесса, от которого он запущен.
    printf ("User PID: %d\n", getpid());
    printf ("User PPID: %d\n\n", getppid());
    return 0;
}
