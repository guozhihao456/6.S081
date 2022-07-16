#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void process(int read_right[2]) {

    int first;

    read(read_right[0] , &first , 4);

    if (first == -1) {
        exit(0);
    }

    printf("prime %d\n" , first);

    int output[2];
    pipe(output);
    
    //fork的位置
    int pid = fork();

    if (pid > 0) {
        close(output[0]);
        int buf;
        while (read(read_right[0] , &buf , 4) != 0 && buf != -1) {
         
            if (buf % first != 0) {
                write(output[1] , &buf , 4);
            }
        }
        int end = -1;
        write(output[1] , &end , 4);
        close(output[1]);
        close(read_right[0]);
        wait(0);
    }else{
        close(output[1]);
        process(output);
        close(output[0]);
        wait(0);
    }
}


int main() {
    
    int fd[2];
    pipe(fd);

    int pid = fork();

    if (pid > 0) {
        close(fd[0]);

        for (int i = 2 ; i <= 35 ; i++) {
            write(fd[1] , &i , 4 );
        }

        int end = -1;
        write(fd[1] , &end , 4);
        close(fd[1]);
        wait(0);
    }else{
        close(fd[1]);
        process(fd);
        close(fd[0]);
        wait(0);
    }

    exit(0);
}