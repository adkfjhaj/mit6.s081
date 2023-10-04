#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

char* getFileName(char *path){
    char *p=path+strlen(path);
    for(;*p!='/';p--);
    p++;

    return p;
}


void find(char *path,char *name){
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512],*p;
    
    
    if((fd = open(path, O_RDONLY)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd,&st)<0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }
    

    switch(st.type){
        case T_FILE:
        //Get the final filename from path
        char* finalName=getFileName(path);
        if(finalName&&strcmp(finalName,name)==0){
            printf("%s\n",path);
        }
        close(fd);
        break;
        case T_DIR:
        memset(buf, 0, sizeof(buf));
        strcpy(buf,path);
        p=buf+strlen(buf);
        *p++='/';
        // int curPathLen=strlen(path);
        // memcpy(buf, path, curPathLen);
        // buf[curPathLen]='/';
        // p=buf+curPathLen+1;
        while(read(fd,&de,sizeof(de))==sizeof(de)){
            if(de.inum==0 || strcmp(de.name,".")==0||strcmp(de.name,"..")==0)continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            find(buf,name);
        }
        close(fd);
        break;
    }
    
}

int main(int argc, char *argv[]){
    find(argv[1],argv[2]);
    exit(0);
}