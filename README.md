# Minitalk
The purpose of this project is to code a small data exchange program using UNIX signals.
Minitalk is a simple inter-process communication project that allows two programs to communicate using signals in C. This project serves as an introduction to Unix signals and IPC (Inter-Process Communication) mechanisms.

## Features

- **Client-Server Architecture**: A client can send messages to a server using signals.
- **Signal Handling**: Utilizes Unix signals for communication between processes.
- **Dynamic Message Size**: Supports sending messages of arbitrary lengths.
- **Multi-client Support**: The server can handle multiple clients simultaneously.

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
