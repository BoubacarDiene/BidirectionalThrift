#include <iostream>
#include <thread>

#include "Service1EventHandler.h"

using namespace ::std;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;

using namespace ::generated;
using namespace ::generated::shared;

using namespace ::client::events::service1;

void Service1EventHandler::onSyncWorkResult(const Result& res) {
    cout << "Service1EventHandler - From server: " << res.value << endl;
}

void Service1EventHandler::onAsyncWorkResult(const Result& res) {
    cout << "Service1EventHandler - From server: " << res.value << endl;
}
