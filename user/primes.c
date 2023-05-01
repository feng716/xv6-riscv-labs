#include "user/user.h"
int main() {
  // write data into the pipe
  int pip[2];
  pipe(pip);
  for (int i = 2; i < 35; i++) {
    write(pip[1], &i, 4);
  }
  int status=0;//---status identity whether it's main process---
  int temp, min_prime=0;
  // for each PIPE
  while (min_prime != 31) {
    read(pip[0], &min_prime, 4);
    fprintf(1, "prime:%d\n", min_prime);

    int topip[2];
    pipe(topip);
    close(pip[1]);
    while (read(pip[0], &temp, 4)) {
      if (temp % min_prime != 0) {
        write(topip[1], &temp, 4);
      }
    }
    close(topip[1]);
    close(pip[0]);

    pipe(pip);
    int pid = fork();
    if (pid == 0) {
      //status=1;
      while (read(topip[0], &temp, 4)) {
        write(pip[1], &temp, 4); // copy frome topip to pip;
      }
      
      close(topip[0]);
      
    } else {
      close(pip[0]);
      close(pip[1]);
      wait(&status);
      exit(0);
    }
  }
  exit(0);
}