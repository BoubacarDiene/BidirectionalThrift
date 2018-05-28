#ifndef ConnectionWatcher_H
#define ConnectionWatcher_H

#include <thrift/protocol/TProtocol.h>

namespace server {
namespace common {
namespace connection {

class ConnectionWatcherBase {
public:
    virtual ~ConnectionWatcherBase() {}

    virtual void onClientConnected(const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol) = 0;
    virtual void onClientDisconnected() = 0;
};

template <typename T>
class ConnectionWatcher : public ConnectionWatcherBase {
public:
    virtual ~ConnectionWatcher() {}

    virtual void onClientConnected(const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol) {
        m_client = new T(protocol);
    }

    virtual void onClientDisconnected() {
        delete m_client;
    }

protected:
    T *m_client;
};

} // namespace connection
} // namespace common
} // namespace server

#endif

