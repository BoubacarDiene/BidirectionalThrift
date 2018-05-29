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

#ifndef EventReceiver_H
#define EventReceiver_H

#include <iostream>
#include <thread>

#include <thrift/protocol/TProtocol.h>
#include <thrift/Thrift.h>

namespace client {
namespace events {

template <typename P, typename H> // Processor, Handler
class EventReceiver {
public:
    EventReceiver(const uint32_t maxAcceptedFailures, H *obj,
                  const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol) {

        m_task = new std::thread([maxAcceptedFailures, protocol, obj]() {
            apache::thrift::stdcxx::scoped_ptr<P> procMsgFromServer(
                new P(apache::thrift::stdcxx::shared_ptr<H>(obj)));

            int cnt = maxAcceptedFailures;
            while (cnt > 0) {
              try {
                while (procMsgFromServer->process(protocol, protocol, nullptr));
              } catch (apache::thrift::TException& e) {
                std::cout << "process() failed: " << e.what() << std::endl;
                --cnt;
              }
            }
        });
    }

    virtual ~EventReceiver() {
        delete m_task;
    }

    void waitTask(bool wait) {
        if (wait)
            m_task->join();
        else
            m_task->detach();
    }

private:
    std::thread *m_task;
};

} // namespace events
} // namespace client

#endif
