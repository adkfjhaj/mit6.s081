#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int listen){
    int receivedNum;
    int myNum=1;
    int pipes[2];
    pipe(pipes);


    while (read(listen, &receivedNum, 4))
    {
        if(receivedNum==0)break;
        if(myNum==1){
            myNum=receivedNum;
            printf("prime %d\n",myNum);
        }else{
            if(receivedNum%myNum!=0){
                write(pipes[1], &receivedNum, 4);
            }
        }
    }

    close(listen);
    close(pipes[1]);
    if(myNum>1){
        if(fork()==0){
            prime(pipes[0]);
            exit(0);
        }
    }
    // close(pipes[0]);
    wait(0);
    close(pipes[0]);
}


int main(int argc, char *argv[]){
    if(argc!=1){
        fprintf(2, "Error: must 0 argument\n");
        exit(1);
    }
    int p[2];
    pipe(p);

    for(int i=2;i<=35;i++){
        write(p[1], &i, 4);
    }
    close(p[1]);
    prime(p[0]);
    close(p[0]);
    exit(0);
}


    
