#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        /* ошибка */
        printf("ERROR\n");
        return 1;
    } else if (pid == 0) {
        /* ребенок */
        printf("Child work:\n");
        execl("/bin/ls", "/bin/ls", ".", NULL);
    } else {
        /* родитель */
        printf("Child %d work", pid);
    }
    
    return 0;
}
