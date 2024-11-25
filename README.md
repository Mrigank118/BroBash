# BroBash Terminal

**BroBash** is a custom terminal application developed using C++ and GTK, designed to manage various data structures such as strings, linked lists, hash tables, trees, queues, and stacks. This terminal features a playful and unique command language that allows users to execute commands in an intuitive and humorous way, making the process of learning about terminal systems and data structures more engaging.

## Project Overview

The BroBash terminal is a command-line interface (CLI) that functions similarly to a traditional shell, with added custom functionality for managing files, directories, and processes. The application also provides a learning environment for understanding how terminals work at the core level, especially in the context of operating systems.

### Key Features:
- **Custom Commands**: Unique commands designed for file operations, directory management, and command history.
- **Data Structure Integration**: Uses linked lists, stacks, queues, trees, and hash tables to handle command parsing, process scheduling, and file operations.
- **GTK-Based UI**: A user-friendly graphical interface built with GTK.
- **Process Management**: Simulates process scheduling and file handling to replicate basic operating system functions.
- **Command History**: Track and navigate through previous commands.

## Commands List

1. `banao <filename>` – Create a new file.
2. `mitao <filename>` – Delete a file.
3. `padh <filename>` – Read (view) the contents of a file.
4. `likh <filename> <content>` – Write content to a file.
5. `dikhao` – List files and directories in the current directory.
6. `banaoDir <dirname>` – Create a new directory.
7. `chalo <dirName>` – Change to a specified directory.
8. `wapas` – Go back to the previous directory.
9. `jaane <filename>` – Display file metadata (size, modified time).
10. `khojo <filename>` – Search for a file in the directory.
11. `dhoondo <filename> <pattern>` – Search for a pattern in a file.
12. `itihas` – Show command history with usage statistics.

## Data Structures Used

- **Linked List**: Manages command history for easy navigation between past commands.
- **Hash Table**: Stores file metadata and command usage statistics.
- **Tree**: Used for representing the directory structure and managing file system navigation.
- **Stack**: Implements navigation within directories and supports the `khojo` command.
- **Queue**: Helps with managing file operations in sequence.

## Code Structure

- **LinkedList**: Handles command history with methods to add, retrieve, and navigate commands.
- **HashTable**: Stores file metadata and tracks command usage.
- **DirectoryTree**: Manages the directory structure and implements methods for navigation and file operations.

## Installation

### Prerequisites:
- **Operating System**: Linux-based (Ubuntu recommended)
- **Language**: C++
- **Libraries**: GTK 3/4, Standard C++ Library
- **Dependencies**: `libgtk-3-dev`, `g++`, `make/CMake`

### Installation Steps:
1: Fork the Repository
2. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/brobash.git
   cd brobash

### Screenshot: 
![Terminal Image](/images/terminal.png)

## Collaborators
[![Mrigank118](https://img.shields.io/badge/Mrigank118-6DA55F?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Mrigank118)
[![Jainritikaa](https://img.shields.io/badge/Jainritikaa-6DA55F?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Jainritikaa)
