# Project Documentation

This project is a simple client-server application written in C++.

## Functionality

The server program (`server.cpp`) listens for incoming connections on a specified port (8888). It now handles multiple clients iteratively: after a client disconnects, the server waits for a new connection. When a client connects, the server reads a message from the client, prints the message to the console, and then closes that specific client's connection. Error handling has been significantly improved in the server to ensure it continues running even if individual client connections have issues.

The client program (`client.cpp`) connects to the server, sends a predefined message ("Hello, Server!"), and then closes the connection. Error handling has also been improved in the client to provide more robust operation.

## Building and Running

To build the server and client, you can use a C++ compiler like g++.

**Main Server:**

```bash
g++ server.cpp -o server
./server
```

**Main Client:**

```bash
g++ client.cpp -o client
./client
```

First, start the server in one terminal window. Then, run the client in another terminal window. The server will print the message received from the client. The server will continue running to accept further client connections.

### Test Programs

For more specific testing scenarios, the following test programs are available:

**Advanced Client (connects to any specified server):**

```bash
g++ advanced_client.cpp -o advanced_client
./advanced_client <server_ip> <port>
# Example:
# ./advanced_client 127.0.0.1 8888 
```
This client sends the message "gogogo" to the specified server and port.

**Simple Server Test (handles one client and exits):**

```bash
g++ simple_server_test.cpp -o simple_server_test
./simple_server_test
```
This server listens on port 8888, accepts one connection, prints the received message, and then exits. It is useful for basic, one-shot client tests.

## Files

- **`server.cpp`**: The main server program. It listens for client connections on port 8888, handles multiple clients iteratively, receives a message from each, and prints it. Features improved error handling for robust operation.
- **`client.cpp`**: The client program. It connects to the server and sends a message. Features improved error handling.
- **`advanced_client.cpp`**: A test client program that takes the server IP address and port number as command-line arguments. It connects to the specified server, sends the message "gogogo", and then exits. Features improved error handling.
- **`simple_server_test.cpp`**: A basic test server program. It listens on port 8888, handles a single client connection, prints the received message to the console, and then exits. Useful for simple, one-shot client testing. Features improved error handling.
- **`README.md`**: A brief introductory file for the project.
- **`.gitignore`**: Specifies intentionally untracked files that Git should ignore.
- **`DOCUMENTATION.md`**: This file, providing detailed documentation about the project.
