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

#ifndef ConnectionWatcher_H
#define ConnectionWatcher_H

#include <thrift/protocol/TProtocol.h>

namespace server {
namespace common {
namespace connection {

class ConnectionWatcherBase {
public:
    virtual ~ConnectionWatcherBase() {}

    virtual void onClientConnected(const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol) = 0;
    virtual void onClientDisconnected() = 0;
};

template <typename T>
class ConnectionWatcher : public ConnectionWatcherBase {
public:
    virtual ~ConnectionWatcher() {}

    virtual void onClientConnected(const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol) {
        m_client = new T(protocol);
    }

    virtual void onClientDisconnected() {
        delete m_client;
    }

protected:
    T *m_client;
};

} // namespace connection
} // namespace common
} // namespace server

#endif

