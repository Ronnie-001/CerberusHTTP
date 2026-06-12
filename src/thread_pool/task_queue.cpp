#include <mutex>
#include <sys/socket.h>
#include <thread>
#include <unordered_map>
#include <iostream>

#include "task_queue.h"
#include "tcp.h"

cerberus::TaskQueue::TaskQueue() {}

void cerberus::TaskQueue::addToRequestQueue(const cerberus::Request& request) 
{
    _request_queue.push(request);
}

void cerberus::TaskQueue::createWorker(cerberus::TaskQueue::parser_map map, const sockaddr_storage& recieved_connection)  
{
    cerberus::Request request;
    int fd;
    
    while (true) {
        // Use nested scope for RAII
        // Step 1, parse the request
        {
            std::unique_lock<std::mutex> lock(_fd_mutex);
            _request_cv.wait(lock, [&](){ return !_fd_queue.empty(); });

            fd = _fd_queue.front(); _fd_queue.pop();
            
            // TODO: Finish implementataion; handle the appending of data
            // when data sent through socket accociated with the fd.
            cerberus::HttpParser* parser = map[fd].get();
            std::string data = cerberus::TcpListener::readData(fd, recieved_connection, map); 

            parser->appendData(data);

            if (parser->isRequestComplete()) {
                cerberus::TcpListener::parseHttpRequest(parser);
                
                cerberus::Request req = parser->constructRequest();
                _request_queue.push(req);
            }
        }
        // Step 2, grab the request
        {
            std::unique_lock<std::mutex> lock(_request_mutex);
            _fd_cv.wait(lock, [&](){ return !_request_queue.empty(); });

            request = _request_queue.front(); _request_queue.pop();
        }  
        
        handleRequest(request);
    }
}

void cerberus::TaskQueue::spinUpWorkerThreads(const int number_of_threads)
{
    for (std::size_t i = 0; i < number_of_threads; ++i) {
        // TODO: Add the parameters!!!
        std::jthread(createWorker());
    }
}

// TODO: Implement the handleRequest method.
void cerberus::TaskQueue::handleRequest(const Request& request) 
{
    _active_threads++;
    std::cout << "Got to the handleRequest() method!" << '\n';
}
