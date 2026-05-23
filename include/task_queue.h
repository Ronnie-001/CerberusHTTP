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
            std::queue<cerberus::HttpParser*> _requests_queue;

            std::condition_variable _cv;
            std::mutex _mutex;
            int _number_of_running_tasks;

        public:

            TaskQueue();
            TaskQueue(const TaskQueue& tq) = delete;
            
            void createWorker(const int fd);

            void handleRequest(const Request& request);
    };
}

#endif // !TASK_QUEUE_H
