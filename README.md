## deus

The **deus** project comprises several components showcasing advanced knowledge of C++ and Objective-C features, including template programming, memory management, asynchronous networking, and Cocoa application development for macOS.

- **```ripae/src/tests/test_ripae.cpp```**: This file demonstrates a simple banking system using C++ templates for account management and a multi-threaded transaction system. It emphasizes the use of templates, thread safety, custom data structures, and concurrency for simulating real-world banking operations.

- **```$/test_$.cpp```**: This file demonstrates a simple banking system using C++ templates for account management and Boost.Asio for asynchronous server-client communication. It showcases basic operations like deposits and withdrawals, and simulates transactions over a network, emphasizing the use of modern C++ features like smart pointers and asynchronous I/O. 

- **cocoa/tests/test_cocoa.cpp**: Demonstrates creating a basic macOS GUI application using the Cocoa framework, focusing on window creation and memory management with `@autoreleasepool`.
  
- **mail/src/tests/mail/src/test_mail.cpp**: Implements a generic mail server supporting both TCP and UDP using Boost.Asio, highlighting asynchronous I/O operations and template specialization.

- **videlegere/tests/test_videlegere.cpp**: Builds an eye-tracking system using OpenCV and Boost.Beast, showcasing advanced multithreading, file handling, and networking with asynchronous HTTP responses.

- **nda/tests/nda/src/test_nda.cpp**: Illustrates dynamic memory management, custom `Vector` implementation, and multidimensional arrays in C++ using template classes, `std::unique_ptr`, and RAII principles.

- **foo/src/tests/foo/src/test_main.cpp**: Explores recursive template instantiation, type deduction, and metaprogramming through flexible template design, focusing on nested template classes.

- **foo/src/tests/foo/inc/foobar.hpp**: Showcases template-based design with generic classes like `Foobar` and `Barfoo`, emphasizing template metaprogramming for building complex relationships between types.

- **foo/src/tests/foo/inc/foo.hpp**: Leverages C++ features such as macros, architecture-specific code branching, and `<filesystem>` for dynamic directory and file creation, demonstrating proficiency in system-level programming.


## ```$/test_$.cpp```

This project demonstrates a simple banking system with account management and a server-client communication model using Boost.Asio for asynchronous networking.

Features:
Account Management: The Account class supports basic operations such as deposit and withdrawal, utilizing a templated Property class to manage and encapsulate account attributes (owner and balance).

Server-Client Architecture:

The BankingServer class handles incoming client connections and processes transaction requests asynchronously.
The BankingClient class connects to the server and sends transaction messages, simulating simple banking transactions.
Example Workflow:
Two accounts (Alice and Bob) are created with initial balances.
A transaction is performed where Alice sends money to Bob, and the new balances are updated and displayed.
A banking server is launched, and a client sends a mock transaction message to demonstrate server-client communication.
This project demonstrates the use of modern C++ features like templates, smart pointers, and asynchronous I/O with Boost.Asio to build a networked banking application.

## ```ripae/src/tests/test_ripae.cpp```

This project demonstrates a simple banking system with account management and a multi-threaded transaction handling model.

### Features:
- **Account Management**: The `Account` class supports basic operations such as deposit and withdrawal, utilizing a templated `Utility` class to manage and encapsulate account attributes like `id` and `balance`.

- **Banking System**: The `Bank` class holds a collection of accounts, implemented with a custom stack (`Stack` class), which illustrates custom data structure management without reliance on the STL.

- **Multi-Threaded Transactions**: The main function simulates concurrent transactions using multiple threads, highlighting key concurrency concepts such as:
  - **Thread Safety**: `std::mutex` is used to protect shared resources, ensuring safe concurrent access.
  - **Retry Mechanism and Idempotency**: If a transaction fails due to insufficient funds, a retry mechanism is demonstrated for idempotent withdrawal attempts, providing resilience in financial operations.

- **Logging**: Simple logging macros (`LOG_FAILURE` and `LOG_SUCCESS`) provide easy-to-follow messages on the outcome of each transaction, helping trace the execution flow and debug issues.

This project highlights advanced C++ concepts such as template programming, custom data structures, and concurrency. It illustrates a practical scenario of concurrent banking transactions, showcasing how thread safety and idempotency are critical for real-world financial applications.

## cocoa/tests/test_cocoa.cpp

The code in `cocoa/tests/test_cocoa.cpp` is a simple example of using the Cocoa framework in Objective-C to create a macOS GUI application. It demonstrates the creation of an `NSApplication` object and an `NSWindow` with basic window properties such as title, size, and style. The window is set as the key window, which brings it to the front of the interface.

This code showcases knowledge of **Objective-C memory management** with `@autoreleasepool`, and fundamental **Cocoa application architecture** by leveraging `NSApplication` and `NSWindow` to create a GUI window. The use of `NSMakeRect` to define window size and the Cocoa-specific window style masks (e.g., `NSWindowStyleMaskTitled`, `NSWindowStyleMaskClosable`) reflects an understanding of macOS application development.

## mail/src/tests/mail/src/test_mail.cpp

This code demonstrates a generic C++ mail server using the Boost.Asio library for asynchronous I/O operations, supporting both TCP and UDP protocols. The template-based design allows for easy specialization of the server for different protocols, leveraging the flexibility of templates in C++. The `MailServer` class is templated on the protocol type (either `tcp` or `udp`), and specializations for each protocol handle connection and message processing differently. 

- For **TCP**, the server handles each connection in a detached thread, reading and echoing the received message.
- For **UDP**, it uses asynchronous receive operations to process messages.

This design showcases a strong understanding of **asynchronous programming**, **template specialization**, and the **Boost.Asio library**. The use of `std::thread` for handling TCP connections and `async_receive_from` for UDP demonstrates expertise in managing network I/O in a concurrent and non-blocking manner.

## videlegere/tests/test_videlegere.cpp

The code in `videlegere/tests/test_videlegere.cpp` demonstrates the use of OpenCV, Boost.Beast, and asynchronous networking to create an eye-tracking system for detecting and mapping gaze positions to regions of text displayed on a web page. The application tracks user eye movements using OpenCV’s Haar Cascade classifiers, logs gaze positions, and compares them with predefined text regions on the page. This implementation showcases advanced C++ features like multithreading, file handling, and efficient resource management via asynchronous operations. Additionally, the code integrates HTTP responses using Boost.Beast, making it a full-stack application capable of handling web requests while tracking user interactions visually in real-time.

## nda/tests/nda/src/test_nda.cpp

The code in `nda/tests/nda/src/test_nda.cpp` highlights proficiency in utilizing C++ features such as template classes, memory management through `std::unique_ptr`, and multidimensional array handling. The custom `Vector` class manages dynamic resizing of arrays with automatic memory management, showcasing an understanding of RAII principles. The `NDArray` class offers a flexible n-dimensional array, where indices are calculated using a flattened storage approach, demonstrating a solid grasp of multidimensional data structures. The `NDArrayManager` efficiently manages multiple instances of `NDArray`, and the code illustrates how to interact with and manipulate multidimensional arrays dynamically. This design demonstrates advanced knowledge of templates, exception handling, and resource management.

## foo/src/tests/foo/src/test_main.cpp

The code in `test_main.cpp` demonstrates advanced C++ features such as templates, recursive template instantiation, and type deduction. It showcases the flexibility of template programming by defining a class `Foobar` that can hold any type and a `NestedTemplates` class that recursively nests template classes. The use of `std::decay` ensures the proper handling of types when printing values, highlighting knowledge of type manipulation in C++. Additionally, the code emphasizes metaprogramming techniques through the recursive nesting of templates, illustrating the power and complexity of templates in C++.

## foo/src/tests/foo/inc/foobar.hpp

The `foobar.hpp` file demonstrates advanced C++ templating capabilities. It defines two templated classes: `Foobar` and `Barfoo`. `Foobar` is a generic class that can store and manipulate any data type, allowing flexible object instantiation. The `Barfoo` class further showcases the use of template templates by accepting another template class (`Foobar`) as a parameter, along with a type. This design highlights the programmer's understanding of generic programming and template metaprogramming, demonstrating how templates can be nested to build complex relationships between types.

## foo/src/tests/foo/inc/foo.hpp

The `foo.hpp` file leverages several C++ features such as macros, architecture-specific code branching, and filesystem operations. It defines architecture-dependent integer types (`int32` and `int64`) based on the underlying processor, ensuring portability. It also uses macros like `STACK_TRACE` to provide debugging information. The `Foo` class demonstrates the use of C++'s `<filesystem>` library for dynamic file and directory creation, while also incorporating randomness for file naming and template-based methods. This demonstrates knowledge of both system-level programming and modern C++ features like `std::filesystem`, metaprogramming, and platform-specific code branching.
