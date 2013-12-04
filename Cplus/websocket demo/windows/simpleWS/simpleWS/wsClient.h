/* wsClient.h
 *
 * websocket client head file.
 *
 * author  arthur.Xu
 */

#include <string>

#ifndef _WSCLIENT_H
#define _WSCLIENT_H

namespace wsClient {
	
	struct WebSocket {
		typedef WebSocket *pointer;
		typedef enum readyStateValues { CLOSING, CLOSED, CONNECTING, OPEN } readyStateValues;

		//factories
		static pointer create_dummy();
		static pointer from_url(std::string url);

		//interfaces
		virtual void poll() = 0;
		virtual void send(std::string message) = 0;
		virtual void close() = 0;
		virtual readyStateValues getReadyState() = 0;

		template<class Callable>
		void dispatch(Callable callable) {
			struct _Callback : public Callback {
				Callable &callable;
				_Callback(Callable &callable) :callable(callable) {}
				void operator()(const std::string &message) { callable(message); }
			};
			_Callback callback(callable);
			_dispatch(callback);
		}

		virtual ~WebSocket() {}

	protected:
		struct Callback {
			virtual void operator()(const std::string &message) = 0;
		};
		virtual void _dispatch(Callback &callable) = 0;
	};
}//namespace wsClient



#endif

