# C++ Programming Concepts

This section provides a comprehensive guide to the C++ programming concepts used in the M-Boma Housing Project. We'll start with basic concepts and gradually move to more advanced topics, showing how each is implemented in the project.

## Table of Contents

1. [Basics](#1-basics)
2. [Object-Oriented Programming](#2-object-oriented-programming)
3. [Memory Management](#3-memory-management)
4. [Standard Template Library](#4-standard-template-library)
5. [Error Handling](#5-error-handling)
6. [Modern C++ Features](#6-modern-c-features)
7. [File I/O and Serialization](#7-file-io-and-serialization)
8. [Concurrency and Multithreading](#8-concurrency-and-multithreading)

## 1. Basics

### [1.1 Variables and Data Types](./1-1-variables-data-types.md)
- Fundamental types used in the project
- Type conversion in database operations
- String handling for user input and display

### [1.2 Control Structures](./1-2-control-structures.md)
- Decision-making with if-else statements
- Looping constructs in menu systems
- Switch statements for user options

### [1.3 Functions and Parameters](./1-3-functions-parameters.md)
- Function declarations and definitions
- Parameter passing techniques
- Return values and output parameters

### [1.4 Header Files and Compilation](./1-4-header-compilation.md)
- Header file organization
- Include guards
- Compilation process with Makefile

## 2. Object-Oriented Programming

### [2.1 Classes and Objects](./2-1-classes-objects.md)
- Class design in the project
- Encapsulation of data and behavior
- Object creation and lifecycle

### [2.2 Inheritance and Polymorphism](./2-2-inheritance-polymorphism.md)
- Base and derived classes
- Virtual functions
- Runtime polymorphism

### [2.3 Class Relationships](./2-3-class-relationships.md)
- Composition vs. aggregation
- Has-a and is-a relationships
- UML diagrams of project classes

### [2.4 Operator Overloading](./2-4-operator-overloading.md)
- Custom operators for project classes
- Stream operators for output formatting
- Comparison operators

## 3. Memory Management

### [3.1 Stack vs. Heap](./3-1-stack-heap.md)
- Stack allocation for local objects
- Dynamic allocation with new/delete
- Heap management in database connections

### [3.2 Resource Acquisition Is Initialization (RAII)](./3-2-raii.md)
- RAII principles in practice
- Resource management patterns
- Automatic cleanup with destructors

### [3.3 Smart Pointers](./3-3-smart-pointers.md)
- Using std::unique_ptr for ownership
- Shared resources with std::shared_ptr
- Custom deleters for resources

### [3.4 Memory Leaks Prevention](./3-4-memory-leaks.md)
- Common memory leak patterns
- Tools for leak detection
- Best practices for memory management

## 4. Standard Template Library

### [4.1 Containers](./4-1-containers.md)
- Vector usage for collections (houses, users)
- Maps for lookup tables
- Container selection criteria

### [4.2 Iterators](./4-2-iterators.md)
- Iterating through collections
- Iterator types and usage
- Range-based for loops

### [4.3 Algorithms](./4-3-algorithms.md)
- Searching and sorting
- Transformations and operations
- Functional programming with algorithms

### [4.4 Utility Classes](./4-4-utility-classes.md)
- std::string operations
- Date and time handling
- Numeric operations

## 5. Error Handling

### [5.1 Exception Handling](./5-1-exception-handling.md)
- Try-catch blocks
- Exception hierarchy
- Exception safety guarantees

### [5.2 Error Codes and Messages](./5-2-error-codes.md)
- Error reporting patterns
- User-friendly error messages
- Error propagation

### [5.3 Input Validation](./5-3-input-validation.md)
- Validating user input
- Preventing invalid states
- Defensive programming

### [5.4 Debugging Techniques](./5-4-debugging.md)
- Logging systems
- Debug vs. release builds
- Debugging tools and practices

## 6. Modern C++ Features

### [6.1 Auto Type Inference](./6-1-auto.md)
- Type inference with auto
- Decltype and type deduction
- When (and when not) to use auto

### [6.2 Lambda Expressions](./6-2-lambda.md)
- Lambda syntax and usage
- Captures and scoping
- Functional programming patterns

### [6.3 Move Semantics](./6-3-move-semantics.md)
- Rvalue references
- Move constructors and assignment
- Performance improvements with move semantics

### [6.4 Constexpr and Compile-Time Evaluation](./6-4-constexpr.md)
- Compile-time constants
- constexpr functions
- Optimization through compile-time evaluation

## 7. File I/O and Serialization

### [7.1 File Operations](./7-1-file-operations.md)
- Reading and writing files
- Binary vs. text files
- File streams and buffering

### [7.2 Database Serialization](./7-2-database-serialization.md)
- Converting objects to database format
- SQL query generation
- Result set processing

### [7.3 Configuration Management](./7-3-configuration.md)
- Loading configuration from files
- Environment variables
- Dynamic configuration

## 8. Concurrency and Multithreading

### [8.1 Thread Basics](./8-1-thread-basics.md)
- Creating and managing threads
- Thread synchronization
- Use cases for multithreading

### [8.2 Mutexes and Locks](./8-2-mutexes.md)
- Protecting shared resources
- Lock types and usage
- Deadlock prevention

### [8.3 Async Operations](./8-3-async.md)
- Futures and promises
- Asynchronous database operations
- Task-based parallelism

### [8.4 Thread Pools](./8-4-thread-pools.md)
- Worker thread patterns
- Job scheduling
- Managing concurrent workloads

---

Each lesson includes:
- Theoretical explanations of the concept
- Examples from the M-Boma Housing Project
- Best practices and pitfalls
- Exercises to reinforce learning
- References to further resources
