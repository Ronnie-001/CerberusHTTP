#ifndef TASK_QUEUE
#define TASK_QUEUE

#include <condition_variable>
#include <memory>
#include <queue>
#include <sys/socket.h>
#include <unordered_map>

#include "metrics.h"
#include "parser.h"
#include "request.h"
#include "router.h"

#define NUM_OF_THREADS 10

namespace cerberus 
{
class TaskQueue 
{
public:
    using parser_map = std::unordered_map<int, std::unique_ptr<cerberus::HttpParser>>;

    // Constructors
    TaskQueue(cerberus::Metrics& metrics);
        
    void addToRequestQueue(const cerberus::Request request);    
    void addToFdQueue(const int fd);

    void createParserWorker(cerberus::TaskQueue::parser_map& map, const sockaddr_storage& recieved_connection,
                            cerberus::Data& data);

    void createRequestWorker(cerberus::Router& router, cerberus::Data& data);

    void spinUpWorkerThreads(const int number_of_threads, cerberus::TaskQueue::parser_map& map, 
                             const sockaddr_storage& recieved_connection, cerberus::Router& router,
                             cerberus::Data& data);

    void handleRequest(cerberus::Router& router, const cerberus::Request& request, cerberus::Data& data);

private:
    std::queue<cerberus::Request> _request_queue;
    std::mutex _request_mutex;
    std::condition_variable _request_cv;

    std::queue<int> _fd_queue;
    std::mutex _fd_mutex;
    std::condition_variable _fd_cv;

    cerberus::Metrics& _metrics;
};
}

#endif // !TASK_QUEUE_H
