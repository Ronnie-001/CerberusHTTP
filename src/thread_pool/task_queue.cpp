#include "task_queue.h"
#include "parser.h"
#include <mutex>

cerberus::TaskQueue::TaskQueue() {}

void cerberus::TaskQueue::createWorker(const cerberus::HttpParser& parser)  
{
    cerberus::Request request;
    
    while (true) {
        // Use nested scope for RAII
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _cv.wait(lock, [&]{return !_queue.empty(); });

            // Grab the request
            request = _queue.front(); _queue.pop();
        }  
        
        handleRequest(request);
    }
}
