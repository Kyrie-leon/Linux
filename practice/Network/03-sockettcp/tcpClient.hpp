#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include<iostream>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<cstring>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

class tcpClient{
  private:
    std::string svr_ip; //服务器ip
    int svr_port; //服务器端口号
    int sock; //sock文件描述符
  public:
    //构造函数
    tcpClient(std::string _ip="127.0.0.1",int _port = 9999)
      :svr_ip(_ip),svr_port(_port)
    {}
    //初始化
    void initClient()
    {
      //1.创建套接字
      sock = socket(AF_INET, SOCK_STREAM, 0);
      if(sock < 0)
      {
        std::cerr << "sock error" << std::endl;
        exit(2);
      }
      //2.客户端不需要绑定，因为应用较多，如果固定绑定了某一端口造成别的应用无法使用，交给系统自动绑定即可
      struct sockaddr_in svr;
      svr.sin_family = AF_INET;
      svr.sin_port = htons(svr_port);
      svr.sin_addr.s_addr = inet_addr(svr_ip.c_str());
      if(connect(sock,(struct sockaddr*)&svr,sizeof(svr)) != 0)
      {
        std::cerr << "connect error" << std::endl;
      }

    }
    void start()
    {
      char msg[64];
      while(true)
      {
        std::cout << "Please Input Msg#" << std::endl;
        fflush(stdout);
        size_t s = read(0,msg,sizeof(msg)-1);
        if(s > 0)
        {
          //注意这里的细节
          //read会把键盘上的回车读入，因此少读一个字节
          msg[s-1] = 0;
          send(sock,msg,strlen(msg),0);
          size_t ss = recv(sock, msg, sizeof(msg)-1,0);
          if(ss > 0)
          {
            msg[ss] = 0;
            std::cout << "server echo #" << msg << std::endl;
          }

        }
      }
    }
    ~tcpClient()
    {
      close(sock);
    }

};


#endif
