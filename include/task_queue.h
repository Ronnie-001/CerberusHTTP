#ifndef TASK_QUEUE
#define TASK_QUEUE

#include "parser.h"
#include <condition_variable>
#include <queue>

namespace cerberus 
{
class TaskQueue 
{
    private:
        std::queue<cerberus::Request> _queue;

        std::condition_variable _cv;
        std::mutex _mutex;
        int _number_of_running_tasks;

    public:
        // Constructors
        TaskQueue();
        
        void createWorker(const cerberus::HttpParser& parser);

        void handleRequest(const Request& request);
};
}

#endif // !TASK_QUEUE_H
