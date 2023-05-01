#include "user/user.h"
int main() {
  // write data into the pipe
  int pip[2];
  pipe(pip);
  for (int i = 2; i < 35; i++) {
    write(pip[1], &i, 4);
  }

  int temp, min_prime=0;
  // for each PIPE
  while (min_prime != 31) {

    read(pip[0], &min_prime, 4);
    fprintf(1, "prime:%d", min_prime);

    int topip[2];
    pipe(topip);
    int b=read(pip[0], &temp, 4);
    while (b) {
      int b=read(pip[0], &temp, 4);
      fprintf(1,"while%d\n",b);
      if (temp % min_prime != 0) {
        write(topip[1], &temp, 4);
        fprintf(1,"check%d\n",temp);
      }
      
    }
    fprintf(1,"1done\n");
    int pid = fork();
    if (pid == 0) {
      while (read(topip[0], &temp, 4)) {
        write(pip[1], &temp, 4); // copy frome topip to pip;
      }
    } else {
      exit(0);
    }
  }
  exit(0);
}