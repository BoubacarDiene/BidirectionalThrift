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
        auto functor = [result](Service1EventClient *client) {
            client->onSyncWorkResult(result);
        };
        sendMessageToClients(functor);
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
            auto functor = [result](Service1EventClient *client) {
                client->onAsyncWorkResult(result);
            };
            sendMessageToClients(functor);
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
