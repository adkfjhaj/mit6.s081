#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

// void getArguments(char* buf, char* args[],int len){
//     int i=0;
//     char* tmp;
//     char* p=buf;
//     while(*p!='\0'){
//         while(*p!='\n'){
//             p++;
//         }
//         tmp=malloc(sizeof(char)*(p-buf+1));

//         memcpy(tmp,buf,p-buf);
//         // tmp[p-buf+1]='\n';
//         tmp[p-buf]='\0';
//         printf("%s\n",tmp);
//         args[i++]=tmp;
//         memset(buf,0,p-buf);
//         p++;
//     }
// }
// void xargs(char* execName,char* oldarg,char* args[]){
//     int i=0;
//     char* buf[MAXARG];
//     while(args[i]){
//         memset(buf,0,sizeof(buf));
//         buf[0]=oldarg;
//         buf[1]=args[i];
//         if(fork()==0){
//             if(exec(execName,buf)<0){
//                 fprintf(2,"exec: error\n");
//             }
//             exit(0);
//         }
//         wait(0);
//         i++;
//     }
// }

int main(int argc, char *argv[]){
    char buf[512];
    char* args[MAXARG];
    char* p;
    int n;
    char c;
    
    for(int i=1;i<argc;i++){
        args[i-1]=argv[i];
    }

    while(1){
        p=buf;
        while((n=read(0,&c,1))&&c!='\n'){
            *p++=c;
        }
        *p='\0';
        if(n==0){
            close(0);
            break;
        }
        args[argc-1]=buf;
        if(fork()==0){
            if(exec(argv[1],args)<0){
                fprintf(2,"exec: error\n");
            }
            exit(0);
        }
        wait(0);
        
        memset(buf,0,sizeof(buf));
    }
    exit(0);
}