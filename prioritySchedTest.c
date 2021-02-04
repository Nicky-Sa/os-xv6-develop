#include "types.h"
#include "user.h"

struct timing
{
    int creationTime;
    int terminationTime;
    int sleepingTime;
    int readyTime;
    int runningTime;
};

int main(void)
{
    changePolicy(2); // 2 stands for priority sched

    int i = 0;
    int j = 0;
    int k = 0;

    struct timing times[30];
    int pids[30];
    for (j = 0; j < 30; j++)
    {
        if (fork() == 0)
        {
            if (0 <= j && j <= 4)
                setPriority(6);
            else if (5 <= j && j <= 9)
                setPriority(5);
            else if (10 <= j && j <= 14)
                setPriority(4);
            else if (15 <= j && j <= 19)
                setPriority(3);
            else if (20 <= j && j <= 24)
                setPriority(2);
            else if (25 <= j && j <= 29)
                setPriority(1);

            for (i = 0; i < 250; i++)
                printf(1, "[%d]:[%d] \n", j, i);
            exit();
        }
    }

    for (k = 0; k < 30; k++)
        pids[k] = waitWithTimings(&times[k]);

    int sumTurnaroundTime = 0;
    int sumCBT = 0;
    int sumWaitingTime = 0;

    // sorting
    struct timing tmp;
    int priority_min_index;
    int pid_min;
    int pid_tmp;
    for (i = 0; i < 30; i++)
    {
        // find minimum
        pid_min = 100000;
        priority_min_index = -1;
        for (j = i; j < 30; j++)
        {
            if (pids[j] < pid_min)
            {
                pid_min = pids[j];
                priority_min_index = j;
            }
        }

        // swapping
        tmp = times[priority_min_index];
        times[priority_min_index] = times[i];
        times[i] = tmp;

        pid_tmp = pids[priority_min_index];
        pids[priority_min_index] = pids[i];
        pids[i] = pid_tmp;
    }

    int sumTurnaroundTime6 = 0, sumTurnaroundTime5 = 0, sumTurnaroundTime4 = 0, sumTurnaroundTime3 = 0, sumTurnaroundTime2 = 0, sumTurnaroundTime1 = 0;
    int sumCBT6 = 0, sumCBT5 = 0, sumCBT4 = 0, sumCBT3 = 0, sumCBT2 = 0, sumCBT1 = 0;
    int sumWaitingTime6 = 0, sumWaitingTime5 = 0, sumWaitingTime4 = 0, sumWaitingTime3 = 0, sumWaitingTime2 = 0, sumWaitingTime1 = 0;

    for (k = 0; k < 30; k++)
    {
        if (0 <= k && k <= 4)
        {
            sumTurnaroundTime6 += (times[k].terminationTime - times[k].creationTime);
            sumCBT6 += times[k].runningTime;
            sumWaitingTime6 += times[k].readyTime;
        }
        else if (5 <= k && k <= 9)
        {
            sumTurnaroundTime5 += (times[k].terminationTime - times[k].creationTime);
            sumCBT5 += times[k].runningTime;
            sumWaitingTime5 += times[k].readyTime;
        }
        else if (10 <= k && k <= 14)
        {
            sumTurnaroundTime4 += (times[k].terminationTime - times[k].creationTime);
            sumCBT4 += times[k].runningTime;
            sumWaitingTime4 += times[k].readyTime;
        }
        else if (15 <= k && k <= 19)
        {
            sumTurnaroundTime3 += (times[k].terminationTime - times[k].creationTime);
            sumCBT3 += times[k].runningTime;
            sumWaitingTime3 += times[k].readyTime;
        }
        else if (20 <= k && k <= 24)
        {
            sumTurnaroundTime2 += (times[k].terminationTime - times[k].creationTime);
            sumCBT2 += times[k].runningTime;
            sumWaitingTime2 += times[k].readyTime;
        }
        else if (25 <= k && k <= 29)
        {
            sumTurnaroundTime1 += (times[k].terminationTime - times[k].creationTime);
            sumCBT1 += times[k].runningTime;
            sumWaitingTime1 += times[k].readyTime;
        }

        sumTurnaroundTime += (times[k].terminationTime - times[k].creationTime);
        sumCBT += times[k].runningTime;
        sumWaitingTime += times[k].readyTime;

        printf(1, "Child number : %d \n", (k + 1));
        printf(1, "Turnaround time : %d  \n", (times[k].terminationTime - times[k].creationTime));
        printf(1, "CBT : %d  \n", times[k].runningTime);
        printf(1, "Waiting time : %d  \n", times[k].readyTime);
        printf(1, "\n");
    }

    // calculating parameters
    int childNumber = 30;
    int avgTurnaroundTime = sumTurnaroundTime / childNumber;
    int avgCBT = sumCBT / childNumber;
    int avgWaitingTime = sumWaitingTime / childNumber;

    int childPerClass = 5;

    int avgTurnaroundTime6 = sumTurnaroundTime6 / childPerClass;
    int avgCBT6 = sumCBT6 / childPerClass;
    int avgWaitingTime6 = sumWaitingTime6 / childPerClass;

    int avgTurnaroundTime5 = sumTurnaroundTime5 / childPerClass;
    int avgCBT5 = sumCBT5 / childPerClass;
    int avgWaitingTime5 = sumWaitingTime5 / childPerClass;

    int avgTurnaroundTime4 = sumTurnaroundTime4 / childPerClass;
    int avgCBT4 = sumCBT4 / childPerClass;
    int avgWaitingTime4 = sumWaitingTime4 / childPerClass;

    int avgTurnaroundTime3 = sumTurnaroundTime3 / childPerClass;
    int avgCBT3 = sumCBT3 / childPerClass;
    int avgWaitingTime3 = sumWaitingTime3 / childPerClass;

    int avgTurnaroundTime2 = sumTurnaroundTime2 / childPerClass;
    int avgCBT2 = sumCBT2 / childPerClass;
    int avgWaitingTime2 = sumWaitingTime2 / childPerClass;

    int avgTurnaroundTime1 = sumTurnaroundTime1 / childPerClass;
    int avgCBT1 = sumCBT1 / childPerClass;
    int avgWaitingTime1 = sumWaitingTime1 / childPerClass;

    printf(1, "\nPriority 6 : \n");
    printf(1, "Average Turnaround time : %d  \n", avgTurnaroundTime6);
    printf(1, "Average CBT : %d  \n", avgCBT6);
    printf(1, "Average Waiting time : %d  \n", avgWaitingTime6);

    printf(1, "\nPriority 5 : \n");
    printf(1, "Average Turnaround time : %d  \n", avgTurnaroundTime5);
    printf(1, "Average CBT : %d  \n", avgCBT5);
    printf(1, "Average Waiting time : %d  \n", avgWaitingTime5);

    printf(1, "\nPriority 4 : \n");
    printf(1, "Average Turnaround time : %d  \n", avgTurnaroundTime4);
    printf(1, "Average CBT : %d  \n", avgCBT4);
    printf(1, "Average Waiting time : %d  \n", avgWaitingTime4);

    printf(1, "\nPriority 3 : \n");
    printf(1, "Average Turnaround time : %d  \n", avgTurnaroundTime3);
    printf(1, "Average CBT : %d  \n", avgCBT3);
    printf(1, "Average Waiting time : %d  \n", avgWaitingTime3);

    printf(1, "\nPriority 2 : \n");
    printf(1, "Average Turnaround time : %d  \n", avgTurnaroundTime2);
    printf(1, "Average CBT : %d  \n", avgCBT2);
    printf(1, "Average Waiting time : %d  \n", avgWaitingTime2);

    printf(1, "\nPriority 1 : \n");
    printf(1, "Average Turnaround time : %d  \n", avgTurnaroundTime1);
    printf(1, "Average CBT : %d  \n", avgCBT1);
    printf(1, "Average Waiting time : %d  \n", avgWaitingTime1);

    printf(1, "\nAll Processes : \n");
    printf(1, "Average Turnaround time : %d  \n", avgTurnaroundTime);
    printf(1, "Average CBT : %d  \n", avgCBT);
    printf(1, "Average Waiting time : %d  \n", avgWaitingTime);

    exit();
}
