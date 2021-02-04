#include "types.h"
#include "user.h"

int main(int argc, char const *argv[])
{
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    int n3 = atoi(argv[3]);

    // syscall #11 repeated 6 times
    getpid();
    getpid();
    getpid();
    getpid();
    getpid();
    getpid();

    // syscall #22 repeated 9 times
    getParentID();
    getParentID();
    getParentID();
    getParentID();
    getParentID();
    getParentID();
    getParentID();
    getParentID();
    getParentID();

    // syscall #23 repeated 5 times
    getChildren();
    getChildren();
    getChildren();
    getChildren();
    getChildren();

    printf(1, "System call #%d repeated %d times.\n", n1, getSyscallCounter(n1));
    printf(1, "System call #%d repeated %d times.\n", n2, getSyscallCounter(n2));
    printf(1, "System call #%d repeated %d times.\n", n3, getSyscallCounter(n3));

    exit();
}