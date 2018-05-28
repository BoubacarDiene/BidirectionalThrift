#ifndef EventReceiver_H
#define EventReceiver_H

#include <iostream>
#include <thread>

#include <thrift/protocol/TProtocol.h>
#include <thrift/Thrift.h>

namespace client {
namespace events {

template <typename P, typename H> // Processor, Handler
class EventReceiver {
public:
    EventReceiver(const uint32_t maxAcceptedFailures, H *obj,
                  const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol) {

        m_task = new std::thread([maxAcceptedFailures, protocol, obj]() {
            P *procMsgFromServer(new P(apache::thrift::stdcxx::shared_ptr<H>(obj)));

            int cnt = maxAcceptedFailures;
            while (cnt > 0) {
              try {
                while (procMsgFromServer->process(protocol, protocol, nullptr));
              } catch (apache::thrift::TException& e) {
                std::cout << "process() failed: " << e.what() << std::endl;
                --cnt;
              }
            }

            delete procMsgFromServer;
        });
    }

    virtual ~EventReceiver() {
        delete m_task;
    }

    void waitTask(bool wait) {
        if (wait)
            m_task->join();
        else
            m_task->detach();
    }

private:
    std::thread *m_task;
};

} // namespace events
} // namespace client

#endif
