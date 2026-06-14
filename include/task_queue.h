#ifndef TASK_QUEUE
#define TASK_QUEUE

#include "parser.h"
#include "request.h"
#include <condition_variable>
#include <memory>
#include <queue>
#include <sys/socket.h>
#include <unordered_map>

#define NUM_OF_THREADS 10

namespace cerberus 
{
class TaskQueue 
{
public:
    using parser_map = std::unordered_map<int, std::unique_ptr<cerberus::HttpParser>>;

    // Constructors
    TaskQueue();
        
    void addToRequestQueue(const cerberus::Request request);    
    void addToFdQueue(const int fd);

    void createParserWorker(cerberus::TaskQueue::parser_map& map, const sockaddr_storage& recieved_connection);
    void createRequestWorker();

    void spinUpWorkerThreads(const int number_of_threads, cerberus::TaskQueue::parser_map& map, const sockaddr_storage& recieved_connection);

    void handleRequest(const Request& request);

private:
    std::queue<cerberus::Request> _request_queue;
    std::mutex _request_mutex;
    std::condition_variable _request_cv;

    std::queue<int> _fd_queue;
    std::mutex _fd_mutex;
    std::condition_variable _fd_cv;

    int _active_threads;
};
}

#endif // !TASK_QUEUE_H
