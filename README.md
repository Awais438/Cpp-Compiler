# Cpp-Compiler
This project demonstrates the successful design and implementation of a compiler using C++ in Visual Studio, showcasing its ability to perform lexical and syntax analysis, generate abstract syntax trees, and evaluate mathematical expressions. The utilization of GUI C++/CLI and the .NET framework empowers users to interact with the compiler seamlessly, making it a valuable tool for developers, students, and professionals alike.

## Acronyms and Abbreviations
DSA: Data Structures and Algorithms  
GUI: Graphical User Interface  
CLR: Common Language Runtime  
AST: Abstract Syntax Tree  
.NET: Microsoft .NET Framework  
C++: C Plus Plus  
VS: Visual Studio  
API: Application Programming Interface  
IDE: Integrated Development Environment  
UI: User Interface  
QA: Quality Assurance  

### Design 
Here’s a comprehensive overview of the design choices, architecture, and components of our compiler project. Here are some key points to cover:

### Overall Architecture: 
We have adopted a layered architecture, with separate layers for the graphical user interface (GUI), front-end components (lexical analysis, syntax analysis), and back-end components (AST generation, expression evaluation). The layers communicate with each other through well-defined interfaces, promoting separation of concerns and modular design.

### Lexical Analysis Design: 
We have employed regular expressions or finite automata to perform efficient tokenization. The input expression would be scanned character by character, and tokens such as identifiers, operators, and literals would be identified and categorized into appropriate token types. The tokens are stored using data structures such as arrays for further processing.

### Syntax Analysis Design: 
We have designed a context-free grammar (CFG) that defines the syntax rules of the language you are targeting. The syntax analyzer may utilize a recursive descent parsing technique, where each grammar rule is implemented as a separate function, allowing for top-down parsing. The syntax analyzer would verify the input expression’s compliance with the CFG by recursively applying these grammar rules.

### Abstract Syntax Tree (AST) Design: 
AST is designed as a tree-like data structure, where each node represents an expression or an operation. The AST is constructed by traversing the parsed input expression and creating appropriate nodes and connections to represent the hierarchical relationships. Each node may contain information such as the type of operation or value associated with the expression.

### Expression Evaluation Design: 
The expression evaluation component involves traversing the AST in a recursive manner. The AST nodes are evaluated based on their types (operators or operands), and the necessary computations are performed accordingly. Precedence and associativity rules are considered during the evaluation to ensure correct mathematical calculations.

## Outputs & Screenshots 
### Sign in Form: 
![image](https://github.com/ShaiikhAbdullah/Cpp-Compiler-VS/assets/93272893/d594ff92-c33a-4a1a-b5ea-3b79db352aff)
#### If the Password is in-correct: 
![image](https://github.com/ShaiikhAbdullah/Cpp-Compiler-VS/assets/93272893/812f6b0b-9ebb-4d51-850e-c31ed2807287)
### Compiler Form: 
![image](https://github.com/ShaiikhAbdullah/Cpp-Compiler-VS/assets/93272893/b7e41210-bfc7-4ac7-aa8b-3a0c92aad8c6)
### Lexical Form: 
![image](https://github.com/ShaiikhAbdullah/Cpp-Compiler-VS/assets/93272893/582a839d-e761-40f2-852b-fb3707716f45)
#### Generated Tokens: 
![image](https://github.com/ShaiikhAbdullah/Cpp-Compiler-VS/assets/93272893/6287f389-2d12-4c32-aae1-82db2e058cc1)
### Semantic Analyzer: 
#### Tree Generation & Evaluation of Expression: 
![image](https://github.com/ShaiikhAbdullah/Cpp-Compiler-VS/assets/93272893/0ffbe43d-6512-4c02-b346-decf5ba59f41)

In conclusion, this project aimed to develop a graphical user interface (GUI) component for interacting with compiler components. Although the specific implementation details of the GUI were not provided in the header file codes, we have discussed the general concepts and code logic involved in building a GUI that interacts with the underlying compiler components.

The GUI serves as the front-end of the application, providing a visual representation of the user interface. It allows users to input code, configure compiler settings, and execute various compiler operations. The GUI captures user events and triggers corresponding event handlers, which process the input, validate it if necessary, and pass the data to the compiler components.

The interaction between the GUI and the compiler components follows a typical flow. The GUI calls functions from the compiler components, passing relevant data as arguments. The compiler components perform the necessary operations, such as compiling code, executing commands, or processing input. The results or status information are then returned to the GUI, which updates the user interface accordingly, displaying the output or any error messages.

Throughout the project, considerations were given to user input handling, including validation and error handling, as well as displaying results in a user-friendly manner. The GUI component also acted as an intermediary between the user and the back-end functionality, translating user actions into commands or function calls that interacted with the compiler components.

It is important to note that the implementation details of the GUI component and its integration with the compiler components may vary depending on the programming language, GUI framework, and specific project requirements. The provided header file codes served as a starting point, but a complete understanding of the GUI implementation would require further examination and analysis.

In summary, the development of a GUI component for interacting with compiler components is a complex task that involves capturing user input, processing it, and integrating with the back-end functionality. By creating an intuitive and efficient user interface, this project aimed to enhance the user experience when working with compilers and facilitate the execution of compiler operations.
