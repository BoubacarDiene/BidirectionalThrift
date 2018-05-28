#include <iostream>
#include <thread>

#include "Service2EventHandler.h"

using namespace ::std;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;

using namespace ::generated;
using namespace ::generated::shared;

using namespace ::client::events::service2;

void Service2EventHandler::onSyncWorkResult(const Result& res) {
    cout << "Service2EventHandler - From server: " << res.value << endl;
}

void Service2EventHandler::onAsyncWorkResult(const Result& res) {
    cout << "Service2EventHandler - From server: " << res.value << endl;
}
