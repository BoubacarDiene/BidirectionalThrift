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

#ifndef Service2Handler_H
#define Service2Handler_H

#include "generated/Service2.h"
#include "generated/Service2Event.h"

#include "server/common/connection/ConnectionWatcher.h"

namespace server {
namespace services {
namespace service2 {

class Service2Handler : public generated::Service2If,
                        public server::common::connection::ConnectionWatcher<generated::Service2EventClient> {
public:
    virtual ~Service2Handler() {}

    void doSyncWork(const generated::shared::Request& req);
    void doAsyncWork(const generated::shared::Request& req);
    void doSyncNoResultWork(const generated::shared::Request& req);
};

} // namespace service2
} // namespace services
} // namespace server

#endif
