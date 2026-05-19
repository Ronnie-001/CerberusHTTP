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
            std::queue<cerberus::HttpParser*> requests_queue;

            std::condition_variable cv;
            std::mutex mutex;

        public:

            TaskQueue();
            
            void createWorker(const int fd);
    };
}

#endif // !TASK_QUEUE_H
