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

#ifndef ServiceCreator_H
#define ServiceCreator_H

#include <iterator>
#include <string>

#include <thrift/processor/TMultiplexedProcessor.h>
#include <thrift/stdcxx.h>

#include "server/common/connection/ConnectionWatcher.h"

namespace server {
namespace services {

class ServiceCreator {
public:
    ServiceCreator() : m_multiplexedProcessor(
                           apache::thrift::stdcxx::make_shared<apache::thrift::TMultiplexedProcessor>()) {}

    template <typename H, typename P> void addService(const std::string& serviceName) {
        m_services[serviceName] = new H;
        m_multiplexedProcessor->registerProcessor(
            serviceName,
            apache::thrift::stdcxx::shared_ptr<apache::thrift::TProcessor>(
                new P(
                    apache::thrift::stdcxx::shared_ptr<H>(
                        static_cast<H*>(m_services[serviceName])
                    )
                )
            )
        );
    }

    void removeServices() {
        std::map<std::string, server::common::connection::ConnectionWatcherBase*>::iterator it;
        for (it = m_services.begin(); it != m_services.end(); ++it) {
            delete it->second;
        }
    }

    std::map<std::string, server::common::connection::ConnectionWatcherBase*>& getServices() {
        return m_services;
    }

    apache::thrift::stdcxx::shared_ptr<apache::thrift::TMultiplexedProcessor>& getProcessor() {
        return m_multiplexedProcessor;
    }

private:
    std::map<std::string, server::common::connection::ConnectionWatcherBase*> m_services;
    apache::thrift::stdcxx::shared_ptr<apache::thrift::TMultiplexedProcessor> m_multiplexedProcessor;
};

} // namespace services
} // namespace server

#endif

