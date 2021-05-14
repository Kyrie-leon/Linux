#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

class udpClient
{
  private:
    std::string _ip;  //ip地址
    int _port; //端口号
    int _sock; //套接字文件描述符
  public:
    //构造函数
    udpClient(std::string ip = "127.0.0.1", int port = 8080)
      :_ip(ip)
      ,_port(port)
    {}
    //初始化
    void initClient()
    {
      //1.创建套接字
      _sock = socket(AF_INET, SOCK_DGRAM, 0); 
      std::cout << "sock:"<< _sock << std::endl;
     // //2.填重结构体协议，ip，_port
     // struct sockaddr_in peer;
     // peer.sin_family = AF_INET;
     // peer.sin_addr.s_addr = inet_addr(_ip.c_str());
     // peer.sin_port = htons(_port);
     // //3.绑定端口,失败直接结束进程
     // if(bind(_sock,(struct sockaddr*)&peer,sizeof(local)) < 0)
     //   std::cerr << "bind failed!" << std::endl;
     //   exit(1);
    }
    //启动
    void start()
    {
      std::string msg;
      struct sockaddr_in peer;
      peer.sin_family = AF_INET;
      peer.sin_addr.s_addr = inet_addr(_ip.c_str());
      peer.sin_port = htons(_port);

      while(1)
      {
        std::cout << "Please enter your msg:#";
        std::cin >> msg;
        if(msg == "quit")
          break;
        sendto(_sock, msg.c_str(), msg.size(), 0, (struct sockaddr*)&peer, sizeof(peer));

        char echo[128];
        ssize_t s = recvfrom(_sock, echo, sizeof(echo)-1, 0, nullptr, nullptr);
        if(s >0){
          echo[s] = 0;
          std::cout << "server# " << echo << std::endl;
       } 
      }
    }
    //析构函数
    ~udpClient()
    {
      close(_sock);
    }
};
