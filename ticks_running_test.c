#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid=9999;
  if(argc>2){
    printf(1,"Too Many Arguments");
    exit();
  }
  if(argc<2)
  {
     pid = getpid();
  }
  else{
    pid=atoi(argv[1]);
  }
    int ticks = ticks_running(pid); 
    printf(1, "Ticks running for process %d: %d\n", pid, ticks);

    /*int non_existent_pid = 9999; 
    ticks = ticks_running(non_existent_pid);
    if (ticks == -1)
        printf(1, "Process with PID %d does not exist\n", non_existent_pid);
    else
        printf(1, "Ticks running for process %d: %d\n", non_existent_pid, ticks);

    // Test with a process ID that exists but hasn't been scheduled yet
    int new_process_pid = fork();
    sleep(10);
    if (new_process_pid == 0) {
        // Child process
        
        exit();
    } else if (new_process_pid > 0) {
        
        ticks = ticks_running(new_process_pid);
        printf(1, "Ticks running for process %d: %d\n", new_process_pid, ticks);
        wait();
    }*/

    exit();
}

