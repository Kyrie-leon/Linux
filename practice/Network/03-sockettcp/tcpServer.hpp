#ifndef __TCP_SERVER_H
#define __TCP_SERVER_H

#include<iostream>
#include<string>
#include<unistd.h>
#include<cstring>
#include<cstdlib>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define BACKLOG 5
class tcpServer{
  private:
    int port;   //端口号
    int lsock;  //监听套接字
  public:
    //构造函数
    tcpServer(int _port)
      :port(_port),lsock(-1)
  {}
    //初始化服务器
    void initServer()
    {
      //1.创建套接字
      lsock = socket(AF_INET,SOCK_STREAM,0);
      if(lsock < 0)
      {
        std::cerr << "lsocker error" << std::endl;
        exit(2);
      }
      //填充结构体协议
      struct sockaddr_in local;
      local.sin_family = AF_INET;
      local.sin_port = htons(port);
      local.sin_addr.s_addr = htonl(INADDR_ANY);
      //2.绑定 
      if(bind(lsock, (struct sockaddr*)&local, sizeof(local)) < 0)
      {
        std::cerr << "bind error" << std::endl;
        exit(3);
      }
      //3.监听(允许在任何时刻有客户端来连接服务器)
      //backlog（底层链接队列的长度），例如海底捞排队的长度，全连接队列 
      if(listen(lsock,BACKLOG) < 0)
      {
        std::cerr << "bind error" << std::endl;
        exit(4);
      }
      
    }
    //开始服务
    void service(int sock)
    {
      //buf用来接收消息
      char buf[1024];
      while(true)
      {
        //read or write来读写信息
        //注意这里s的三个取值
        //s>0表示收到信息，s==0表示客户端退出，如果不写这个条件或造成服务器一直阻塞在接收或发送的状态，不能再接收客户端信息
       ssize_t s = recv(sock,buf,sizeof(buf)-1,0);
       if(s > 0) 
       {
          buf[s] = 0;
          std::cout << "clinet#" << buf << std::endl;

          send(sock, buf, strlen(buf), 0);
       }
       else if(s == 0)
       {
          std::cout << "Clinet quit..." << std::endl;
          close(sock);  //不退出造成描述符越来越少，默认32
          break;
       }
       else{
         std::cout << "recv client data error" <<std::endl;
         break;
       }

      }
    }
    //启动服务器
    void start()
    {
      //定义远端结构体便于获取ip端口等信息
      sockaddr_in endpoint;
      while(true)
      {
        socklen_t len = sizeof(endpoint);
        //4.接收请求，注意lsock和sock的区别，后面主要为sock服务，lsock只是不断接收客户端
        int sock = accept(lsock, (struct sockaddr*)&endpoint, &len);
        if(sock < 0)
        {
          std::cerr << "accept error" << std::endl;
          continue;
        }
        //获取客户端ip和port,inet_ntoa将ip转为点分十进制的字符
        std::string cli_info = inet_ntoa(endpoint.sin_addr);
        cli_info += ":";
        //to_string同样是将16为短整型的port转为字符串
        cli_info += std::to_string(ntohs(endpoint.sin_port));

        std::cout << "get a new link..."<< cli_info << std::endl;
        service(sock);
      }
    }

    ~tcpServer()
    {
      close(lsock);
    }
};

#endif
