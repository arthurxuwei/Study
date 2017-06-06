/* appServer.h
 *
 * apps Server head file.
 *
 * author  arthur.Xu
 */

#include <string>
#include <winsock2.h>

#ifndef _APPSERVER_H
#define _APPSERVER_H

namespace appServer {
	
	struct AppServer {
		typedef AppServer *pointer;
		//factories
		static pointer create_dummy();
		static pointer connect(std::string port); //connect

		//interfaces
		virtual void poll() = 0;
		virtual void send(std::string message) = 0;
		virtual void close() = 0;

		virtual ~AppServer() {}
	};
}//namespace appServer



#endif

