#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int main(int argc, char *argv[]){

    
    if (argc==1) {
        fprintf(2,"You input too less param\n");
        exit(1);
    }
    else if (!atoi(argv[1])) {
        fprintf(2,"you need to input the right sleep time\n");
        exit(1);
    }
    else if (argc>2) {
        fprintf(2,"You input too many param\n");
        exit(1);
    }
    else {
        sleep(atoi(argv[1]));
    }
    exit(0);
}