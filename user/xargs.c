#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#define   MSGSIZE 16

int main(int argc, char *argv[]) {

    sleep(10);

    char buf[MSGSIZE];
    read(0 , buf , MSGSIZE);
    
    char *xargv[MSGSIZE];
    int xargc = 0;

    //自己的
    for (int i = 1 ; i < argc ; i++) {
        xargv[xargc] = argv[i];
        xargc++;
    }

    char *p = buf;

    for (int i = 0 ; i < MSGSIZE ; i++) {
        if (buf[i] == '\n') {
            int pid = fork();
            if (pid > 0) {  
                p = &buf[i+1];
                wait(0);
            }else{
                buf[i] = 0;
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0;
                xargc++;
                exec(xargv[0] , xargv);
                exit(0);
            }
        }
    }

   // wait(0);
    exit(0);
}