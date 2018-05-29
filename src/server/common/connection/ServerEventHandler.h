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

#ifndef ServerEventHandler_H
#define ServerEventHandler_H

#include <map>
#include <string>

#include <thrift/server/TServer.h>
#include <thrift/stdcxx.h>

#include "ConnectionWatcher.h"

namespace server {
namespace common {
namespace connection {

class ServerEventHandler : public apache::thrift::server::TServerEventHandler {
public:
    ServerEventHandler(const std::map<std::string, ConnectionWatcherBase*>& services) : watchers(services) {}

    // Called by thrift when client is connected
    void* createContext(apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol> input,
                        apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol> output);

    // Called by thrift when client is disconnected
    void deleteContext(void* serverContext,
                       apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol> input,
                       apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol> output);

private:
    std::map<std::string, ConnectionWatcherBase*> watchers;
};

} // namespace connection
} // namespace common
} // namespace server

#endif

