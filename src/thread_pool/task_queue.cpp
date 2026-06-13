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
    std::unique_lock<std::mutex> lock(_request_mutex);
    _request_queue.push(request);
    _request_cv.notify_one();
}

void cerberus::TaskQueue::addToFdQueue(const int fd) 
{
    std::unique_lock<std::mutex> lock(_fd_mutex);
    _fd_queue.push(fd);
    _fd_cv.notify_one();
}

void cerberus::TaskQueue::createWorker(cerberus::TaskQueue::parser_map& map, const sockaddr_storage& recieved_connection)  
{
    cerberus::Request request;
    int fd;
    
    std::cout << "[LOGS] Worker thread created." << '\n';
    
    while (true) {
        // Use nested scope for RAII
        // Step 1, parse the request
        {
            std::unique_lock<std::mutex> lock(_fd_mutex);
            _fd_cv.wait(lock, [&](){ return !_fd_queue.empty(); });

            std::cout << "[LOGS] Aqquired mutex" << '\n';
            fd = _fd_queue.front(); _fd_queue.pop();
            lock.unlock();

            std::cout << "[LOGS] file descriptor in thread: " << fd << '\n';
            
            // TODO: Finish implementataion; handle the appending of data
            // when data sent through socket accociated with the fd.
            cerberus::HttpParser* parser = map[fd].get();
            std::string data = cerberus::TcpListener::readData(fd, recieved_connection, map); 

            std::cout << data << '\n';

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
            _request_cv.wait(lock, [&](){ return !_request_queue.empty(); });

            request = _request_queue.front(); _request_queue.pop();
            
            std::cout << "[LOGS] WORKING!";
        }  
        
        handleRequest(request);
    }
}

void cerberus::TaskQueue::spinUpWorkerThreads(const int number_of_threads, cerberus::TaskQueue::parser_map& map, const sockaddr_storage& recieved_connection)
{
    for (std::size_t i = 0; i < number_of_threads; ++i) {
        std::jthread thread(&cerberus::TaskQueue::createWorker, this, std::ref(map), std::ref(recieved_connection));
        thread.detach();
    }

    std::cout << "[LOGS] Spun up the worker threads." << '\n';
}

// TODO: Implement the handleRequest method.
void cerberus::TaskQueue::handleRequest(const Request& request) 
{
    _active_threads++;
    std::cout << "Got to the handleRequest() method!" << '\n';
}
