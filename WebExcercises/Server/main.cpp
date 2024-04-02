//#include <stdafx.h>
#include <iostream>
#include <tchar.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <vector>

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	int wsaErr;
	WORD w_VersionRequested{ MAKEWORD(2, 2) };
	wsaErr = WSAStartup(w_VersionRequested, &wsaData);
	if (wsaErr != 0)
	{
		std::cout << "Owned by Skill Issue! The Winsock dll not found!" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "The Winsock dll found!" << std::endl;
		std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
	}

	SOCKET serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		std::cout << "Owned by Skill Issue! Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout << "socket() is fine..." << std::endl;
	}

	int port{ 55555 };
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		std::cout << "Owned by Skill Issue! bind() failed: " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else
	{
		std::cout << "bind() is fine..." << std::endl;
	}

	// second parameter is max number of clients that can be connected to specific socket
	if (listen(serverSocket, 12) == SOCKET_ERROR)
	{
		std::cout << "Owned by Skill Issue! listen(): Error listening on socket: " << WSAGetLastError() << std::endl;
	}
	else
	{
		std::cout << "listen(): is fine.. Waiting for connections form clients." << std::endl;
	}

	SOCKET acceptSocket;
	acceptSocket = accept(serverSocket, nullptr, nullptr);
	if (acceptSocket == INVALID_SOCKET)
	{
		std::cout << "Owned by Skill Issue! accept() failed: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}
	std::cout << "Accepted connection!" << std::endl;

	std::vector<char> buffer(4 * 1024);
	if (auto byteCount{ recv(acceptSocket, buffer.data(), buffer.size(), 0) }; byteCount > 0)
	{
		std::cout << "Message received: " << buffer.data() << std::endl;
	}
	else
	{
		std::cout << "Error: Only " << byteCount << " bytes received out off " << buffer.size() << " from your message." << std::endl;
		WSACleanup();
	}

	std::vector<char> confirmationBuffer(32);
	const std::string messageReceived{ "Message received!" };
	confirmationBuffer.assign(messageReceived.begin(), messageReceived.end());
	if (auto byteCount{ send(acceptSocket, confirmationBuffer.data(), confirmationBuffer.size(), 0) }; byteCount > 0)
	{
		std::cout << "Automated confirmation message send." << std::endl;
	}
	else
	{
		std::cout << "Error: Only " << byteCount << " bytes send out off " << buffer.size() << " from automated confirmation message." << std::endl;
		WSACleanup();
	}

	std::cin.get();
	WSACleanup();
	return 0;
}