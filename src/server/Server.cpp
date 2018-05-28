#include <iostream>

// Thrift
#include <thrift/processor/TMultiplexedProcessor.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

// Services
#include "services/service1/Service1Handler.h"
#include "services/service2/Service2Handler.h"

// Connection watcher
#include "common/connection/ServerEventHandler.h"

// Constants
#include "generated/main_constants.h"

using namespace ::std;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::transport;

using namespace ::generated;
using namespace ::generated::shared;

using namespace ::server::services::service1;
using namespace ::server::services::service2;

using namespace ::server::common::connection;

static void signalHandler(int sig)
{
    cout << "SIGINT" << endl;
    exit(0); // Properly stop server here
}

int main(int argc, char **argv) {
    //// Signal handler
    signal(SIGINT, &signalHandler);

    //// Services
    Service1Handler *svc1Handler = new Service1Handler;
    Service2Handler *svc2Handler = new Service2Handler;

    map<string, ConnectionWatcherBase*> services;
    services[g_main_constants.SERVICE1_NAME] = svc1Handler;
    services[g_main_constants.SERVICE2_NAME] = svc2Handler;

    //// Multiplexed processor
    stdcxx::shared_ptr<TMultiplexedProcessor> multiplexedProcessor(new TMultiplexedProcessor);

    // --> Add service1
    multiplexedProcessor->registerProcessor(g_main_constants.SERVICE1_NAME,
                                            stdcxx::shared_ptr<TProcessor>(new Service1Processor(
                                                stdcxx::shared_ptr<Service1Handler>(svc1Handler))));
    // --> Add service2
    multiplexedProcessor->registerProcessor(g_main_constants.SERVICE2_NAME,
                                            stdcxx::shared_ptr<TProcessor>(new Service2Processor(
                                                stdcxx::shared_ptr<Service2Handler>(svc2Handler))));

    //// Server
    stdcxx::shared_ptr<TServerTransport> transport(new TServerSocket(9090));
    stdcxx::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory);
    stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory);

    TSimpleServer server(multiplexedProcessor, transport, transportFactory, protocolFactory);
    server.setServerEventHandler(stdcxx::shared_ptr<ServerEventHandler>(new ServerEventHandler(services)));

    cout << "Server is running ..." << endl;
    server.serve();

    return 0;
}

