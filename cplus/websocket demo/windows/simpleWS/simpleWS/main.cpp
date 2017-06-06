#include "wsClient.h"
#include "appServer.h"

#include <assert.h>
#include <string>

using wsClient::WebSocket;
static WebSocket::pointer ws = NULL;

using appServer::AppServer;
static AppServer::pointer as = NULL;

void handle_message(const std::string &message) {
	printf(">>> %s\n", message.c_str());
//	if (message == "end") {
		as->send(message);
		as->poll();
//	}
}

int main() {
	ws = WebSocket::from_url("ws://16.187.94.183:8126/windows");
	as = AppServer::connect("55555");
	assert(ws);
	assert(as);

	ws->send("hello");
	ws->send("goodbye");
	
	while (ws->getReadyState() != WebSocket::CLOSED) {
		ws->poll();
		ws->dispatch(handle_message);
	}

	return 0;
}