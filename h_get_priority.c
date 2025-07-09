#include "types.h"
#include "stat.h"
#include "user.h"
#define RED  "\033[31m"
#define RESET   "\033[0m"

int main(int argc, char *argv[]){

    int pid;
    int priority;
    if (argc < 2){
        printf(2,RED "Error: No pid specified\n" RESET);
        exit();
    }
    pid = atoi(argv[1]);
    priority = get_sched_priority(pid);
    printf(2,"priority : %d\n", priority);
    exit();
}

