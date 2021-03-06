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

    uint32_t clientId(0);

    map<string, ConnectionWatcherBase*>::iterator it;
    for (it = m_watchers.begin(); it != m_watchers.end(); ++it) {
        cout << "Notify observer: " << it->first << endl;
        clientId = it->second->onClientConnected(output);
    }

    cout << "\"client-" << clientId << "\" connected" << endl;

    return static_cast<void*>(new int(clientId));
}

/**
* Called when a client has finished request-handling to delete server
* context.
*/
void ServerEventHandler::deleteContext(void* serverContext,
                                       stdcxx::shared_ptr<TProtocol> input,
                                       stdcxx::shared_ptr<TProtocol> output) {
    (void)input;
    (void)output;

    int *clientId = static_cast<int*>(serverContext);
    cout << "\"client-" << *clientId << "\" disconnected" << endl;

    map<string, ConnectionWatcherBase*>::iterator it;
    for (it = m_watchers.begin(); it != m_watchers.end(); ++it) {
        cout << "Notify observer: " << it->first << endl;
        it->second->onClientDisconnected(*clientId);
    }

    delete clientId;
}
