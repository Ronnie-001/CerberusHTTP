#ifndef TASK_QUEUE
#define TASK_QUEUE

#include "parser.h"
#include "request.h"
#include <condition_variable>
#include <queue>

#define NUM_OF_THREADS 10

namespace cerberus 
{
class TaskQueue 
{
public:
    // Constructors
    TaskQueue();
        
    void addToRequestQueue(const cerberus::Request& request);    
    void addToFdQueue(const int fd);

    void createWorker();

    void spinUpWorkerThreads(const int number_of_threads);

    void handleRequest(const Request& request);

private:
    std::queue<cerberus::Request> _request_queue;
    std::mutex _request_mutex;

    std::queue<int> _fd_queue;
    std::mutex _fd_mutex;

    std::condition_variable _cv;
    int _active_threads;
};
}

#endif // !TASK_QUEUE_H
