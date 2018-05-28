#ifndef ServerEventHandler_H
#define ServerEventHandler_H

#include <map>
#include <string>

#include <thrift/server/TServer.h>
#include <thrift/stdcxx.h>

#include "ConnectionWatcher.h"

namespace server {
namespace common {
namespace connection {

class ServerEventHandler : public apache::thrift::server::TServerEventHandler {
public:
    ServerEventHandler(const std::map<std::string, ConnectionWatcherBase*>& services) : watchers(services) {}

    // Called by thrift when client is connected
    void* createContext(apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol> input,
                        apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol> output);

    // Called by thrift when client is disconnected
    void deleteContext(void* serverContext,
                       apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol> input,
                       apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol> output);

private:
    std::map<std::string, ConnectionWatcherBase*> watchers;
};

} // namespace connection
} // namespace common
} // namespace server

#endif

