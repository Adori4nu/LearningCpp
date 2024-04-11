#pragma once
#include <algorithm>
#include <array>
#include <cctype>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <winsock2.h>
#include <WS2tcpip.h>

constexpr int MAX_CONNECTED_CLIENT_COUNT = 12;

enum AppType : int
{
	SERVER,
	SERVER_HEADLESS,
	CLIENT
}; //1:20:13

struct AcceptedSocket
{
	SOCKET acceptedSocketFD{ INVALID_SOCKET };
	sockaddr address;
	int error;
	bool acceptedSuccessfully;
};

class ChatApp
{
	std::array<AcceptedSocket, 12> acceptedSockets;
	size_t acceptedSocketsCout{ 0 };
	SOCKET m_socketFD{ INVALID_SOCKET };
	SOCKET m_acceptClientSocketFD{ INVALID_SOCKET };
	sockaddr_in m_addressForASocket;
	AppType m_appMode;
	std::vector<char> m_messageBuffer;
	std::vector<char> m_responseBuffer;
	static const std::string m_exit;
	std::function<int()> m_run;
	std::vector<char> m_username;
	int sendData();
	bool receiveData(SOCKET socketFD);
	AcceptedSocket& acceptIncomingConnection(SOCKET serverSocketFD);
	int startAcceptingIncomingConnection(SOCKET serverSocketFD);
	bool receiveAndPrintDataThread(AcceptedSocket& clientSocketData);
	void sendReceivedMessageToTheOtherClients(const std::vector<char>& buffer, SOCKET socketFD);
	bool startListeningAndPrintMessagesOnNewThread(SOCKET socketFD);
	bool clientListenAndPrint(SOCKET socketFD);

public:
	ChatApp() = default;
	~ChatApp()
	{
	}

	WSADATA wsaData;
	int wsaErr;
	WORD w_VersionRequested{ MAKEWORD(2, 2) };

	bool init();
	bool deinit();
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
	
	wsaErr = WSAStartup(w_VersionRequested, &wsaData);
	if (wsaErr != 0)
	{
		std::cout << "Owned by Skill Issue! The Winsock dll not found!" << std::endl;
		return false;
	}
	else
	{
		std::cout << "The Winsock dll found!" << std::endl;
		std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
	}

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
	m_responseBuffer.resize(32);
	m_username.resize(128);

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
	std::cin.get();
	WSACleanup();
	return true;
}

inline int ChatApp::sendData()
{
	std::vector<char> messageWithUserDataBuffer(4096 + 128);
	while (true)
	{
		std::cout << "Please enter a message or type \"exit\" to close the app:" << std::endl;
		std::cin.getline(m_messageBuffer.data(), m_messageBuffer.size());
		
		if (auto result{ m_exit.compare(m_messageBuffer.data()) }; result == 0)
		{
			std::cout << "Data equals \"exit\"" << std::endl;
			return 0;
		}
		/*std::shift_right(m_messageBuffer.begin(), m_messageBuffer.end(), 128);
		m_username.at(127) = 0;
		std::copy(m_username.begin(), m_username.end(), m_messageBuffer.begin());*/

		auto it = std::ranges::find_if(m_username, [](char c) { return c == '\0'; });
		if (it != m_username.end())
		{
			*it = ' ';
			++it;
		}
		if (it != m_username.end())
		{
			*it = ':';
			++it;
		}
		if (it != m_username.end())
		{
			*it = ' ';
			++it;
		}
		if (it != m_username.end())
		{
			*it = '\0';
		}
		messageWithUserDataBuffer.assign(m_username.begin(), it);
		//--it;
		auto itDif = std::distance(m_username.begin(), it);
		auto it_2 = messageWithUserDataBuffer.begin() + itDif;
		messageWithUserDataBuffer.insert(it_2, m_messageBuffer.begin(), m_messageBuffer.end());
		if (auto byteCount{ send(m_socketFD, messageWithUserDataBuffer.data(), messageWithUserDataBuffer.size(), 0) }; byteCount > 0)
		{
			std::cout << "Message sent: " << std::endl << messageWithUserDataBuffer.data() << std::endl;
		}
		else
		{
			std::cout << "Owned by Skill Issue! only " << byteCount << " bytes send out off " << messageWithUserDataBuffer.size() << " from your message." << std::endl;
			WSACleanup();
		}
	}
}

inline bool ChatApp::receiveData(SOCKET socketFD)
{
	std::vector<char> reciveBuffer(4096 + 128);

	int byteCount;
	do
	{
		//byteCount = recv(m_acceptClientSocketFD, m_reciveBuffer.data(), m_reciveBuffer.size(), 0);
		byteCount = recv(socketFD, reciveBuffer.data(), reciveBuffer.size(), 0);
		if (byteCount == 0)
		{
			std::cout << "Connection closed!" << std::endl;
			break;
		}
		else if (byteCount > 0)
		{
			std::cout << "Message received: " << reciveBuffer.data() << std::endl;
			sendReceivedMessageToTheOtherClients(reciveBuffer, socketFD);
		}
		else
		{
			std::cout << "Error: Only " << byteCount << " bytes received out off " << reciveBuffer.size() << " from your message." << std::endl;
			WSACleanup();
			return false;
		}
	} while (byteCount > 0);

	std::cout << "Stoped receiving data!" << std::endl;
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
		if (listen(m_socketFD, MAX_CONNECTED_CLIENT_COUNT) == SOCKET_ERROR)
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
		m_run = std::bind(&ChatApp::startAcceptingIncomingConnection, this, m_socketFD);
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
		std::cout << "Pick Username max length 128 characters: ";
		std::cin.getline(m_username.data(), m_username.size());
		break;
		//send
		//recv
	}
	}
	if (m_appMode == CLIENT)
		startListeningAndPrintMessagesOnNewThread(m_socketFD);
	m_run();
}

inline AcceptedSocket& ChatApp::acceptIncomingConnection(SOCKET serverSocketFD)
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

inline int ChatApp::startAcceptingIncomingConnection(SOCKET serverSocketFD)
{
	while (acceptedSocketsCout < MAX_CONNECTED_CLIENT_COUNT)
	{
		AcceptedSocket clientSocketFD = acceptIncomingConnection(m_socketFD);
		acceptedSockets.at(acceptedSocketsCout++) = clientSocketFD;
		receiveAndPrintDataThread(clientSocketFD);
	}
	return 1;
}

inline bool ChatApp::receiveAndPrintDataThread(AcceptedSocket& clientSocketData)
{
	//std::thread receivingThreadForOneClient(receiveData, clientSocketData.acceptedSocketFD);
	std::thread receivingThreadForOneClient([this, &clientSocketData]() {
		this->receiveData(clientSocketData.acceptedSocketFD);
	});
	//if (receivingThreadForOneClient.joinable())
		//receivingThreadForOneClient.join();
	receivingThreadForOneClient.detach();
	return true;
}

inline void ChatApp::sendReceivedMessageToTheOtherClients(const std::vector<char>& buffer, SOCKET socketFD)
{
	for (size_t i{ 0 }; i < acceptedSocketsCout; ++i)
	{
		if (acceptedSockets.at(i).acceptedSocketFD != socketFD)
		{
			if (auto byteCount{ send(acceptedSockets.at(i).acceptedSocketFD, buffer.data(), buffer.size(), 0) }; byteCount > 0)
			{
				std::cout << "Message broadcasted." << std::endl;
			}
		}
	}
}

inline bool ChatApp::startListeningAndPrintMessagesOnNewThread(SOCKET socketFD)
{
	std::thread receiveAndPrintClientThread([this, &socketFD]() {
		this->clientListenAndPrint(socketFD);
	});
	receiveAndPrintClientThread.detach();
	return true;
}

inline bool ChatApp::clientListenAndPrint(SOCKET socketFD)
{
	std::vector<char> reciveBuffer(4096 + 128);

	int byteCount;
	do
	{
		//byteCount = recv(m_acceptClientSocketFD, m_reciveBuffer.data(), m_reciveBuffer.size(), 0);
		byteCount = recv(socketFD, reciveBuffer.data(), reciveBuffer.size(), 0);
		if (byteCount == 0)
		{
			std::cout << "Connection closed!" << std::endl;
			break;
		}
		else if (byteCount > 0)
		{
			std::cout << reciveBuffer.data() << std::endl;
		}
		else
		{
			std::cout << "Error: Only " << byteCount << " bytes received out off " << reciveBuffer.size() << " from your message." << std::endl;
			WSACleanup();
			return false;
		}
	} while (byteCount > 0);

	std::cout << "Stoped receiving data!" << std::endl;
	return true;
}