#include "udpServer.hpp"

void Usage(std::string proc)
{
  std::cout << "Usage:" << proc << " server_ip server_port"<< std::endl;
}

//./udpServer ip port
int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  udpServer *up = new udpServer(argv[1],atoi(argv[2]));
  up->initServer();
  up->start();

  delete up;
  return 0;
}
