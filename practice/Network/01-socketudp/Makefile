.PHONY:all
all:udpClient udpServer
udpClient:udpClient.cc
	g++ -o $@ $^ -std=c++11
udpServer:udpServer.cc
	g++ -o $@ $^
.PHNOY:clean
clean:
	rm -f udpClient udpServer
