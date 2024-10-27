# Minitalk
The purpose of this project is to code a small data exchange program using UNIX signals.
Minitalk is a simple inter-process communication project that allows two programs to communicate using signals in C. This project serves as an introduction to Unix signals and IPC (Inter-Process Communication) mechanisms.

## Table of Contents

- [Features](#features)
- [Bonus Features](#bonus-features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Example](#example)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Client-Server Architecture**: A client can send messages to a server using signals.
- **Signal Handling**: Utilizes Unix signals for communication between processes.
- **Dynamic Message Size**: Supports sending messages of arbitrary lengths.
- **Multi-client Support**: The server can handle multiple clients simultaneously.

## Bonus Features

- **Message Acknowledgment**: The server sends an acknowledgment back to the client upon receiving a message.
- **Error Handling**: Improved error handling to manage failed signal transmissions and invalid inputs.
- **Logging**: Option to log messages sent and received for debugging purposes.
- **Custom Signal**: Ability to configure custom signals for message transmission, enhancing flexibility.

## Requirements

- C compiler (GCC)
- Make
- Unix-based operating system (Linux or macOS)

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/Miami05/minitalk.git
   ```
   ```
   cd minitalk
   ```

### Compile the project using Make:

    ```bash
    make
    ```

1. This will generate two executables: server and client

## Usage

### Starting the Server

Open a terminal and run the server:

    ```bash
    ./server
    ```
### Running the Client

In another terminal, run the client by providing the server's PID and the message to send:

    ```bash
    ./client <PID> "your_message_here"
    ```
1. Replace <PID> with the server process ID, which is displayed in the terminal where the server is running.

## Example

1. Start the server:

    ```bash
    ./server
    
2. Get the server PID (displayed in the terminal).

3. Send a message from the client:

    ```bash
    ./client <PID> "Hello, Server!"

## Contributing

Contributions are welcome! If you would like to enhance the project or fix bugs, please fork the repository and submit a pull request. Ensure that your code adheres to the project's coding standards and includes relevant tests.

## License

This project is licensed under the MIT License. See the LICENSE file for details.