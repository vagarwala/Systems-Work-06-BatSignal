#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

static void sig_handle (int sig);

int main(){
  signal(SIGINT, sig_handle);
  signal(SIGUSR1, sig_handle);
  while (1){
    printf("pid: %d. \n", getpid());
    sleep(1);
  }
}

void sig_handle(int signo){
  if (signo == SIGINT){
    printf("signal caught: %d.  exiting.\n", signo);
    int d = open("log.txt", O_CREAT | O_WRONLY | O_APPEND, 0666);
    write(d, "SIGINT\n", 8);
    close(d);
    exit(1);
  } else if (signo == SIGUSR1) {
    printf("pid of parent process: %d \n", getppid());
  }
}