#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        printf("error\n");
        return 1;
    } else if (pid == 0) {
        printf("child work:\n");
        execl("/bin/ls", "/bin/ls", ".", NULL);
    } else {
        printf("child %d work", pid);
    }
    
    return 0;
}
