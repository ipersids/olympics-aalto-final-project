# Olympic medals tracking program
Final project for [Aalto University's C programming course](https://fitech.io/en/studies/basic-course-in-c-programming/). The task involves implementing a system to track Olympic medals for various countries, including functionalities for adding, sorting, and managing the medal data.

### Project Structure

```css
olympics-aalto-final-project/
│
├── include/
│   └── project.h
│
├── src/
│   ├── add_medals.c
│   ├── add_nations.c
│   ├── db_file.c
│   ├── memory.c
│   ├── print_sorted_db.c
│   ├── str_input.c
│   └── main.c
│
└── Makefile
```

- **`include/`**: Contains header files with declarations and definitions.
  - `project.h`: Includes libraries,function declarations and type definitions used across the project.

- **`src/`**: Contains source code files and the Makefile for compiling the project.
  - `add_medals.c`: Source file where the function to add medals is implemented.
  - `add_nations.c`: Source file where the function to add new nations is implemented.
  - `db_file.c`: Source file containing functions for loading and saving the database to a file.
  - `memory.c`: Source file with functions for managing memory deallocation.
  - `print_sorted_db.c`: Source file containing functions for printing the sorted database.
  - `str_input.c`: Source file with functions for handling string input and splitting.
  - `main.c`: Contains the `main()` function and handles user input and commands.
  - `Makefile`: Script for compiling and linking the source files into an executable.

### Used libraries:
```C
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
```

### Where to start
The `main()` function serves as the entry point for the program. It continuously reads user input, processes various commands, and manages a linked list database of nations and their respective medal counts.

### Allowed Commands Description:

- _Add Nation_ (A):  Add a country to the database.  
`A <name>`  
- _Write to File_ (W): Saves the current database to a file.  
`W <filename>`  
- _Add Medals_ (M): Updates a nation's medal counts.  
`M <name> <gold> <silver> <bronze>`  
- _Print Sorted Database_ (L): Sorts and displays the database contents.  
`L`
- _Load from File_ (O): Loads a database from a file, replacing the current one.  
`O <filename>`  
- _Quit command_ (Q): Exit the program.  
`Q`  

**Example:**
```
A Finland
>> SUCCESS
W db.txt
>> SUCCESS
M Finland 1 2 3
>> SUCCESS
L
>> Finland 1 2 3
>> SUCCESS
O db.txt
>> SUCCESS
Q
>> exit program
```

## Skills
- Basic concepts of systems-level programming.  
- Basics of the C programming language.  
- Dynamic memory management and its application in common data structures. 
- Basic use of programming and debugging tools for C.  
  

_________
  
Written by Julia Persidskaia.  
[LinkedIn](https://www.linkedin.com/in/iuliia-persidskaia/)