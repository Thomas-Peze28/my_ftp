# MyFTP

MyFTP is a File Transfer Protocol (FTP) server implementation written in C. It handles multiple concurrent TCP connections and implements a subset of the RFC 959 FTP standard.

## Features

- **Concurrent Connections**: Handles multiple clients simultaneously using I/O multiplexing.
- **Anonymous Login**: Supports anonymous authentication.
- **Data Transfer**: Implements Passive (PASV) mode for data transfers (e.g., directory listings).
- **Graceful Error Handling**: Responds with standard FTP status codes.

## Supported Commands

The server currently implements the following FTP commands:
- `USER` : Specify the username for authentication.
- `PASS` : Specify the password for authentication.
- `CWD`  : Change working directory.
- `CDUP` : Change to the parent directory.
- `QUIT` : Disconnect from the server.
- `DELE` : Delete a file on the server.
- `PWD`  : Print the current working directory.
- `PASV` : Enter passive mode.
- `LIST` : List files in the current directory.
- `RETR` : Download file from server to client.
- `STOR` : Upload file from client to server.
- `HELP` : Display helpful information about the server.
- `NOOP` : No operation (keeps the connection alive).

## Prerequisites

- GCC or any standard C compiler
- GNU Make

## Compilation

To compile the project and generate the `myftp` executable, run:

```bash
make
```

To clean up the compiled object files:

```bash
make clean
```

To remove the executable and all object files:

```bash
make fclean
```

To force a full recompilation:

```bash
make re
```

## Usage

Start the server by providing a port number and the path to the root directory for the FTP server:

```bash
./myftp <port> <path>
```

- `<port>`: The port number on which the server will listen for incoming connections.
- `<path>`: The absolute or relative path to the directory that will act as the root (`/`) for the FTP clients.

### Example

```bash
./myftp 8080 /home/anonymous
```

Once the server is running, you can connect to it using any standard FTP client:
```bash
ftp localhost 8080
```
(Login as `Anonymous` with an empty password).
