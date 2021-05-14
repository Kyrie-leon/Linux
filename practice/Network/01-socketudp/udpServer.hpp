#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

class udpServer
{
  private:
    std::string _ip;  //ip地址
    int _port; //端口号
    int _sock; //套接字文件描述符
  public:
    //构造函数
    udpServer(std::string ip = "127.0.0.1", int port = 8080)
      :_ip(ip)
      ,_port(port)
    {}
    //初始化服务器
    void initServer()
    {
      //1.创建套接字
      _sock = socket(AF_INET, SOCK_DGRAM, 0); 
      std::cout << "sock:"<< _sock << std::endl;
      //2.填重结构体协议，ip，_port
      struct sockaddr_in local;
      local.sin_family = AF_INET;
      local.sin_addr.s_addr = inet_addr(_ip.c_str());
      local.sin_port = htons(_port);
      //3.绑定端口,失败直接结束进程
      if(bind(_sock,(struct sockaddr*)&local,sizeof(local)) < 0)
      {
        std::cerr << "bind failed!" << std::endl;
        exit(1);

      }
    }
    //启动服务器
    void start()
    {
      //1.创建字符串接收数据
      std::cout << "---";
      char msg[64] = "\0";
      while(1)
      {
        //定义远端addr结构体用于接收ip地址等
        struct sockaddr_in end_point;
        socklen_t len = sizeof(end_point);
        ssize_t s = recvfrom(_sock, msg, sizeof(msg), 0, (struct sockaddr*)&end_point, &len);
        if(s > 0)
        {
          std::cout << "client#"<< msg << std::endl;
          std::string echo_string = msg;
          echo_string += "[server echo!]";
          sendto(_sock, echo_string.c_str(), echo_string.size(), 0, (struct sockaddr*)&end_point, len);
          
        }

      }
    }
    //析构函数
    ~udpServer()
    {
      close(_sock);
    }
};
