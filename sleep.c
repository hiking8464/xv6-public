#include "types.h"
#include "stat.h"
#include "user.h"
#define RED  "\033[31m"
#define RESET   "\033[0m"
// #include "ctype.h"

int main(int argc, char *argv[]){
    int sleep_time;
    if (argc < 2){
        printf(2,RED "Error : No time specified\n" RESET);
        exit();
    }
    char *hiking = argv[1];
    while (*hiking){
        if ((*hiking > '9' || *hiking < '0') && (*hiking != '.')){
            printf(2, RED "Error : Invalid input\n" RESET);
            exit();
        }
        hiking++;
    }

    sleep_time = atoi(argv[1]);

    // if (sleep_time < 0){
    //     printf(2,RED "Error : Invalid time\n" RESET);
    // } 
    // else{
        sleep(sleep_time*100);
// }

    exit();

    }
    

      // if (argv[1][0] == '-'){
    //     printf(2,"Error : Invalid time\n");
    // }

    // else{
    //     sleep_time = atoi(argv[1]);
    //     sleep(sleep_time*100);
    // }

    // exit();
    // }


