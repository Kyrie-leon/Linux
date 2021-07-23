#include"httpServer.hpp"

//使用方法./httpServer port
static void Usage(string proc)
{
  cout << "Usage:\n\t";
  cout << proc << ":port" << endl;
}

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    Usage(argv[0]);
    exit(1);
  }
  HttpServer *hp = new HttpServer(atoi(argv[1]));
  hp->InitServer();
  hp->start();

  return 0;
}
