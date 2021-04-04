#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void handler(int sig)
{
  printf("catch a sig:%d\n",sig);
}

int main(int argc, char * argv[])
{
  kill(atoi(argv[1]),)

  //signal(2,handler);
  //while(1)
  //{
 //   printf("i am runing\n");
 //   sleep(2);
 // }
  return 0;
}
