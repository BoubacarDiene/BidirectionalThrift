#include <iostream>
#include <thread>

#include "Service2Handler.h"

using namespace ::std;

using namespace ::apache::thrift; // TException

using namespace ::generated;
using namespace ::generated::shared;

using namespace ::server::services::service2;

void Service2Handler::doSyncWork(const Request& req) {
    cout << "Service2: doSyncWork - in" << endl;

    // Do work
    sleep(req.sleepTime);

    // send result to client
    Result result;
    result.value = "{ Service2, doSyncWork }";
    try {
        m_client->onSyncWorkResult(result);
    } catch (TException& e) {
        // What to do in this case?
        // - Retry sending result when client will be back
        // - ...
        cerr << "Service1: " << e.what() << endl;
    }

    cout << "Service2: doSyncWork - out" << endl;
}

void Service2Handler::doAsyncWork(const Request& req) {
    thread th([req, this]() {
        cout << "Service2: doAsyncWork - in" << endl;

        // Do work
        sleep(req.sleepTime);

        // send result to client
        Result result;
        result.value = "{ Service2, doAsyncWork }";
        try {
            m_client->onAsyncWorkResult(result);
        } catch (TException& e) {
            // What to do in this case?
            // - Retry sending result when client will be back
            // - ...
            cerr << "Service1: " << e.what() << endl;
        }

        cout << "Service2: doAsyncWork - out" << endl;
    });
    th.detach();
}

void Service2Handler::doSyncNoResultWork(const Request& req) {
    cout << "Service2: doSyncNoResultWork - in" << endl;

    // Do work - no result expected
    sleep(req.sleepTime);

    cout << "Service2: doSyncNoResultWork - out" << endl;
}
