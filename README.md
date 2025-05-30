# AP_Messenger_Project

## Overview

Welcome! This project is a C++-backed and Qt-fronted messenger application developed for the Advanced Programming Course at IUT (Spring 2023). The codebase demonstrates the use of several advanced programming concepts and design patterns, aiming to provide a scalable, maintainable, and feature-rich messaging experience.

## Notable Features & Technologies

- **C++** (core logic, object-oriented design)
- **Qt Framework** (cross-platform GUI and networking)
- **QMake** (build configuration)
- **Multithreading** (using QtConcurrent and QThreadPool)
- **DTO/CRUD Repository Pattern** (clean data handling for chats, groups, and channels)
- **Polymorphism & Inheritance** (flexible, reusable code structure)
- **Custom Exception Handling** (robust error management)
- **File Handling in JSON** (structured, portable data storage)
- **Consistent naming and comprehensive code comments**

## Code Structure & Architecture

- **DTOs (Data Transfer Objects):** Channels, Groups, PV (private chats) inherit from a common DTO parent class.
- **Repositories:** Each data type (Channel, Group, PV) has its repository managing CRUD operations, leveraging the DTO pattern.
- **UI Layer:** Built with Qt Widgets. Major screens include Login, Signup, Main Window, and Logged-in Page.
- **Client:** Handles authentication, user session, and interaction with repositories.
- **ExceptionHandler:** Centralized class for robust error handling.
- **Multithreading:** Asynchronous updates for chat and message lists using QtConcurrent and QThreadPool for responsiveness.

## Key Design Patterns

- **DTO/Repository:** Separation of concerns and scalability in data handling.
- **Abstract OOP:** Abstract classes/interfaces for shared behaviors, aiding extensibility and maintainability.
- **Polymorphism:** Treat different chat/group/channel objects uniformly.
- **Custom Exception Handling:** Graceful UI error reporting and debugging.

## Installation & Usage

There are two ways to install and run the project:

### 1. Pre-built Installer (Windows)
- Download the installer from the releases section (if provided).
- Run the installer, which will set up dependencies and shortcuts automatically.

### 2. Manual Build

**Prerequisites:**
- Qt (with qmake and Qt Creator)
- C++17 compatible compiler

**Steps:**
1. Clone or download this repository.
2. Install Qt and ensure qmake is in your PATH.
3. Open a terminal in the project directory.
4. Generate Makefile:
    ```sh
    qmake AP_Messenger_Project.pro
    ```
5. Build the project:
    ```sh
    make debug
    ```
6. Run the executable from the build directory:
    ```sh
    ./build/MyProject
    ```
7. Alternatively, open the `.pro` file in Qt Creator, select your compiler, configure, and run.

*Note:* Commands and folders may vary based on your OS and Qt setup.

## Example Usage

The UI consists of:
- **Login/Signup Pages:** For authentication
- **Main Window:** After login, shows chats, channels, and groups
- **Logged-in Page:** Real-time updates of messages and user activity, powered by multithreading

![Screenshot](https://github.com/Kebabist/Messenger_C--_1/assets/83098161/8430d607-f2c5-48de-9e24-c8d42e7e79b8)
*(Add more screenshots or GIFs to showcase main features and flows)*

## Contribution Guidelines

- Fork the repository and create feature branches for new contributions.
- Write clear, concise commit messages and document your code.
- Follow the project’s consistent naming conventions and coding style.
- Add comments and, if possible, unit tests for new features.
- Submit pull requests for review.

*(Consider adding a CONTRIBUTING.md file for detailed guidelines)*

## License

This project is licensed under the GPL license. See the [LICENSE](https://github.com/Kebabist/Messenger_C--_1/blob/main/LICENSE) file for details.

## Acknowledgements

- Developed for Advanced Programming @ IUT.ac, Spring 2023.
