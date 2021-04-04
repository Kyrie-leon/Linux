#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define FIFO_FILE "./fifo"

int main()
{
  int fd = open(FIFO_FILE,O_WRONLY);
  if(fd >=0)
  {
    char buf[64];
    while(1)
    {
      printf("please enter your message #");
      fflush(stdout);
      ssize_t s = read(0,buf,sizeof(buf)-1);
      if(s > 0)
      {
        buf[s] = 0;
        write(fd,buf,s);
      }
    }
  }

  return 0;
}
