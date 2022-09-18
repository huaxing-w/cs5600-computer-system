#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
        }
    if (rc == 0){

        char * const argv[] = {"ls", NULL};
        char * const envp[] = {NULL};
        execvp("ls", argv);

        //execl("/bin/ls", "ls", NULL);
        //execlp("ls", "ls", NULL);
        //execle("/bin/ls", "ls", NULL, envp);
        //execv("/bin/ls", argv);
        //execvpe("ls", argv, envp); 
    }
    if (rc > 0){
        wait(NULL);
    }
    return 0;
}