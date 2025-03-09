# Interprocess Communication System

This project implements an interprocess communication system using multiple components (`brain`, `ear`, `mouth`, and `launcher`) to facilitate message passing between different processes. It uses **UDP sockets** and **file-based communication** to simulate a distributed message handling system.

## Components

### 1. `brain.c`
- Reads messages from a file (`_eb.txt` and `_lb.txt`).
- Writes messages to `_mb.txt`.
- Acts as the main processing unit of the system.

### 2. `ear.c`
- Listens for incoming UDP messages on a specified port.
- Writes received messages to the `_eb.txt` file.

### 3. `mouth.c`
- Reads messages from `_mb.txt` and sends them over a UDP socket.
- Extracts port numbers from the message for routing.

### 4. `launcher.c`
- Reads configurations from a file (e.g., `config1`, `config2`).
- Starts `brain`, `ear`, and `mouth` as child processes using `fork()`.
- Provides a simple UI for sending messages.

### 5. `multiple_system_launcher.c`
- Launches multiple instances of `launcher` in separate terminal windows.

---

## Build Instructions

This project uses `Makefile` to automate the compilation process.

### Build All Components
```sh
make
```

### Clean Build Files
```sh
make clean
```

---

## Running the Project

### 1. Start the System
```sh
./multiple_system_launcher
```
This will open multiple terminal windows running `launcher` with different configurations.

### 2. Sending Messages
- Follow the UI prompts in the `launcher` terminal to send messages.
- Messages will be received and processed accordingly.

### 3. Stopping the System
- Close all open terminals running `launcher`.
- Run `make clean` to remove generated binaries and text files.

---

## File Naming Convention
Each process instance uses specific files for message storage:
- `<ID>_eb.txt` → Incoming messages.
- `<ID>_lb.txt` → Messages to be sent.
- `<ID>_mb.txt` → Processed messages.

Each component reads/writes these files accordingly to simulate interprocess communication.

---

## Dependencies
- **GCC Compiler** (`sudo apt install build-essential` on Ubuntu)
- **GNU Make** (`sudo apt install make` on Ubuntu)
- **Gnome Terminal** (default on most Ubuntu systems)
- **Linux-based OS** (Tested on Ubuntu)

---

## Notes
- Ensure all `configX` files exist before running `launcher`.
- The project is designed to work on **Linux** and may require modifications for Windows.

---

## Author
Developed by Shashi Ranjan Kumar..


