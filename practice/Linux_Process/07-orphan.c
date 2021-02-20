#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
  pid_t ret = fork();
  if(ret < 0)
  {
    printf("创建进程失败！\n");
  }
  else if(ret > 0)
  {
    int count = 0;
    while(count++ < 5)
    {
      printf("我是父进程(id:%d)\n",getpid());
      sleep(2);
    }
    exit(0);
  }
  else
  {
    while(1)
    {
      printf("我是子进程(id:%d)\n",getpid());
      sleep(1);
    }
  }
  sleep(1);
  return 0;
}
