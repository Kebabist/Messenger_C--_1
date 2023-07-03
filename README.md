# AP_Messenger_Project

# Overview:

Welcome Friends, This is a C++ backed and Qt fronted project that aims to provide users with a seamless and intuitive messaging experience. Our project caters to individuals seeking a reliable and efficient messaging platform, and it does so through the use of different design patterns and programming concepts.

# Design Patterns and Programming Concepts:

Our project boasts a range of design patterns and programming concepts, including DTO_CRUD, Repository design, Polymorphism and Inheritance, Exception Handling, Multithreading, File Handling in JSON format, and Reusability of code.

## A. DTO_CRUD Repository Design:
Our project uses DTO_CRUD Repository Design to handle private chats groups and channels and their respective data. This design pattern ensures that the data is handled in a secure and organized manner.Here are Some Advantages of this Design Pattern:

1. Separation of concerns: By using DTOs to transfer data between layers of the application, you can separate concerns between the data layer and the business logic layer. This allows you to keep your business logic independent of the underlying data model, making it easier to maintain and test.

2. Scalability: By keeping your data access code in a separate repository, you can easily scale your application horizontally by adding more instances of the data access layer. This can help you handle increased traffic and load as your application grows.

3. Flexibility: Using DTOs allows you to easily change the data model without affecting the business logic layer. This means you can make changes to the database schema or switch to a different database technology without having to modify your business logic code.

4. Testability: The use of DTOs makes it easier to test your business logic by allowing you to mock the data access layer. This can help you write more robust and reliable unit tests.

5. Security: By using DTOs to transfer data between layers, you can ensure that sensitive data is not exposed to unauthorized users or processes. This can help you maintain the security and integrity of your application's data.

![image](https://github.com/Kebabist/Messenger_C--_1/assets/83098161/40319308-214c-4451-b849-060d11f2ca80)

Overall, the use of DTO CRUD repo concept can help you build more scalable, flexible, and maintainable applications by separating concerns between the data layer and the business logic layer.

## B. Abstract OOP:
Our project also employs Abstract OOP paradigm that emphasizes the use of abstract classes and interfaces to define common behavior and properties that can be shared by multiple objects. This design pattern ensures that our data is stored and retrieved in a manner that is efficient and reliable. Here are some advantages of using abstract OOP programming:

1. Code reusability: Abstract classes and interfaces can be used to define common behavior and properties that can be shared by multiple objects. This can save time and effort by reducing the amount of code that needs to be written.

2. Polymorphism: Abstract classes and interfaces can be used to define polymorphic behavior, which allows objects of different types to be treated as if they were of the same type. This can make code more flexible and adaptable.

3. Encapsulation: Abstract classes and interfaces can be used to encapsulate implementation details, making it easier to change the implementation without affecting the rest of the code.

4. Separation of concerns: Abstract classes and interfaces can be used to separate concerns between different parts of the code, making it easier to maintain and test.

5. Abstraction: Abstract classes and interfaces can be used to abstract away implementation details, making it easier to think about the problem at a higher level of abstraction.

6. Design for extension: Abstract classes and interfaces can be used to design for extension, allowing new functionality to be added to the system without breaking existing code.

Overall, abstract OOP programming can help you write more modular, maintainable, and flexible code by emphasizing abstraction, polymorphism, and encapsulation. By using these concepts, you can create code that is easier to understand, extend, and maintain over time.

## C. Polymorphism and Inheritance:
We have implemented polymorphism and inheritance between the DTO parent class and the private chats groups and channels classes, which inherit from DTO. This ensures that our code is modular and flexible, allowing for easy expansion and modification. Here are some advantages of using these concepts:

1. Code reusability: Inheritance allows you to reuse code by creating classes that inherit properties and methods from a parent class.

2. Reduced code duplication: By using inheritance, you can avoid duplicating code and instead reuse code from a parent class.

3. Improved code organization: Inheritance can help you organize your code by creating a hierarchy of classes that share common properties and methods.

4. Easy maintenance: Inheritance can make code easier to maintain by reducing the amount of code duplication and allowing for more modular code.

5. Polymorphism: Inheritance is often used in conjunction with polymorphism, allowing for more flexible and adaptable code.

Overall, both polymorphism and inheritance can help you write more modular, maintainable, and flexible code. However, it's important to use these concepts judiciously and not overuse them, as they can also make code more complex and harder to understand if not used properly.

## D. Custom Exception Handler Class:
We have implemented a custom exception handler class, which ensures that our project is robust and error-free. This class allows us to handle exceptions in a manner that is both graceful and informative.Here are some advantages:

1. Improved error handling: A custom exception handler class can provide more detailed and specific error messages than the default exception handling mechanism. This can make it easier to identify and diagnose problems in the code.

2. Consistent error handling: A custom exception handler class can provide a consistent approach to error handling across the entire application, making it easier to maintain and debug the code.

3. Customized error handling: A custom exception handler class can be tailored to the specific needs of the application, allowing for more customized error handling. For example, you can define different types of exceptions for different error scenarios, or log errors to a specific location or format.

4. Better separation of concerns: A custom exception handler class can help to separate the error handling logic from the rest of the code, making it easier to maintain and test.

5. Enhanced error reporting: A custom exception handler class can provide enhanced error reporting features, such as sending error messages to a remote server, or generating detailed error reports that can be used for debugging purposes.

Overall, a custom exception handler class can help to improve the error handling capabilities of an application, making it more robust and reliable. By providing more detailed error messages, a consistent approach to error handling, and customized error handling capabilities, a custom exception handler class can help to reduce the time and effort required to diagnose and fix errors in the code.

## E. Multithreading:
Multithreading is a programming technique that allows multiple threads of execution to run concurrently within a single program. We have incorporated multithreading into our project, which allows us to perform parallel processing of background tasks in a manner that is both efficient and effective. Here are some advantages of using multithreading:

1. Improved performance: Multithreading can improve the performance of a program by allowing multiple tasks to be executed simultaneously. This can lead to faster and more efficient execution of complex algorithms and tasks.

2. Responsiveness: Multithreading can improve the responsiveness of a program by allowing it to continue running while waiting for input or output from other devices or processes.

3. Resource utilization: Multithreading can help to better utilize system resources, such as CPU cores, by allowing multiple threads to run on different cores simultaneously.

4. Simplified code: Multithreading can simplify code by allowing different parts of the program to be executed concurrently, without the need for complex synchronization mechanisms.

5. Scalability: Multithreading can improve scalability by allowing a program to handle more requests or tasks simultaneously, without the need to add more hardware resources.

6. Modularity: Multithreading can help to modularize code by allowing different parts of the program to be executed independently, making it easier to maintain and debug the code.

Overall, multithreading can offer significant advantages in terms of performance, responsiveness, resource utilization, code complexity, scalability, and modularity. However, it's important to use multithreading judiciously and avoid common pitfalls, such as race conditions and deadlocks, that can lead to difficult-to-debug errors.

## F. File Handling in JSON Format:
Our project uses file handling in JSON format to save data on disk, which ensures that our data is stored in a manner that is both secure and organized.
JSON (JavaScript Object Notation) is a lightweight data interchange format that is widely used for data exchange between web services and applications. Here are some advantages of using JSON for file handling over text and binary formats:

1. Human-readable: JSON is a human-readable format, which makes it easy to understand and modify by developers and other stakeholders. This can improve the maintainability and readability of the code.

2. Lightweight: JSON is a lightweight format, which can help to reduce the file size and improve the performance of the application.

3. Portable: JSON files can be easily transferred between different platforms and programming languages, making it a portable format for data exchange.

4. Easy to parse: JSON is easy to parse and can be quickly converted into native data structures in most programming languages, which can improve the speed and efficiency of data processing.

5. Supports complex data structures: JSON supports complex data structures, such as arrays and nested objects, which can be useful for representing and exchanging complex data structures.

6. Interoperability: JSON is widely supported by web browsers and web services, which makes it an ideal format for data exchange between different applications and systems.

Overall, JSON offers several advantages over text and binary formats for file handling, including human-readability, lightweightness, portability, ease of parsing, support for complex data structures, and interoperability. These advantages make JSON a popular choice for web-based applications and services that require data exchange between different platforms and programming languages.

## G. Consistent Naming Convention:
We follow a consistent naming convention throughout our codebase, which ensures that our code is easy to read and understand. This also allows us to navigate through our codebase in a seamless and efficient manner.

## H. Good Comments:
We have also included good comments throughout our codebase, which provide context and clarity to our code. This ensures that our code is easy to understand and modify, even for those who are not intimately familiar with our project.

## I. Aesthetic Code Structure:
Our code is structured aesthetically, which makes it easy to read and understand. This also ensures that our code is maintainable and scalable, allowing for easy expansion and modification.

## J. QT Advantages for UI Design:
We have chosen to use QT for our UI design, which provides numerous advantages over other UI frameworks. Some of the key advantages of QT include:

1. Cross-Platform Compatibility: QT is a cross-platform framework, which means that our UI will work seamlessly across multiple platforms, including Windows, macOS, and Linux.

2. Customizable Widgets: QT provides a range of customizable widgets, which allows us to design our UI in a manner that is both efficient and aesthetically pleasing. This also ensures that our UI is intuitive and easy to use.

3. Easy Integration with C++: QT is designed to work seamlessly with C++, which ensures that our UI is fast, efficient, and responsive. This also ensures that our code is modular and flexible, allowing for easy expansion and modification.



# Installation and Usage:

There are two ways to install our project:

1. Pre-built Installer:
   For Windows users, we have provided a pre-built installer that can be downloaded and executed. This installer will automatically install all the necessary dependencies and create shortcuts for easy access.

2. Manual Installation:
   For those who prefer to compile and run the project manually, the following instructions should be followed:

- Download the entire project from our repository.
- Install a qmake compiler on your system.
- Open a terminal and navigate to the project directory.
- Run the qmake tool to generate a Makefile based on your project's .pro file. For example, if your project is called "MyProject" and your .pro file is located in the root directory, you would run:
  `qmake MyProject.pro`
- Run the make command to compile your project. This will generate an executable file in the build directory. For example, if you want to build the "debug" version of your project, you would run:
  ` make debug`
- If the make command completes without errors, you can run your application by executing the generated executable file. For example, if your executable file is called "MyProject" and it is located in the build directory, you would run:

  `./build/MyProject`

Note: the exact commands may vary depending on your operating system and the specific configuration of your project. It's also possible to use an Integrated Development Environment (IDE) such as Qt Creator to compile and run your project. However, the general steps outlined above should work for most Qt C++ projects.

We hope that these installation instructions are clear and easy to follow. Please feel free to reach out to us if you encounter any issues during the installation process.


# License:

I am pleased to inform you that our project is released under the GPL license. This license ensures that our codebase is open source and freely available to the public. We have included a LICENSE file in our repository that outlines the terms and conditions of the GPL license. We remain committed to maintaining the integrity of our codebase and ensuring that it is accessible to all who wish to use it.

We hope that this README provides you with a clear and concise understanding of our Messenger project. We remain committed to providing users with a messaging experience that is efficient, reliable, and intuitive.

# This is Our Project for Advanced Programming Course @ IUT.ac\Spring 2023\
