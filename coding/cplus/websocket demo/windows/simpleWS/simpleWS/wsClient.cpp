#include "wsClient.h"

#include <stdio.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

//close warning
#pragma warning(disable:4996)

namespace { //private module 
	int hostname_connect(std::string hostname, int port) {
		struct addrinfo hints;
		struct addrinfo *result;
		struct addrinfo *p;

		WSADATA wsaData;
		int iResult;
		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed: %d\n", iResult);
			return 1;
		}

		int ret;
		int sockfd = -1;
		char sport[16];
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		_snprintf_s(sport, 16, "%d", port);
		if ((ret = getaddrinfo(hostname.c_str(), sport, &hints, &result)) != 0 ) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
			return 1;
		}

		for(p = result; p != NULL; p = p->ai_next) {
			sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
			if (sockfd == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return 1;
			}

			// Connect to server.
			iResult = connect( sockfd, p->ai_addr, (int)p->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(sockfd);
				sockfd = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (sockfd == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return 1;
		}
		return sockfd;
	}
}//unnamed namespace

namespace wsClient {
	struct _DummyWebSocket : public WebSocket {
		void poll() {}
		void send(std::string message) {}
		void close() {}
		void _dispatch(Callback &callable) {}
		readyStateValues getReadyState() {return CLOSED;}
	};

	struct _RealWebSocket : public WebSocket {
		//websocket head
		struct wsheader_type {
			int header_size;
			bool fin;
			bool mask;
			enum opcode_type {
				CONTINUATION = 0x0,
				TEXT_FRAME = 0x1,
				BINARY_FRAME = 0x2,
				CLOSE = 8,
				PING = 9,
				PONG = 0xa,
			} opcode;
			int N0;
			_int64 N;
			_int8 masking_key[4];
		};

		std::vector<_int8> rxbuf;
		std::vector<_int8> txbuf;

		int sockfd;
		readyStateValues readyState;

		_RealWebSocket(int sockfd) : sockfd(sockfd), readyState(OPEN) { }

		readyStateValues getReadyState() {
			return readyState;
		}

		void poll() {
			if (readyState == CLOSED) return;
			while (true) {
				int N = rxbuf.size();
				SSIZE_T ret;
				rxbuf.resize(N + 1500);
				ret = recv(sockfd, &rxbuf[0] + N, 1500, 0);
				if (ret < 0) {
					rxbuf.resize(N);
					break;
				} else if (ret == 0) {
					rxbuf.resize(N);
					closesocket(sockfd);
					readyState = CLOSED;
					fprintf(stderr, "Connection closed!\n");
					break;
				} else {
					rxbuf.resize(N + ret);
				}
			}//while

			while (txbuf.size()) {
				int ret = ::send(sockfd, &txbuf[0], txbuf.size(), 0);
				if (ret > 0) { txbuf.erase(txbuf.begin(), txbuf.begin() + ret); }
				else 
					break;
			}//while

			if (!txbuf.size() && readyState == CLOSING) {
				closesocket(sockfd);
				readyState = CLOSED;
			}
		}//poll()


		virtual void _dispatch(WebSocket::Callback &callable) {
			while (true) {
				wsheader_type ws;
				if (rxbuf.size() < 2) return;
				const _int8 * data = (_int8 *)&rxbuf[0];
				ws.fin = (data[0] & 0x80) == 0x80;
				ws.opcode = (wsheader_type::opcode_type)(data[0] & 0x0f);
				ws.mask = (data[1] & 0x80) == 0x80;
				ws.N0 = (data[1] & 0x7f);
				ws.header_size = 2 + (ws.N0 == 126 ? 2 : 0) + (ws.N0 == 127 ? 6 : 0) + 
					(ws.mask ? 4 : 0);
				if (rxbuf.size() < ws.header_size) return;
				int i;
				if (ws.N0 < 126) {
					ws.N = ws.N0;
					i = 2;
				} else if (ws.N0 == 126) {
					ws.N = 0;
					ws.N |= ((_int64)data[2]) << 8;
					ws.N |= ((_int64)data[3]) << 0;
					i = 4;
				} else if (ws.N0 == 127) {
					ws.N = 0;
					ws.N |= ((_int64)data[2]) << 56;
					ws.N |= ((_int64)data[3]) << 48;
					ws.N |= ((_int64)data[4]) << 40;
					ws.N |= ((_int64)data[5]) << 32;
					ws.N |= ((_int64)data[6]) << 24;
					ws.N |= ((_int64)data[7]) << 16;
					ws.N |= ((_int64)data[8]) << 8;
					ws.N |= ((_int64)data[9]) << 0;
					i = 10;
				}

				if (ws.mask) {
					ws.masking_key[0] = ((_int8)data[i + 0]) << 0;
					ws.masking_key[1] = ((_int8)data[i + 1]) << 0;
					ws.masking_key[2] = ((_int8)data[i + 2]) << 0;
					ws.masking_key[3] = ((_int8)data[i + 3]) << 0;
				} else {
					ws.masking_key[0] = 0;
					ws.masking_key[1] = 0;
					ws.masking_key[2] = 0;
					ws.masking_key[3] = 0;
				}

				if (rxbuf.size() < ws.header_size + ws.N) return;

				if (ws.opcode == wsheader_type::TEXT_FRAME && ws.fin) {
					if(ws.mask) {
						for(size_t i = 0; i != ws.N; ++i) {
							rxbuf[i + ws.header_size] ^= ws.masking_key[i & 0x3];
						}
					}//nested-if
					std::string data(rxbuf.begin() + ws.header_size, rxbuf.begin() + ws.header_size + ws.N);
					callable((const std::string)data);
				} else if (ws.opcode == wsheader_type::PING) {
				} else if (ws.opcode == wsheader_type::PONG) {
				} else if (ws.opcode == wsheader_type::CLOSE) {
					close();
				} else {
					fprintf(stderr, "ERROR: Got unexpected WebSocket message.\n");
					close();
				}
				rxbuf.erase(rxbuf.begin(), rxbuf.begin() + ws.header_size + ws.N);
			}//while
		}//_dispatch()

		void send(std::string message) {
			if (readyState == CLOSING || readyState == CLOSED) return;
			std::vector<_int8> header;
			header.assign(2 + (message.size() >= 126 ? 2 : 0) + (message.size() >= 64436 ? 6 : 0), 0);
			header[0] = 0x80 | wsheader_type::TEXT_FRAME;
			if (message.size() < 126) {
				header[1] = message.size();
			} else if (message.size() < 64436) {
				header[1] = 126;
				header[2] = (message.size() >> 8) & 0xff;
				header[3] = (message.size() >> 0) & 0xff;
			} else {
				header[1] = 127;
				header[2] = (message.size() >> 56) & 0xff;
				header[3] = (message.size() >> 48) & 0xff;
				header[4] = (message.size() >> 40) & 0xff;
				header[5] = (message.size() >> 32) & 0xff;
				header[6] = (message.size() >> 24) & 0xff;
				header[7] = (message.size() >> 16) & 0xff;
				header[8] = (message.size() >> 8) & 0xff;
				header[9] = (message.size() >> 0) & 0xff;
			}
			txbuf.insert(txbuf.end(), header.begin(), header.end());
			txbuf.insert(txbuf.end(), message.begin(), message.end());
		}//send()

		void close() {
			if (readyState == CLOSING || readyState == CLOSED) return;
			readyState = CLOSING;
			fprintf(stderr, "Close...\n");
			_int8 closeFrame[4] = {0x88, 0x00, 0x00, 0x00};
			std::vector<_int8> header(closeFrame, closeFrame + 4);
			txbuf.insert(txbuf.end(), header.begin(), header.end());
		}//close()
	};

	WebSocket::pointer WebSocket::create_dummy() {
		static pointer dummy = pointer(new _DummyWebSocket);
		return dummy;
	}

	WebSocket::pointer WebSocket::from_url(std::string url) {
		char host[128];
		int port;
		char path[128];
		if (sscanf(url.c_str(), "ws://%[^:/]:%d/%s", host, &port, path) == 3) {
		} else if (sscanf(url.c_str(), "ws://%[^:/]/%s", host, path) == 2) {
			port = 80;
		} else if (sscanf(url.c_str(), "ws://%[^:/]:%d", host, &port) == 2) {
			path[0] = '\0';
		} else if (sscanf(url.c_str(), "ws://%[^:/]", host) == 1) {
			port = 80;
			path[0] = '\0';
		}   else {
			fprintf(stderr, "ERROR: Could not parse WebSocket url: %s\n", url.c_str());
			return NULL;
		}

		fprintf(stderr, "wsClient: connecting: host=%s port=%d path=/%s\n", host, port, path);
		int sockfd = hostname_connect(host, port);
		if (sockfd == -1) {
			fprintf(stderr, "ERROR:Unable to connect to %s: %d\n", host, port);
			return NULL;
		}

		{
			//this should be done non-blocking
			char line[256];
			int status;
			int i;

			_snprintf(line, 256, "GET /%s HTTP/1.1\r\n", path); 
			::send(sockfd, line, strlen(line), 0);
			_snprintf(line, 256, "Host: %s:%d\r\n", host, port); 
			::send(sockfd, line, strlen(line), 0);
			_snprintf(line, 256, "Upgrade: websocket\r\n"); 
			::send(sockfd, line, strlen(line), 0);
			_snprintf(line, 256, "Connection: Upgrade\r\n"); 
			::send(sockfd, line, strlen(line), 0);
			_snprintf(line, 256, "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==\r\n"); 
			::send(sockfd, line, strlen(line), 0);
			_snprintf(line, 256, "Sec-WebSocket-Version: 13\r\n"); 
			::send(sockfd, line, strlen(line), 0);
			_snprintf(line, 256, "\r\n"); 
			::send(sockfd, line, strlen(line), 0);


			for (i = 0; i < 2 || i < 255 && line[i - 2] != '\r' && line[i - 1] != '\n'; ++i) {
				if (recv(sockfd, line + i, 1, 0) == 0) return NULL;
			}
			line[i] = 0;
			if (i == 255) { 
				fprintf(stderr, "ERROR: Got invalid status line connecting to: %s\n", url.c_str());
				return NULL;
			}
			if (sscanf(line, "HTTP/1.1 %d", &status) != 1 || status != 101) {
				fprintf(stderr, "ERROR: Got bad status line connecting to %s: %s\n", url.c_str(), line);
				return NULL;
			}

			//verify response headers
			while (true) {
				for (i = 0; i < 2 || i < 255 && line[i - 2] != '\r' && line[i - 1] != '\n'; ++i) {
					if (recv(sockfd, line + i, 1, 0) == 0) return NULL;
				}
				if (line[0] == '\r' && line[1] == '\n') break;
			}
		}

		int flag = 1;
		setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(flag)); //disable Nagle's algorithm
		u_long ul = 1;
		ioctlsocket(sockfd, FIONBIO,&ul);
		fprintf(stderr, "Connected to: %s\n", url.c_str());
		return pointer(new _RealWebSocket(sockfd));
	}
}

