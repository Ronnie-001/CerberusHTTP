#include <netdb.h>


class Server {

private:
    int _status;
    
    // member variables to hold the socket file descriptors 
    int _sock_fd;
    int _bind_fd;
    int _listen_fd;
    int _accept_fd;

    struct addrinfo _hints;
    struct addrinfo* _servinfo;
    struct addrinfo* _ptr;

public:
    // Constructor
    Server() {}
    
    // Destructor
    ~Server() {}
};
