#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{

    if (fork() == 0)
    {
        printf(1, "This is process %d and the parent id is %d\n", getpid(), getParentID());
    }
    else
    {
        wait();

        if (fork() == 0)
        {
            printf(1, "This is process %d and the parent id is %d\n", getpid(), getParentID());
        }
        else
        {
            wait();
        }
    }
    exit();
}