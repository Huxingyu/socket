# Project Documentation

This project is a simple client-server application written in C++.

## Functionality

The server program (`server.cpp` or `come.cpp`) listens for incoming connections on a specified port (8888). When a client connects, the server reads a message from the client, prints the message to the console, and then closes the connection.

The client program (`client.cpp`) connects to the server, sends a predefined message ("Hello, Server!"), and then closes the connection.

## Building and Running

To build the server and client, you can use a C++ compiler like g++.

**Server:**

```bash
g++ server.cpp -o server
./server
```

Alternatively, you can use `come.cpp` as the server:

```bash
g++ come.cpp -o come_server
./come_server
```

**Client:**

```bash
g++ client.cpp -o client
./client
```

First, start the server in one terminal window. Then, run the client in another terminal window. The server will print the message received from the client.

## Files

- **`server.cpp`**: The main server program. It listens for client connections, receives a message, and prints it.
- **`client.cpp`**: The client program. It connects to the server and sends a message.
- **`come.cpp`**: An alternative/very similar version of the server program.
- **`client_test.cpp`**: Contains unit tests for the client (Note: The actual content and nature of tests might need to be verified as they were not inspected).
- **`server_test.cpp`**: Contains unit tests for the server (Note: The actual content and nature of tests might need to be verified as they were not inspected).
- **`README.md`**: A brief introductory file for the project.
- **`.gitignore`**: Specifies intentionally untracked files that Git should ignore.
- **`DOCUMENTATION.md`**: This file, providing detailed documentation about the project.
