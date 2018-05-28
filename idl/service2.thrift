namespace cpp generated

include "shared.thrift"

service Service2
{
    oneway void doSyncWork(1:shared.Request req)         // Result expected
    oneway void doAsyncWork(1:shared.Request req)        // Result expected
    oneway void doSyncNoResultWork(1:shared.Request req) // Result not expected => No eventHandler required!
}

service Service2Event {
    oneway void onSyncWorkResult(1:shared.Result res)  // Send result of doWork_1 to client
    oneway void onAsyncWorkResult(1:shared.Result res) // Send result of doWork_2 to client
}
