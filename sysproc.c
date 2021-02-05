#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_getParentID(void)
{
  return myproc()->parent->pid;
}

int sys_getChildren(void)
{
  // calling getChildren() with the current process id as input
  return getChildren(myproc()->pid);
}

int sys_getSyscallCounter(void)
{
  int number; // called syscall number (1-24)
  argint(0, &number);
  return myproc()->sysCall_count[number];
}

int sys_setPriority(void)
{
  int p;
  argint(0, &p);
  if (p > 6 || p < 1)
  {
    p = 5;
  }

  myproc()->priority = p;

  if (myproc()->priority == p)
    return 1;
  return -1;
}

int sys_changePolicy(void)
{
  int policy;
  argint(0, &policy);
  if (policy == 0 || policy == 1 || policy == 2 || policy == 3)
  {
    selectedScheduler = policy;
    if (selectedScheduler == 1) // RR
    {
      RR_active = 1; // to distinguish trap.c and proc.c
    }
    else
    {
      RR_active = 0;
    }
    return 1;
  }
  return -1;
}

int sys_waitWithTimings(void)
{
  struct timing *times;
  argptr(0, (void *)&times, sizeof(times));
  return waitWithTimings(times);
}


int sys_setQueue(void)
{
  int q;
  argint(0, &q);
  if (q > 4 || q < 1)
  {
    q = 1; // default queue
  }

  myproc()->queue = q;

  if (myproc()->queue == q)
    return 1;
  return -1;
}