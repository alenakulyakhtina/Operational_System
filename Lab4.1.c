#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[], char *envp[]) {
    printf("Arguments:\n");
    printf("argc: %d\n", argc);
  
    printf("argv[]:\n");
    char ** list;
    for (list = argv; *list; ++list )
        printf("\t\t%s\n", *list);
    printf("\n");

    printf("envp[]:\n");
    for ( list = envp; *list; ++list )
        printf("\t\t%s\n", *list);
    printf("\n");
  
    return 0;
}
