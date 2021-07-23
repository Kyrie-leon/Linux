#pragma once
#include<iostream>
#include<string>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#define BACKLOG 5
using namespace std;

class HttpServer{
  private:
    int port;   //端口号
    int lsock;  
  public:
    //1.构造函数
    HttpServer(int _p):port(_p),lsock(-1)
    {}
    
    //2.初始化服务器
    void InitServer()
    {

      signal(SIGCHLD, SIG_IGN);
      //1.创建套接字、失败就退出
      lsock = socket(AF_INET, SOCK_STREAM, 0);
      if(lsock < 0)
      {
        cout << "socket err" <<endl;
        exit(2);
      }

      //2.填充结构体协议
      struct sockaddr_in local;
      bzero(&local, sizeof(local));
      local.sin_family = AF_INET;
      local.sin_port = htons(port);
      local.sin_addr.s_addr = INADDR_ANY;
      //3.绑定端口
      if(bind(lsock, (struct sockaddr*)&local, sizeof(local)) < 0)
      {
        cerr << "bind err " << endl;
        exit(3);
      }
      //4.监听套接字
      if(listen(lsock, BACKLOG) < 0)
      {
        exit(4);
      }
    }
    
    //回显http
    int EchoHttp(int sock)
    {
      //
      char request[2048];
      size_t s = recv(sock, request, sizeof(request), 0);  //bug
      if(s > 0)
      {
        //1.读取请求
        request[s] = 0;
        cout << request << endl;
        //2.响应请求
        //string response = "HTTP/1.0 200 OK\r\n";    //响应行
        string response = "HTTP/1.0 302 Found\r\n";
        //302 NOT FOUND\r\n
        response += "Content-type: text/html\r\n";  //响应报头
        response += "location:https://www.baidu.com/\r\n";
        response += "\r\n";                          //空行
        /*
        response += "\
        <!DOCTYPE html>\
        <html>\
        <head>\
        <title>WELCOME</title>\
        </head>\
        <body>\
        <h1>Hello</h1>\
        <p>World</p>\
        </body>\
        </html>";
        send(sock, response.c_str(), response.size(), 0);
        */
      }
      close(sock);
    }
    
    //3.启动服务器
    void start()
    {
      struct sockaddr_in peer;
      for(;;)
      {
        socklen_t len = sizeof(peer);
        int sock = accept(lsock, (struct sockaddr*)&peer, &len);
        if(sock < 0)
        {
          cerr << "accept err" << endl;
          continue;
        }

        cout << "get a new link..." << endl;
        //创建子进程
        if(fork() == 0)
        {
          close(lsock);
          EchoHttp(sock);
          exit(0);
        }
        else{
          close(sock);
        }
      }
    }
    
    //析构函数，关闭lsock
    ~HttpServer()
    {
      if(lsock != -1)
      {
        close(lsock);
      }
    }
};
