#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf ("UserID: %d\n", getuid());
    printf ("GroupID: %d\n\n", getgid());
    return 0;
}
