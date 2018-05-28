#ifndef Service1EventHandler_H
#define Service1EventHandler_H

#include "generated/Service1.h"
#include "generated/Service1Event.h"

#include "generated/shared_types.h"

#include "client/events/EventReceiver.h"

namespace client {
namespace events {
namespace service1 {

class Service1EventHandler : public generated::Service1EventIf,
                             public client::events::EventReceiver<generated::Service1EventProcessor,
                                                                  Service1EventHandler> {
public:
    Service1EventHandler(const uint32_t maxAcceptedFailures,
                         const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol)
                         : EventReceiver(maxAcceptedFailures, this, protocol) {}

    void onSyncWorkResult(const generated::shared::Result& res);
    void onAsyncWorkResult(const generated::shared::Result& res);
};

} // namespace service1
} // namespace events
} // namespace client

#endif
