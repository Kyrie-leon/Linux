#include "udpClient.hpp"

void Usage(std::string proc)
{
  std::cout << proc << "Server_IP" << " server_port" << std::endl;
}

int main(int argc, char * argv[])
{
  if(argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  udpClient *uc = new udpClient(argv[1],atoi(argv[2]));
  uc->initClient();
  uc->start();

  delete uc;
  return 0;
}
