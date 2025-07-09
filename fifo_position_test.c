#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    
    int pid = 999;
    if(argc>2)
    {
    printf(1,"Too Many Arguments");
    exit();
    }
    if(argc<2){
    pid=getpid(); 
    }
    else{
    pid=atoi(argv[1]);
    }
    int position = fifo_position(pid);
    if (position == -1)
        printf(1, "Process with PID %d does not exist or is not in the scheduling queue.\n", pid);
    else
        printf(1, "Position of process with PID %d in the FIFO queue: %d\n", pid, position);

    exit();
}

