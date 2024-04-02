#pragma once
#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <winsock2.h>
#include <WS2tcpip.h>

enum AppType : int
{
	SERVER,
	SERVER_HEADLESS,
	CLIENT
}; //1:08:07

struct AcceptedSocket
{
	SOCKET acceptedSocketFD{ INVALID_SOCKET };
	sockaddr address;
	int error;
	bool acceptedSuccessfully;
};

class ChatApp
{
	SOCKET m_socketFD{ INVALID_SOCKET };
	SOCKET m_acceptClientSocketFD{ INVALID_SOCKET };
	sockaddr_in m_addressForASocket;
	AppType m_appMode;
	std::vector<char> m_messageBuffer;
	std::vector<char> m_reciveBuffer;
	std::vector<char> m_responseBuffer;
	static const std::string m_exit;
	std::function<int()> m_run;
	AcceptedSocket& m_acceptIncomingConnection(SOCKET serverSocketFD);
	int m_startAcceptingIncomingConnection(SOCKET serverSocketFD);
	//bool m_acceptIncomingConnectionAndPrintRecivedData(SOCKET serverSocketFD);
	bool m_receiveAndPrintDataThread(AcceptedSocket& clientSocketData);
public:
	ChatApp() = default;
	~ChatApp()
	{
	}

	bool init();
	bool deinit();
	int sendData();
	bool receiveData(SOCKET socketFD);
	int run();

	SOCKET createTCPIPv4Socket() { return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); }
	void setupSocketToIPv4Address(sockaddr_in& socket_address_data, std::wstring address = L"", int port = 55555);

	//friend std::istream& operator>>(std::istream& is, AppType& app_type)
	//{
	//	std::string response{};
	//	is >> response;

	//	std::transform(response.begin(), response.end(), response.begin(),
	//		[](unsigned char c) { return std::tolower(c); } // correct
	//	);
	//	if (response == "server")
	//		app_type = AppType::SERVER;
	//	return is;
	//}
};

inline const std::string ChatApp::m_exit{ "exit" };

inline bool ChatApp::init()
{
	int response{ -1 };
	while (response != 0 && response != 1 && response != 2)
	{
		std::cout << "Which mode to start enter the number {SERVER - 0, SERVER_HEADLESS - 1, CLIENT - 2}:";
		std::cin >> response;
	}
	m_appMode = static_cast<AppType>(response);
	std::cin.get();
	std::cout << "You selected " << m_appMode << " mode." << std::endl;

	m_socketFD = createTCPIPv4Socket();
	if (m_socketFD == INVALID_SOCKET)
	{
		std::cout << "Owned by Skill Issue! Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return false;
	}
	else
	{
		std::cout << "socket() is fine..." << std::endl;
	}

	if (m_appMode == AppType::CLIENT)
	{
		setupSocketToIPv4Address(m_addressForASocket, L"127.0.0.1", 55555); // 42069
	}
	else
	{
		setupSocketToIPv4Address(m_addressForASocket); // 42069
	}

	m_messageBuffer.resize(4096);
	m_reciveBuffer.resize(4096);
	m_responseBuffer.resize(32);

	return true;
}


inline bool ChatApp::deinit()
{
	using enum AppType;
	if (m_appMode == SERVER || m_appMode == SERVER_HEADLESS)
	{
		if (auto result{ shutdown(m_socketFD, SD_SEND) }; result == SOCKET_ERROR)
		{
			std::cout << "Shutdown failed: " << WSAGetLastError() << std::endl;
			closesocket(m_socketFD);
			WSACleanup();
			return false;
		}
		closesocket(m_socketFD);
	}
	if (m_appMode == CLIENT)
	{
		if (auto result{ shutdown(m_socketFD, SD_SEND) }; result == SOCKET_ERROR)
		{
			std::cout << "Shutdown failed: " << WSAGetLastError() << std::endl;
			closesocket(m_socketFD);
			WSACleanup();
			return false;
		}
		closesocket(m_socketFD);
	}
	return true;
}

inline int ChatApp::sendData()
{
	while (true)
	{
		std::cout << "Please enter a message to send to the Server or type \"exit\" to close the app:" << std::endl;
		std::cin.getline(m_messageBuffer.data(), m_messageBuffer.size());
		
		if (auto result{ m_exit.compare(m_messageBuffer.data()) }; result == 0)
		{
			std::cout << "Data equals \"exit\"" << std::endl;
			return 0;
		}

		if (auto byteCount{ send(m_socketFD, m_messageBuffer.data(), m_messageBuffer.size(), 0) }; byteCount > 0)
		{
			std::cout << "\n\nMessage sent: " << std::endl << m_messageBuffer.data() << std::endl;
		}
		else
		{
			std::cout << "Owned by Skill Issue! only " << byteCount << " bytes send out off " << m_messageBuffer.size() << " from your message." << std::endl;
			WSACleanup();
		}
	}
}

inline bool ChatApp::receiveData(SOCKET socketFD)
{
	int byteCount;
	do
	{
		//byteCount = recv(m_acceptClientSocketFD, m_reciveBuffer.data(), m_reciveBuffer.size(), 0);
		byteCount = recv(socketFD, m_reciveBuffer.data(), m_reciveBuffer.size(), 0);
		if (byteCount == 0)
		{
			std::cout << "Connection closed!" << std::endl;
			break;
		}
		else if (byteCount > 0)
		{
			std::cout << "Message received: " << m_reciveBuffer.data() << std::endl;
		}
		else
		{
			std::cout << "Error: Only " << byteCount << " bytes received out off " << m_reciveBuffer.size() << " from your message." << std::endl;
			WSACleanup();
			return false;
		}
	} while (byteCount > 0);

	std::cout << "Stoped receiving data!" << std::endl;
	// closing socket
	if (m_appMode == SERVER || m_appMode == SERVER_HEADLESS)
	{
		if (auto result{ shutdown(socketFD, SD_SEND) }; result == SOCKET_ERROR)
		{
			std::cout << "Shutdown failed: " << WSAGetLastError() << std::endl;
			closesocket(socketFD);
			WSACleanup();
			return false;
		}
		closesocket(socketFD);
	}
	return true;
}

inline void ChatApp::setupSocketToIPv4Address(sockaddr_in& socket_address_data, std::wstring address, int port)
{
	socket_address_data.sin_family = AF_INET;
	socket_address_data.sin_port = htons(port);

	if (address.empty())
		socket_address_data.sin_addr.s_addr = INADDR_ANY;
	else
		InetPton(AF_INET, address.c_str(), &socket_address_data.sin_addr.s_addr);
};

inline int ChatApp::run()
{
	switch (m_appMode)
	{
		using enum AppType;
	case SERVER:
	case SERVER_HEADLESS:
	{
		//bind
		if (bind(m_socketFD, (SOCKADDR*)&m_addressForASocket, sizeof(m_addressForASocket)) == SOCKET_ERROR)
		{
			std::cout << "Owned by Skill Issue! bind() failed: " << WSAGetLastError() << std::endl;
			closesocket(m_socketFD);
			WSACleanup();
			return 0;
		}
		else
		{
			std::cout << "bind() is fine..." << std::endl;
		}
		//listen
		// second parameter is max number of clients that can be connected to specific socket
		if (listen(m_socketFD, 12) == SOCKET_ERROR)
		{
			std::cout << "Owned by Skill Issue! listen(): Error listening on socket: " << WSAGetLastError() << std::endl;
		}
		else
		{
			std::cout << "listen(): is fine.. Waiting for connections form clients." << std::endl;
		}
		//accept
		////m_acceptClientSocketFD = accept(m_socketFD, nullptr, nullptr);
		//AcceptedSocket clientSocketFD = m_acceptIncomingConnection(m_socketFD);
		////if (m_acceptClientSocketFD == INVALID_SOCKET)
		//if (clientSocketFD.acceptedSocketFD == INVALID_SOCKET)
		//{
		//	std::cout << "Owned by Skill Issue! accept() failed: " << WSAGetLastError() << std::endl;
		//	WSACleanup();
		//	return 0;
		//}
		//std::cout << "Accepted connection!" << std::endl;
		// this is no longer working
		m_run = std::bind(&ChatApp::m_startAcceptingIncomingConnection, this, m_socketFD);
		// it should be here? 
		//closesocket(m_socketFD);
		break;
		//recv
		//send
	}
	case CLIENT:
	{
		//connect
		if (connect(m_socketFD, (SOCKADDR*)&m_addressForASocket, sizeof(m_addressForASocket)) == SOCKET_ERROR)
		{
			std::cout << "Owned by Skill Issue! connect() failed: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return 0;
		}
		else
		{
			std::cout << "Client: connect() is fine..." << std::endl;
			std::cout << "Client: Can start sending and receiving data..." << std::endl;
			m_run = std::bind(&ChatApp::sendData, this);
		}
		break;
		//send
		//recv
	}
	}
	m_run();
}

inline AcceptedSocket& ChatApp::m_acceptIncomingConnection(SOCKET serverSocketFD)
{
	sockaddr clientAddress;
	int clientAddressSize{ sizeof(sockaddr) };
	AcceptedSocket* acceptedSocket = new AcceptedSocket();
	//m_acceptClientSocketFD = accept(m_socketFD, &clientAddress, &clientAddressSize);
	//acceptedSocket->acceptedSocketFD = accept(m_socketFD, &clientAddress, &clientAddressSize);
	//acceptedSocket->acceptedSocketFD = accept(m_socketFD, nullptr, nullptr);
	acceptedSocket->acceptedSocketFD = accept(m_socketFD, &clientAddress, &clientAddressSize);
	acceptedSocket->address = clientAddress;
	acceptedSocket->acceptedSuccessfully = m_acceptClientSocketFD > 0; //  ? true : false

	if (acceptedSocket->acceptedSocketFD == INVALID_SOCKET)
	{
		acceptedSocket->error = WSAGetLastError();
		std::cout << "Incoming connection wasn't accepted successfully! Error " << acceptedSocket->error << "." << std::endl;
		WSACleanup();
	}
	std::cout << "Accepted connection!" << std::endl;

	return *acceptedSocket;
}

inline int ChatApp::m_startAcceptingIncomingConnection(SOCKET serverSocketFD)
{
	while (true)
	{
		AcceptedSocket clientSocketFD = m_acceptIncomingConnection(m_socketFD);
		m_receiveAndPrintDataThread(clientSocketFD);
	}
	return 1;
	//std::thread connectionAcceptingThread(&m_acceptIncomingConnectionAndPrintRecivedData, serverSocketFD);
	//return 1;
}

//inline bool ChatApp::m_acceptIncomingConnectionAndPrintRecivedData(SOCKET serverSocketFD)
//{
//	return true;
//}

inline bool ChatApp::m_receiveAndPrintDataThread(AcceptedSocket& clientSocketData)
{
	//std::thread receivingThreadForOneClient(receiveData, clientSocketData.acceptedSocketFD);
	std::thread receivingThreadForOneClient([this, &clientSocketData]() {
		this->receiveData(clientSocketData.acceptedSocketFD);
	});
	//receiveData(clientSocketData.acceptedSocketFD);
	if (receivingThreadForOneClient.joinable())
		receivingThreadForOneClient.join();
	return true;
}