#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

void tree(char* path,int);
char* filter(char* path);

//macro
#define DIRLENG 14
int main(int argc,char* argv[]){
    if(strlen(argv[1])>DIRLENG){
        printf("Too long");
        exit(0);
    }
    char buff[DIRLENG];
    strcpy(buff,argv[1]);
    tree(buff,-1);
    //tree("/");
    exit(0);
}
void tree(char* path,int tabn){
    int fd;
    struct stat st;
    struct dirent dr;
    fd=open(path,0);
    fstat(fd,&st);
    //printf("%d\n",(st.type==T_DIR));
    switch (st.type) {
        case T_FILE:
            for (int i=0; i<tabn; i++) {
                printf("    ");
            }
            printf("%d",st.type==T_DIR);
            printf("|%s\n",filter(path));
            break;
        case T_DIR:
            while (read(fd, &dr, sizeof(dr)) == sizeof(dr)) {
                if(dr.inum==0)
                    continue;
                if (!(strcmp(dr.name, ".") == 0 || strcmp(dr.name, "..") == 0)) {
                    char temp[DIRLENG];
                    strcpy(temp, path);
                    strcpy(temp + strlen(path), dr.name);
                    //printf("%s|", temp);
                    tree(temp,tabn+1);
                }
            }
            break;
    }
}
char* filter(char* path){
    //char buf[DIRLENG+1];
    char* p;
    for(p=path+strlen(path);p>=path&&*p!='/';p--);
    p++;
    return p;
}