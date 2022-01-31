#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid, ppid;
    pid = fork();
    if (pid == -1) {
        /* ошибка */
         printf ("ERROR: %d\n", pid);
    } else if (pid == 0) {
        /* ребенок */
         printf ("It's PID: %d\n", getppid());
    } else {
        /* родитель */
         printf ("It's PPID: %d\n", getpid());
    }
    return 0;
}
