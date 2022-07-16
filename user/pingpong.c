#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {

    int pipe1[2];
    int pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    int pid = fork();

    if (pid > 0) {
        close(pipe1[0]);
        close(pipe2[1]);

        write(pipe1[1] , "a" , 4);

        char buf[4];
        int parentPid = getpid();
        int n = read(pipe2[0] , buf , 4);
        if (n > 0) {
            printf("%d: received pong\n" , parentPid);
        }
        close(pipe1[1]);
        close(pipe2[0]);
    }else{
        close(pipe1[1]);
        close(pipe2[0]);
        char buf[4];
        int childPid = getpid();
        int m = read(pipe1[0] , buf , 4);
        if (m > 0) {
            printf("%d: received ping\n" , childPid);
            write(pipe2[1] , "a" , 4);
        }
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }
    wait(0);
    exit(0);
}