#ifndef Service2Handler_H
#define Service2Handler_H

#include "generated/Service2.h"
#include "generated/Service2Event.h"

#include "server/common/connection/ConnectionWatcher.h"

namespace server {
namespace services {
namespace service2 {

class Service2Handler : public generated::Service2If,
                        public server::common::connection::ConnectionWatcher<generated::Service2EventClient> {
public:
    virtual ~Service2Handler() {}

    void doSyncWork(const generated::shared::Request& req);
    void doAsyncWork(const generated::shared::Request& req);
    void doSyncNoResultWork(const generated::shared::Request& req);
};

} // namespace service2
} // namespace services
} // namespace server

#endif
