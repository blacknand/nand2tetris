# A 16 bit computer, built completely from the ground up capable of running Tetris
all hardware and software components are built completely from scratch to fully learn and understand how computers work. The ultimate goal is to create a fully functional 16-bit computer capable of running Tetris.
## 1. Logic Gates/Boolean Logic
The foundation of any computer system is built on logic gates and boolean logic. In this phase, we construct a large collection of 1-bit and 16-bit logic gates from scratch.
+ Basic Gates: AND, OR, NOT, NAND, NOR, XOR, XNOR
+ Composite Gates: Multiplexers, Demultiplexers, Adders, Subtractors
+ 16-bit Versions: Expanding 1-bit logic gates to operate on 16-bit data
## 2. Boolean Arithmetic/ALU
Building on the logic gates, we develop the Arithmetic Logic Unit (ALU), which is responsible for performing arithmetic and logic operations.
+ Mathematical Operations: Addition, Subtraction, Bitwise operations
+ Logical Operations: AND, OR, NOT, NAND, NOR, XOR, XNOR
+ 16-bit ALU: Capable of executing complex operations on 16-bit data
## 3. Memory
Memory is crucial for storing data and instructions. This phase focuses on creating various sizes of RAM chips and clocked chips, including D flip-flops.
+ Basic Memory Elements: D Flip-Flops, Latches
+ RAM Chips: 4-bit, 8-bit, 16-bit, and beyond
+ Clocking Mechanisms: Ensuring synchronized data storage and retrieval
## 4. Machine Language
With the hardware foundation in place, we define and test programs written in the Hack flavor of Assembly language.
+ Instruction Set Architecture (ISA): Definition of the Hack assembly language
+ Test Programs: Simple programs to test and validate the hardware components
## 5. CPU
The Central Processing Unit (CPU) integrates all hardware components into a single chip capable of executing instructions.
+ Control Unit: Manages the execution of instructions
+ Data Path: Routes data between the ALU, memory, and registers
+ Integration: Combining all components to form a cohesive CPU
## 6. Assembler
The assembler translates Hack machine language into binary code that the CPU can execute.
+ Syntax Parsing: Converts assembly language into machine code
+ Code Generation: Outputs binary files ready for execution
## 7. VM Part I
The first part of the Virtual Machine (VM) translation as part of a two-step compilation process handles basic VM bytecode and translates it into machine code.
+ Stack Arithmetic: Handling basic stack operations
+ Memory Access: Translating memory access commands
+ Code Translation: Converting VM code to Hack assembly
Sure! Here's the continuation of the README, detailing the remaining phases of the project:
## 8. VM Part II
In this phase, we extend the capabilities of the VM translator to handle more complex commands, including program flow and function calling.
+ Program Flow: Translating conditional and unconditional branching commands
+ Function Calling: Handling function calls and returns
+ Advanced Memory Access: Managing memory segments like pointers, static, and temp
## 9. High-Level Language (Jack)
The high-level language Jack is introduced, providing a more abstract and user-friendly way to write programs.
+ Syntax and Semantics: Definition of the Jack language, including syntax and semantic rules
+ Standard Library: Basic standard library functions for string manipulation, I/O, and mathematics
+ Sample Programs: Example Jack programs demonstrating language features
## 10. Compiler I
The first part of the Jack compiler translates Jack high-level language into VM code.
+ Syntax Analysis: Parsing Jack code into an abstract syntax tree (AST)
+ Code Generation: Translating the AST into VM code
+ Error Handling: Detecting and reporting syntax and semantic errors
## 11. Compiler II
The second part of the Jack compiler focuses on optimizing and finalizing the translation process from Jack to VM code.
+ Optimization: Improving the efficiency of the generated VM code
+ Advanced Code Generation: Handling complex language constructs and features
+ Comprehensive Testing: Extensive testing to ensure correctness and performance
## 12. Operating System
With the hardware and software infrastructure in place, we develop a simple operating system to manage the computer's resources and provide essential services.
+ Memory Management: Handling memory allocation and deallocation
+ Process Management: Managing program execution and multitasking
+ I/O Handling: Providing input and output functionalities
