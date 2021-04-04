#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include"comm.h"
#include<sys/shm.h>

int main()
{
  key_t k = ftok(PATHNAME,PROJ_ID);  
  printf("key:%p\n",k);
  int shmid = shmget(k,SIZE, 0);
  if(shmid < 0)
  {
    perror("shmget");
    return 1;
  }
  printf("shmid:%d\n", shmid);

  sleep(10);
  char * str = shmat(shmid,NULL,0);
  char c = 'a';
  for(;c<'z';c++)
  {
    str[c-'a'] = c;
    sleep(1);
  }
  shmdt(str);
  sleep(5);

  return 0;
}
