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

#include <iterator>

#include <thrift/protocol/TProtocol.h>

namespace server {
namespace common {
namespace connection {

class ConnectionWatcherBase {
public:
    virtual ~ConnectionWatcherBase() {}

    virtual uint32_t onClientConnected(const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol) = 0;
    virtual void onClientDisconnected(const uint32_t clientId) = 0;
};

class ConnectionWatcherMessageSender {
public:
    virtual ~ConnectionWatcherMessageSender() {}

    template<typename Functor>
    void sendMessageToClients(Functor functor);
};

template <typename T>
class ConnectionWatcher : public ConnectionWatcherBase,
                          public ConnectionWatcherMessageSender {
public:
    ConnectionWatcher() : m_nbConnectedClients(0) {}
    virtual ~ConnectionWatcher() {}

    virtual uint32_t onClientConnected(const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol) {
        uint32_t clientId = ++m_nbConnectedClients;

        std::string name("client-" + std::to_string(clientId));
        m_clients[name] = new T(protocol);

        return clientId;
    }

    virtual void onClientDisconnected(const uint32_t clientId) {
        std::string name("client-" + std::to_string(clientId));

        delete m_clients[name];
        m_clients.erase(name);

        m_nbConnectedClients = m_clients.size() == 0 ? 0 : m_nbConnectedClients;
    }

    template<typename Functor>
    void sendMessageToClients(Functor functor) {
        typename std::map<std::string, T*>::iterator it;
        for (it = m_clients.begin(); it != m_clients.end(); ++it) {
            functor(it->second);
        }
    }

protected:
    std::map<std::string, T*> m_clients;

private:
    uint32_t m_nbConnectedClients;
};

} // namespace connection
} // namespace common
} // namespace server

#endif

