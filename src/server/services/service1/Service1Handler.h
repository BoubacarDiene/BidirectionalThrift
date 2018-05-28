#ifndef Service1Handler_H
#define Service1Handler_H

#include "generated/Service1.h"
#include "generated/Service1Event.h"

#include "server/common/connection/ConnectionWatcher.h"

namespace server {
namespace services {
namespace service1 {

class Service1Handler : public generated::Service1If,
                        public server::common::connection::ConnectionWatcher<generated::Service1EventClient> {
public:
    virtual ~Service1Handler() {}

    void doSyncWork(const generated::shared::Request& req);
    void doAsyncWork(const generated::shared::Request& req);
    void doSyncNoResultWork(const generated::shared::Request& req);
};

} // namespace service1
} // namespace services
} // namespace server

#endif
