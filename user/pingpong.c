#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc != 1){
        fprintf(2, "Error:no argument for pingpong\n");
        exit(1);
    }
    char b[10];
    int pParent[2], pChild[2];
    pipe(pChild);
    pipe(pParent);
    // p[0]-->read p[1]-->write
    
    if(fork()==0){
        close(pParent[1]);
        close(pChild[0]);
        read(pParent[0],b,1);
        printf("%d: received ping\n",getpid());
        write(pChild[1],"a",1);
        exit(0);
    }else{
        close(pParent[0]);
        close(pChild[1]);
        write(pParent[1],"a",1);
        read(pChild[0],b,1);
        printf("%d: received pong\n",getpid());
        exit(0);
    }

    //!!!!!error!!!! cause,pipe is half-duplex
    // int p[2];
    // pipe(p);

    // if(fork()==0){
    //     read(p[0],b,1);
    //     printf("%d: received ping\n",getpid());
    //     write(p[1],"a",1);
    //     exit(0);
    // }else{
    //     write(p[1],"a",1);
    //     wait(0);
    //     read(p[0],b,1);
    //     printf("%d: received pong\n",getpid());
    //     exit(0);
    // }
    
}