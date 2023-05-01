#include "user/user.h"
int main(){
    int d[2];
    pipe(d);
    int t=3;
    write(d[1],&t,4);
    read(d[0],&t,4);
    close(d[1]);
    read(d[0],&t,4);
    exit(0);
}