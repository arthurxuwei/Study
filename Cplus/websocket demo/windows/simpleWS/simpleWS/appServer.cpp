#include "appServer.h"

#include <stdio.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "55555"
//close warning
#pragma warning(disable:4996)

namespace { //private module 
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

/*	DWORD WINAPI AcceptThread( void*param )  
	{  
		while(true)  
		{  
			sockaddr_in addr;  
			SOCKET s;  
			int len = sizeof(addr);  
			s = accept(ListenSocket, (sockaddr*)&addr, &len);  
			if(s==SOCKET_ERROR)  {  
				int r=WSAGetLastError();  
				if(r==WSAENOTSOCK)  {  //no client 
					continue;  
				} else {  
					return false;  
				}  
			} else {  //accept client
				fprintf(stderr, "accept client: %d\n", s);
				ClientSocket = s;
			}  
		}   
		fprintf(stderr, "exit acceptThread\n");
		return 0;  
	}  
*/
	int local_listen(std::string port) {
		WSADATA wsaData;
		int iResult;

		struct addrinfo *result = NULL;
		struct addrinfo hints;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return 1;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
		if ( iResult != 0 ) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return 1;
		}

		// Create a SOCKET for connecting to server
		ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (ListenSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return 1;
		}

//		unsigned long ul=1;  
//		int r=ioctlsocket(ListenSocket,FIONBIO,&ul); 

		// Setup the TCP listening socket
		iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		freeaddrinfo(result);

		iResult = listen(ListenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		// Accept a client socket
//		HANDLE hAcceptHandle = CreateThread(NULL,0,AcceptThread,NULL,0,NULL);  
//		if(hAcceptHandle==NULL)	return false;  
		   // Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		// No longer need server socket
		closesocket(ListenSocket);

		return ClientSocket;
	}


}//unnamed namespace

namespace appServer {
	struct _DummyWebSocket : public AppServer {
		void poll() {}
		void send(std::string message) {}
		void close() {}
	};

	struct _RealAppServer : public AppServer {

		std::vector<_int8> rxbuf;
		std::vector<_int8> txbuf;

		SOCKET ClientSocket;

		_RealAppServer(SOCKET clientsock) : ClientSocket(clientsock) { }

		void poll() {
			SSIZE_T ret;
			if (ClientSocket == INVALID_SOCKET) return;

			while (txbuf.size()) {
				int ret = ::send(ClientSocket, &txbuf[0], txbuf.size(), 0);
				if (ret > 0) { txbuf.erase(txbuf.begin(), txbuf.begin() + ret); }
				else 
					break;
				fprintf(stderr, "Send Over\n");
			}//while

			// Receive until the peer shuts down the connection
/*			do {
				int N = rxbuf.size();
				rxbuf.resize(N + 1500);

				ret = recv(ClientSocket, &rxbuf[0] + N, 1500, 0);
				if (ret < 0) {
					int r = WSAGetLastError();
					rxbuf.resize(N);
					if (r == WSAEWOULDBLOCK) continue;
					fprintf(stderr, "recv failed with error: %d\n", r);
					closesocket(ClientSocket);
					WSACleanup();
					break;
				} else if (ret == 0) {
					rxbuf.resize(N);
					closesocket(ClientSocket);
					fprintf(stderr, "Connection closed!\n");
					break;
				} else {
					fprintf(stderr, "Message: %s\n", rxbuf);
					fprintf(stderr, "Bytes received: %d\n", ret);
					rxbuf.resize(N + ret);
				}
			} while (ret > 0);
*/
		}//poll()

		void send(std::string message) {
			txbuf.insert(txbuf.end(), message.begin(), message.end());
		}//send()

		void close() {
			int iResult;
			// shutdown the connection since we're done
			iResult = shutdown(ClientSocket, SD_SEND);
			if (iResult == SOCKET_ERROR) {
				printf("shutdown failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return;
			}
			// cleanup
			closesocket(ClientSocket);
			WSACleanup();
		}//close()
	};

	AppServer::pointer AppServer::create_dummy() {
		static pointer dummy = pointer(new _DummyWebSocket);
		return dummy;
	}

	AppServer::pointer AppServer::connect(std::string port) {
		fprintf(stderr, "appServer: Listening: port=%s\n", port.c_str());
		SOCKET ClientSocket = local_listen(port);
		fprintf(stderr, "Accept A Client.\n");
		return pointer(new _RealAppServer(ClientSocket));
	}
}

