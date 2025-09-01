# Get Next Line (GNL)

## 📖 About

**Get Next Line** is a 42 School project that challenges students to implement a function that reads a file line by line. This project introduces the concept of **static variables** in C and teaches efficient file reading techniques.

The function reads from a file descriptor and returns one line at a time, making it possible to read large files without loading the entire content into memory.

## 🎯 Objectives

- Learn and understand **static variables** in C programming
- Implement efficient file reading algorithms
- Handle memory management properly (no memory leaks)
- Work with file descriptors and system calls
- Master buffer management for optimal performance

## 🚀 Features

### Mandatory Part
- ✅ Reads one line at a time from a file descriptor
- ✅ Returns the line including the terminating `\n` character
- ✅ Returns `NULL` when reaching EOF or on error
- ✅ Works with files and standard input
- ✅ Configurable buffer size via compilation flag
- ✅ Memory efficient - no memory leaks

### Bonus Part
- ✅ Handles multiple file descriptors simultaneously
- ✅ Uses only one static variable
- ✅ Maintains independent reading state for each file descriptor

## 📁 Project Structure

```
get_next_line/
├── get_next_line.c              # Main function implementation
├── get_next_line.h              # Header file with prototypes
├── get_next_line_utils.c        # Utility functions
├── get_next_line_bonus.c        # Bonus implementation
├── get_next_line_bonus.h        # Bonus header file
├── get_next_line_utils_bonus.c  # Bonus utility functions
├── LICENSE			 # License
└── README.md                    # This file
```

## 🛠️ Installation & Usage

### Compilation

```bash
# Basic compilation with default buffer size
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c

# Compilation with custom buffer size
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

# Bonus compilation
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

### Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int		fd;
    char	*line;
    
    fd = open("example.txt", O_RDONLY);
    line = get_next_line(fd);
    if(!line)
	return (1);
    while (line)
    {
      printf("%s", line);
      free(line);
      line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

### Bonus Usage (Multiple File Descriptors)

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1, fd2;
    char *line;
    
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    
    // Read alternately from both files
    line = get_next_line(fd1);
    printf("File 1: %s", line);
    free(line);
    
    line = get_next_line(fd2);
    printf("File 2: %s", line);
    free(line);
    
    line = get_next_line(fd1);
    printf("File 1: %s", line);
    free(line);
    
    line = get_next_line(fd2);
    printf("File 2: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```

## 🔧 Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters
- `fd`: The file descriptor to read from

### Return Value
- The line read from the file descriptor (including `\n`)
- `NULL` if there's nothing more to read or an error occurred

## 🧰 Utility Functions

The project includes several custom utility functions:

- `ft_strlen()` - Calculate string length
- `ft_strchr()` - Locate character in string
- `ft_strjoin()` - Concatenate two strings
- `ft_strdup()` - Duplicate a string
- `ft_substr()` - Extract substring

## 📋 Requirements

- **Language:** C
- **Norm:** 42 Norm compliant
- **Memory:** No memory leaks allowed
- **Functions allowed:** `read`, `malloc`, `free`
- **Forbidden:** `lseek()`, global variables, libft

## 🧪 Testing

The function should work correctly with various buffer sizes:

```bash
# Test with different buffer sizes
cc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c
cc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
cc -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c
```

### Test Cases
- Empty files
- Files without newline at the end
- Files with only newlines
- Very long lines
- Binary files (undefined behavior)
- Invalid file descriptors
- Multiple file descriptors (bonus)

## 💡 Key Concepts

### Static Variables
The project heavily relies on static variables to maintain state between function calls:

```c
static char *remaining;  // Keeps leftover data between calls
```

### Buffer Management
Efficient reading using a configurable buffer size:
- Small buffers (1 byte) - many system calls
- Large buffers (10MB+) - fewer system calls, more memory usage
- Optimal buffer size depends on the use case

### Memory Management
- All allocated memory must be freed
- Handle edge cases (malloc failures, read errors)
- Clean up static variables when appropriate

## 🏆 Grade

This project was completed and approved as part of the 42 School curriculum with 125/100.
