# BroBash Terminal

**BroBash** is a custom terminal application developed using **C++** and **GTK**, designed to make learning about terminal systems and data structures both educational and engaging. With its playful command language and innovative features, BroBash offers a unique environment for managing files, directories, and processes.



## Project Overview

BroBash replicates a traditional shell with added custom functionality, focusing on **data structure integration** and an intuitive command set. It also serves as a tool to understand how terminals operate at a fundamental level, particularly in relation to operating systems.

### Key Features

- **Custom Commands**: A set of unique commands for file operations, directory management, and navigating command history.
- **Data Structure Integration**: Incorporates linked lists, stacks, queues, trees, and hash tables for efficient management of commands, files, and processes.
- **GTK-Based UI**: A user-friendly graphical interface built with GTK.
- **Process Management**: Simulates basic operating system functionalities like process scheduling and file handling.
- **Command History**: Tracks and navigates through previously executed commands.



## Commands List

| Command                  | Description                                               |
|--------------------------|-----------------------------------------------------------|
| `banao <filename>`       | Create a new file.                                        |
| `mitao <filename>`       | Delete a file.                                            |
| `padh <filename>`        | View the contents of a file.                              |
| `likh <filename> <content>` | Write content to a file.                                |
| `dikhao`                 | List files and directories in the current directory.      |
| `banaoDir <dirname>`     | Create a new directory.                                   |
| `chalo <dirname>`        | Change to the specified directory.                        |
| `wapas`                  | Go back to the previous directory.                        |
| `jaane <filename>`       | Display file metadata, such as size and last modified time. |
| `khojo <filename>`       | Search for a file in the directory.                       |
| `dhoondo <filename> <pattern>` | Search for a specific pattern within a file.         |
| `itihas`                 | Display command history with usage statistics.            |


## Data Structures Used

- **Linked List**: Manages command history for easy navigation of past commands.
- **Hash Table**: Stores file metadata and tracks command usage statistics.
- **Tree**: Represents the directory structure and manages file system navigation.
- **Stack**: Implements directory navigation and supports the `khojo` command.
- **Queue**: Handles sequential file operations.



## Code Structure

- **LinkedList**: Handles command history with methods to add, retrieve, and navigate commands.
- **HashTable**: Stores file metadata and tracks command usage.
- **DirectoryTree**: Manages the directory structure and supports file operations.



## Prerequisites

- **Operating System**: Linux-based (Ubuntu recommended)
- **Language**: C++
- **Libraries**: GTK 3/4, Standard C++ Library
- **Dependencies**: `libgtk-3-dev`, `g++`, `make/CMake`



## Installation Steps

1. Fork the repository.
2. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/brobash.git
   cd brobash
3. run command 'make'
4. run command ./build/Brobash


### Screenshot: 
![Terminal Image](/images/terminal.png)

## Collaborators
[![Mrigank118](https://img.shields.io/badge/Mrigank118-6DA55F?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Mrigank118)
[![Jainritikaa](https://img.shields.io/badge/Jainritikaa-6DA55F?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Jainritikaa)
