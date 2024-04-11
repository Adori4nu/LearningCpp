//#include <stdafx.h>
#include "ChatApp.hpp"
#include <chrono>
#include <iostream>
#include <tchar.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char* argv[])
{
	ChatApp ChatClient;

	if (auto result{ ChatClient.init() }; !result)
	{
		std::cout << "Owned by Skill Issue! Can't init ChatApp." << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Init Succesfull" << std::endl;
	}

	ChatClient.run();
	ChatClient.deinit();

#pragma region old_junk
	//SOCKET clientSocketFDOfServer = INVALID_SOCKET;
	//clientSocketFDOfServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//if (clientSocketFDOfServer == INVALID_SOCKET)
	//{
	//	std::cout << "Owned by Skill Issue! Error at socket(): " << WSAGetLastError() << std::endl;
	//	WSACleanup();
	//	return 0;
	//}
	//else
	//{
	//	std::cout << "socket() is fine..." << std::endl;
	//}

	////std::string ip = "93.184.216.34";
	//std::string ip = "127.0.0.1";
	//int port{ 55555 }; // 80
	//sockaddr_in clientService;
	//clientService.sin_family = AF_INET;
	////inet_pton(AF_INET, ip.c_str(), &clientService.sin_addr.s_addr);
	//InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	//clientService.sin_port = htons(port);
	//if (connect(clientSocketFDOfServer, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	//{
	//	std::cout << "Owned by Skill Issue! connect() failed: " << WSAGetLastError() << std::endl;
	//	WSACleanup();
	//	return 0;
	//}
	//else
	//{
	//	std::cout << "Client: connect() is fine..." << std::endl;
	//	std::cout << "Client: Can start sending and receiving data..." << std::endl;
	//}
	

	/*const std::string httpGET
	{
		"GET /index.html HTTP/1.1\r\n"
		"Host: example.com\r\n"
		"Connection: close\r\n\r\n"
	};
	buffer.assign(httpGET.begin(), httpGET.end());*/

	/*if (auto byteCount{ send(clientSocketFDOfServer, buffer.data(), buffer.size(), 0) }; byteCount > 0)
	{
		std::cout << "\n\nMessage sent: " << std::endl << buffer.data() << std::endl;
	}
	else
	{
		std::cout << "Owned by Skill Issue! only " << byteCount << " bytes send out off " << buffer.size() << " from your message." << std::endl;
		WSACleanup();
	}*/

	/*using namespace std::chrono_literals;
	
	int byteCount{};
	std::cout << "Server Response: " << std::endl;
	std::this_thread::sleep_for(100ms);
	while ((byteCount = recv(clientSocketFDOfServer, buffer.data(), buffer.size(), 0)) > 0)
	{
		std::cout.write(buffer.data(), byteCount);
		std::this_thread::sleep_for(10ms);
	}

	if (byteCount < 0)
	{
		std::cout << "Error receiving data." << std::endl;
	}
	else
	{
		std::cout << "Connection closed by the server." << std::endl;
	}*/

	//if (auto byteCount{ recv(clientSocketFDOfServer, buffer.data(), buffer.size(), 0) }; byteCount > 0)
	//{
	//	std::cout << "Server Response: " << buffer.data() << std::endl;
	//}
	//else
	//{
	//	std::cout << "Owned by Skill Issue! only " << byteCount << " bytes received out off " << buffer.size() << " from your message." << std::endl;
	//	WSACleanup();
	//}
#pragma endregion
	
	return 0;
}