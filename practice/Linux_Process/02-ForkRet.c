#include<stdio.h>
#include<unistd.h>

int main()
{
  
  int ret =  fork();
  if(ret < 0)
  {
    printf("进程创建失败！\n");
  }
  else if(0 == ret)
  {
    printf("我是儿子(id:%d),fork返回值:%d\n",getpid(),ret);
  }
  else
  {
    printf("我是父亲(id:%d),fork返回值:%d\n", getpid(),ret);
  }
  sleep(1);
  return 0;
}
