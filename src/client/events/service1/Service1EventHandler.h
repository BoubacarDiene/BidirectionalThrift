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

#ifndef Service1EventHandler_H
#define Service1EventHandler_H

#include "generated/Service1.h"
#include "generated/Service1Event.h"

#include "generated/shared_types.h"

#include "client/events/EventReceiver.h"

namespace client {
namespace events {
namespace service1 {

class Service1EventHandler : public generated::Service1EventIf,
                             public client::events::EventReceiver<generated::Service1EventProcessor,
                                                                  Service1EventHandler> {
public:
    Service1EventHandler(const uint32_t maxAcceptedFailures,
                         const apache::thrift::stdcxx::shared_ptr<apache::thrift::protocol::TProtocol>& protocol)
                         : EventReceiver(maxAcceptedFailures, this, protocol) {}

    void onSyncWorkResult(const generated::shared::Result& res);
    void onAsyncWorkResult(const generated::shared::Result& res);
};

} // namespace service1
} // namespace events
} // namespace client

#endif
