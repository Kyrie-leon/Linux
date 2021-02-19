#include<stdio.h>
#include<unistd.h>

int main()
{
  printf("子进程pid：%d\n",getpid());
  printf("父进程ppid：%d\n",getppid());

  return 0;
}
