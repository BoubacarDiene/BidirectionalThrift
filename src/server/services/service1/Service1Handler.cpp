#include <iostream>
#include <thread>

#include "Service1Handler.h"

using namespace ::std;

using namespace ::apache::thrift; // TException

using namespace ::generated;
using namespace ::generated::shared;

using namespace ::server::services::service1;

void Service1Handler::doSyncWork(const Request& req) {
    cout << "Service1: doSyncWork - in" << endl;

    // Do work
    sleep(req.sleepTime);

    // send result to client
    Result result;
    result.value = "{ Service1, doSyncWork }";
    try {
        m_client->onSyncWorkResult(result);
    } catch (TException& e) {
        // What to do in this case?
        // - Retry sending result when client will be back
        // - ...
        cerr << "Service1: " << e.what() << endl;
    }

    cout << "Service1: doSyncWork - out" << endl;
}

void Service1Handler::doAsyncWork(const Request& req) {
    thread th([req, this]() {
        cout << "Service1: doAsyncWork - in" << endl;

        // Do work
        sleep(req.sleepTime);

        // send result to client
        Result result;
        result.value = "{ Service1, doAsyncWork }";
        try {
            m_client->onAsyncWorkResult(result);
        } catch (TException& e) {
            // What to do in this case?
            // - Retry sending result when client will be back
            // - ...
            cerr << "Service1: " << e.what() << endl;
        }

        cout << "Service1: doAsyncWork - out" << endl;
    });
    th.detach();
}

void Service1Handler::doSyncNoResultWork(const Request& req) {
    cout << "Service1: doSyncNoResultWork - in" << endl;

    // Do work - no result expected
    sleep(req.sleepTime);

    cout << "Service1: doSyncNoResultWork - out" << endl;
}
