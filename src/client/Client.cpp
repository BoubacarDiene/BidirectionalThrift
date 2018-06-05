//////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                              //
//                 Copyright © 2018 Boubacar DIENE                                              //
//                                                                                              //
//                 This file is part of BidirectionalThrift project.                            //
//                                                                                              //
//                 Licensed to the Apache Software Foundation (ASF) under one                   //
//                 or more contributor license agreements.  See the NOTICE file                 //
//                 distributed with this work for additional information                        //
//                 regarding copyright ownership.  The ASF licenses this file                   //
//                 to you under the Apache License, Version 2.0 (the                            //
//                 "License"); you may not use this file except in compliance                   //
//                 with the License.  You may obtain a copy of the License at                   //
//                                                                                              //
//                 http://www.apache.org/licenses/LICENSE-2.0                                   //
//                                                                                              //
//                 Unless required by applicable law or agreed to in writing,                   //
//                 software distributed under the License is distributed on an                  //
//                 "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY                       //
//                 KIND, either express or implied.  See the License for the                    //
//                 specific language governing permissions and limitations                      //
//                 under the License.                                                           //
//                                                                                              //
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

// Thrift
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TMultiplexedProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/stdcxx.h>

// Events
#include "client/events/service1/Service1EventHandler.h"
#include "client/events/service2/Service2EventHandler.h"

// Constants
#include "generated/main_constants.h"

using namespace ::std;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using namespace ::generated;
using namespace ::generated::shared;

using namespace ::client::events::service1;
using namespace ::client::events::service2;

int main(int argc, char **argv) {
    try {
        //// Connect to server
        stdcxx::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
        stdcxx::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        stdcxx::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        transport->open();

        //// Start incoming messages task
        const uint32_t maxAcceptedFailures = 10;
        Service1EventHandler service1EventHandler(maxAcceptedFailures, protocol);
        Service2EventHandler service2EventHandler(maxAcceptedFailures, protocol);

        //// Send messages to server
        stdcxx::shared_ptr<TMultiplexedProtocol> mp1(new TMultiplexedProtocol(protocol, g_main_constants.SERVICE1_NAME));
        Service1Client svc1(mp1);

        stdcxx::shared_ptr<TMultiplexedProtocol> mp2(new TMultiplexedProtocol(protocol, g_main_constants.SERVICE2_NAME));
        Service2Client svc2(mp2);

        Request req;
        req.sleepTime = 5;
        req.myEnum = MyEnum::VAL2;

        // Sequential - Expected result:
        //   { Service1, doSyncWork }
        //   { Service2, doSyncWork }
        svc1.doSyncWork(req);
        svc2.doSyncWork(req);

        // Sequential - No result expected
        svc1.doSyncNoResultWork(req);
        svc2.doSyncNoResultWork(req);

        // Parallel - Expected result (not necessarily in this order):
        //   { Service1, doAsyncSyncWork }
        //   { Service2, doAsyncSyncWork }
        svc1.doAsyncWork(req);
        svc2.doAsyncWork(req);

        //// Keep client alive
        service1EventHandler.waitTask(true);
        service2EventHandler.waitTask(true);

        //// Close connection
        transport->close();
    } catch (TException& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
