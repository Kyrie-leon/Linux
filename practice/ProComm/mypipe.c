#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

//char buf[1024]全局变量不能进行进程间通信，写时拷贝

int main()
{
  int pipefd[2] = {0};
  pipe(pipefd);
  printf("%d,%d\n",pipefd[0],pipefd[1]);
  pid_t id = fork();
  if(id == 0)
  {
    //child write
    close(pipefd[0]);
    const char *msg = "i am child...!\n";
    int count = 0;
    while(1)
    {
      write(pipefd[1],msg,strlen(msg));  
      //1.父进程会等待子进程的写入，没有数据时父进程会阻塞等待
      //sleep(5);
      printf("CHILD:%d\n",count++);
     // if(count == 5)
     // {
      //  close(pipefd[1]);
      //  break;
     // }
    }
    exit(2);
  }
  else{
    //father read
    close(pipefd[1]);
    char buffer[64];
    int count = 0;
    while(1)
    {
      //读取到的数据和期望读取到数据不一定相等
      ssize_t s = read(pipefd[0],buffer,sizeof(buffer)-1);
      if(s>0)
      {
        buffer[s] = 0;
        printf("father get message:%s\n",buffer);
        sleep(1);
      }
      if(count++ == 3)
      {
        close(pipefd[0]);
        break;
      }
      //printf("father exit return :%d\n",s);
    }
    int status = 0;
    waitpid(id, &status,0);
    printf("child exit get a sig, sig number:%d\n",status&0x7f);
  }
  return 0;
}
