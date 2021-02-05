#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{

    int p1 = fork();
    int p2 = fork();
    int p3 = fork();

    if (p1 > 0)
        sleep(40);
    if (p2 > 0)
        sleep(30);
    if (p3 > 0)
        sleep(20);

    // Extracting the children
    int tmp = getChildren();
    if (tmp == 0)
    {
        printf(1, "This is process %d and it has no children!\n", getpid());
    }
    else
    {
        printf(1, "This is process %d and its children are : ", getpid());

        while (tmp != 0)
        {
            printf(1, "[%d] ", tmp % 100);
            tmp = tmp / 100;
        }
        printf(1, "\n");
    }

    wait();
    wait();
    wait();

    exit();
}