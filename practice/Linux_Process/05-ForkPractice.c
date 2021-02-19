#include<stdio.h>
#include<unistd.h>

int main()
{
  
  fork();
  fork();
  fork();
  printf("调用fork打印两遍，父进程ID:%d , 进程ID:%d \n",getppid(), getpid());
  sleep(1);
  return 0;
}
