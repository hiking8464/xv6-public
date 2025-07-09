#include "types.h"
#include "user.h"

int
main(void)
{
    int parent_pid = getpid(); // Get the parent process ID
    
    printf(1, "Parent process ID: %d\n", parent_pid);
    //char *params[3]={"uniq","README",0};
    char *params[4][5]={{"uniq","-u","README",0} , {"find" "/","-inum", "20",0} , {"cat","README",0},{"ls","-a",0}};

    // Create three child processes
    for (int i = 0; i < 4; i++) {
        sleep(5);
        int child_pid = fork();
          
        if (child_pid < 0) {
            printf(1, "Fork failed\n");
            exit();
        } else if (child_pid == 0) {
            // Child process
            
            sleep(10);
            int child_pid = getpid();
            if(i<3)
            set_sched_priority((i)%3);
            printf(1,"Running Child Process pid = %d\n",child_pid);
            exec(params[i][0],params[i]);
            
            // Do any child-specific tasks here
            
            exit();
        }
        /*else{
        wait();
        }*/
    }

    // Parent process
    // Do any parent-specific tasks here
    for (int i = 0; i < 4; i++) {
        wait(); // Wait for each child process to finish
    }
    exit();
}

