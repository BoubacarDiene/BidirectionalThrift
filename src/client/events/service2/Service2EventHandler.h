#ifndef Service2EventHandler_H
#define Service2EventHandler_H

#include "generated/Service2.h"
#include "generated/Service2Event.h"

#include "generated/shared_types.h"

#include "client/events/EventReceiver.h"

namespace client {
namespace events {
namespace service2 {

class Service2EventHandler : public generated::Service2EventIf,
                             public client::events::EventReceiver<generated::Service2EventProcessor,
                                                                  Service2EventHandler> {
public:
    Service2EventHandler(const uint32_t maxAcceptedFailures,
                         const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol)
                         : EventReceiver(maxAcceptedFailures, this, protocol) {}

    void onSyncWorkResult(const generated::shared::Result& res);
    void onAsyncWorkResult(const generated::shared::Result& res);
};

} // namespace service2
} // namespace events
} // namespace client

#endif
