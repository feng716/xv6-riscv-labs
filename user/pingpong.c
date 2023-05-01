#include "user/user.h"
int main(){
    int pipe_send[2];
    pipe(pipe_send);
    int pipe_rec[2];
    pipe(pipe_rec);
    int pid = fork();
    if (pid>0) {
        close(pipe_send[0]);
        close(pipe_rec[1]);
        write(pipe_send[1],"ping",5);
        //fprintf(1,"par:pingpong has been sent to %d \n",&pid);
        close(pipe_send[1]);
        int status;
        pid = wait(&status);
        //fprintf(1,"par:child %d has been done\n",&pid);
        char result[2];
        read(pipe_rec[0],result,5);
        fprintf(1,"%d: received %s\n",pipe_rec,result);
        exit(0);
    }
    else if (pid==0) {
        close(pipe_send[1]);
        close(pipe_rec[0]);
        char result[2];
        read(pipe_send[0],result,5);
        fprintf(1,"%d: received %s\n",pipe_send+1,result);
        write(pipe_rec[1],"pong",5);
        //fprintf(1,"c:pingpong has been sent to father \n",&pid);
        exit(0);
    }
    else {
        fprintf(1,"fork error");
        exit(1);
    }
    exit(0);
}