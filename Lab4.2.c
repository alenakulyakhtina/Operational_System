#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        printf("error occurred\n");
        return 1;
    } else if (pid == 0) {
        printf("child working:\n");
        execl("/bin/ls", "/bin/ls", ".", NULL);
    } else {
        printf("child %d working", pid);
    }
    
    return 0;
}
