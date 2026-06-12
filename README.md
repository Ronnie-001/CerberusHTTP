# CerberusHTTP

A multithreaded HTTP/1.1 server built from scratch in C++20. No frameworks, no external HTTP libraries — just raw sockets, epoll, and threads.

<p align="center">
  <img src="assets/cerberus_logo.png" alt="CerberusHTTP Logo" width="500">
</p>

<h3 align="center">CerberusHTTP: A Multithreaded HTTP Server.</h3>

## Overview

CerberusHTTP is a from-scratch implementation of an HTTP/1.1 server using the POSIX sockets API. It handles concurrent connections through a thread pool backed by a task queue, and uses Linux's `epoll` for efficient I/O event notification. Incoming requests are fully parsed — start line, headers, and message body — then routed to the appropriate handler based on the HTTP method.

## Architecture

The server is organized into five core modules:

| Module | Description |
|---|---|
| **Server** (`src/server/`) | TCP listener using POSIX sockets and `epoll` for non-blocking I/O. Manages connections and delegates work to the thread pool. |
| **Parser** (`src/parser/`) | Parses raw HTTP requests into structured `Request` objects — extracting the method, path, version, headers, and optional JSON body. |
| **Thread Pool** (`src/thread_pool/`) | Worker thread pool with a synchronized task queue. Distributes incoming connections across threads using mutexes and condition variables. |
| **Router** (`src/router/`) | Routes parsed requests to handlers based on HTTP method (GET, POST, PUT, DELETE, etc.). Verifies that requested resources exist before processing. |
| **Utility** (`src/utility/`) | String helpers and Prometheus-based metrics (throughput, latency, saturation). |

### Request Lifecycle

```
Client ──► TCP Listener (epoll) ──► Thread Pool ──► HTTP Parser ──► Router ──► Handler
```

1. The TCP listener accepts a connection and registers it with epoll.
2. When data is ready, the connection is dispatched to a worker thread.
3. The parser reconstructs the full HTTP request (handling partial reads).
4. The router inspects the method and resource path, then calls the appropriate handler.

## Supported HTTP Methods

GET, PUT, POST, DELETE, PATCH, OPTIONS, HEAD, CONNECT, TRACE

## Dependencies

- **C++20** compiler (GCC or Clang)
- **CMake** 3.23+
- **Linux** (uses `epoll` and POSIX sockets)
- [simdjson](https://github.com/simdjson/simdjson) — fast JSON parsing (vendored in `include/simdjson/`)
- [nlohmann/json](https://github.com/nlohmann/json) — JSON serialization for data operations (vendored in `include/nlohmann/`)
- [prometheus-cpp](https://github.com/jupp0r/prometheus-cpp) — metrics exposition (headers vendored in `include/prometheus/`)

## Building

```bash
mkdir build && cd build
cmake ..
make
```

This produces a `Server` executable in the build directory.

## Running

```bash
./Server
```

The server binds to a local address and begins listening for incoming HTTP connections.

## Project Structure

```
CerberusHTTP/
├── main.cpp
├── CMakeLists.txt
├── include/
│   ├── tcp.h            # TCP listener
│   ├── parser.h         # HTTP request parser
│   ├── request.h        # Request struct
│   ├── constants.h      # HTTP methods and status codes
│   ├── task_queue.h     # Thread pool and task queue
│   ├── router.h         # Request routing
│   ├── data.h           # JSON data operations
│   ├── metrics.h        # Prometheus metrics
│   ├── m_strings.h      # String utilities
│   ├── nlohmann/        # JSON library (vendored)
│   ├── simdjson/        # simdjson library (vendored)
│   └── prometheus/      # Prometheus client (vendored)
└── src/
    ├── server/          # TCP and epoll implementation
    ├── parser/          # HTTP parsing logic
    ├── thread_pool/     # Worker threads and task queue
    ├── router/          # Routing and data handlers
    └── utility/         # Metrics and string helpers
```

## Status

This project is under active development. The current focus is on HTTP request parsing within worker threads and building out the routing layer.

## License

See [LICENSE](LICENSE) for details.
