#include "types.h"
#include "stat.h"
#include "user.h"
#define RED  "\033[31m"
#define RESET   "\033[0m"


int main() {
    int i;
    int *ptr = (int*)sbrk(4096); // trying to allocate 4KB (one page) of memory but does not work because of the broken sbrk()
    for (i = 0; i < 20000; i++) {
        ptr[i] = i; // causes page fault because we are trying to access a memory that is not allocated to the process.
    }
    exit();
    return 0;
}

