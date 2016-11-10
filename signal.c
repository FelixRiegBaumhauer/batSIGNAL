#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

int when_to_fire=2;
/*
  when_to_fire is arbitary, it can be any number, it is the number of times that
  the pid is printed before we give SIGUSR1 a value
 */

//the specially made signal handler
static void sighandler(int signo){
  if(signo == SIGINT){//one case
    printf("Check test.txt for a message");
    char message[40] = "SIGINT was called"; 
    int fd = open("test.txt", O_WRONLY);
    write(fd, &message, strlen(message));
    close(fd);
    exit(0);
  }
  if(signo == SIGUSR1){//other case
    int p_pro;
    p_pro=getppid();
    printf("SIGUSR1 was invoked--Parent pid is: %d\n", p_pro);
  }
}

int main(){
  int count = 0;//so we can fire SIGUSR1 once at a specific round
  
  while( 1 > 0){
    int pid;
    pid = getpid();
    count++;
    printf("Current pid is: %d\n", pid);
    sleep(1);
    //Catchers
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    //sets SIGUSR1 to the current pid
    if(count==when_to_fire){
      kill(pid, SIGUSR1);
    }
  }

  return 0;
}
