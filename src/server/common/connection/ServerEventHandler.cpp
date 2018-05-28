#include <iostream>
#include <iterator>
#include <thread>

#include "ServerEventHandler.h"

using namespace ::std;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;

using namespace ::server::common::connection;

/**
* Called when a new client has connected and is about to being processing.
*/
void* ServerEventHandler::createContext(stdcxx::shared_ptr<TProtocol> input,
                                        stdcxx::shared_ptr<TProtocol> output) {
    (void)input;

    cout << "ServerEventHandler: Client connected" << endl;

    map<string, ConnectionWatcherBase*>::iterator it;
    for (it = watchers.begin(); it != watchers.end(); ++it) {
        cout << "Notify observer: " << it->first << endl;
        it->second->onClientConnected(output);
    }

    return NULL;
}

/**
* Called when a client has finished request-handling to delete server
* context.
*/
void ServerEventHandler::deleteContext(void* serverContext,
                                       stdcxx::shared_ptr<TProtocol> input,
                                       stdcxx::shared_ptr<TProtocol> output) {
    (void)serverContext;
    (void)input;
    (void)output;

    cout << "ServerEventHandler: Client disconnected" << endl;

    map<string, ConnectionWatcherBase*>::iterator it;
    for (it = watchers.begin(); it != watchers.end(); ++it) {
        cout << "Notify observer: " << it->first << endl;
        it->second->onClientDisconnected();
    }
}
