#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv[]) {
  int p[2];
  pipe(p);

  int pid = fork();
  if(pid == 0){
    char buf[128];
    int n = read(p[0], buf, sizeof(buf));
    if(n>0) printf("%d: received %s\n", getpid(), buf);
    close(p[0]);

    write(p[1], "pong", 5);
    close(p[1]);

    exit(0);
  }else{
    write(p[1], "ping", 5);
    close(p[1]);

    char buf[128];
    int n = read(p[0], buf, sizeof(buf));
    if(n>0) printf("%d: received %s\n", getpid(), buf);
    close(p[0]);

    wait((int *)0);
  }

  return 0;
}
