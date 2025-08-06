# get_next_line - File Reading Function

## About

**get_next_line** is a C programming project at École 42 that focuses on implementing a function capable of reading a file line by line. This project introduces advanced concepts in file handling, memory management, and static variables while creating a utility function that will be used throughout the remaining 42 curriculum.

The function reads from a file descriptor one line at a time, making it possible to process large files efficiently without loading the entire file into memory. This approach is essential for handling files of any size while maintaining optimal memory usage.

## Learning Objectives

- **File Descriptor Management**: Understanding how file descriptors work in Unix systems
- **Static Variables**: Mastering the use of static variables for persistent data storage
- **Dynamic Memory Management**: Advanced malloc and free usage with complex data structures
- **Buffer Management**: Efficient handling of read buffers and data processing
- **Error Handling**: Robust error detection and memory leak prevention
- **Algorithm Design**: Creating efficient line-by-line reading algorithms

## Function Prototype

```c
char *get_next_line(int fd);
```

**Parameters:**
- `fd`: File descriptor to read from

**Return Value:**
- Returns the line that was read (including the terminating `\n` character if present)
- Returns `NULL` when there is nothing else to read or an error occurred

**External Functions Used:**
- `read()`, `malloc()`, `free()`

## Implementation Details

### Core Algorithm

The function implements a sophisticated buffering system that:
1. Reads data from the file descriptor in chunks (defined by BUFFER_SIZE)
2. Stores incomplete lines in a static variable between function calls
3. Processes the buffer to extract complete lines
4. Returns one line per function call
5. Handles end-of-file conditions gracefully

### Buffer Management

The implementation uses a configurable buffer size that can be set at compile time:
```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
#endif
```

This allows for optimization based on different use cases:
- Small buffer sizes (1 byte) for memory-constrained environments
- Large buffer sizes (8192+ bytes) for high-performance file processing
- Custom buffer sizes based on expected line lengths

### Memory Management Strategy

The function employs careful memory management to prevent leaks:
- Dynamic allocation for line storage
- Proper cleanup of static variables when files end
- Error handling that ensures no memory is leaked
- Efficient reuse of allocated memory where possible

### Static Variable Usage

A static variable maintains state between function calls, storing:
- Partially read lines that span multiple buffer reads
- Remaining data after a complete line is extracted
- File position context for continued reading

## Technical Challenges

### Multiple File Descriptors
The function must handle multiple file descriptors simultaneously, maintaining separate static storage for each active file descriptor.

### Variable Line Lengths
Lines can be of any length, requiring dynamic memory allocation and reallocation strategies that adapt to different line sizes efficiently.

### End-of-File Handling
Proper detection and handling of end-of-file conditions, including files that don't end with a newline character.

### Buffer Boundary Management
Managing cases where lines are split across multiple buffer reads, requiring careful concatenation and memory management.

### Error Recovery
Robust error handling that cleans up resources and prevents memory leaks even when read operations fail.

## Usage Examples

### Basic File Reading
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("example.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return 0;
}
```

## Compilation

### Standard Compilation
```bash
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

### Testing with Different Buffer Sizes
```bash
# Small buffer size for thorough testing
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl_test

# Large buffer size for performance
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=8192 get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

## Testing Strategy

### Edge Cases Tested
- Empty files
- Files without final newline
- Files with only newlines
- Very long lines (exceeding buffer size)
- Binary files
- Invalid file descriptors
- Files with mixed line endings

### Performance Testing
- Large files (GB+ sizes)
- Files with varying line lengths
- Multiple simultaneous file descriptors
- Different buffer sizes for optimization

### Memory Testing
- Valgrind for memory leak detection
- Stress testing with continuous file operations
- Edge case memory usage patterns

## Key Challenges & Solutions

### Memory Leaks Prevention
- **Challenge**: Managing dynamic memory with static variables across multiple function calls
- **Solution**: Careful tracking of allocated memory and systematic cleanup procedures

### Performance Optimization
- **Challenge**: Balancing memory usage with read performance for different file types
- **Solution**: Configurable buffer sizes and efficient string manipulation algorithms

### Error Handling
- **Challenge**: Robust error detection without memory leaks
- **Solution**: Comprehensive error checking with guaranteed cleanup procedures

## Skills Demonstrated

- **Advanced Memory Management**: Complex dynamic allocation with static variable persistence
- **File System Operations**: Low-level file handling using system calls
- **Algorithm Design**: Efficient buffer management and string processing
- **Error Handling**: Robust error detection and resource cleanup
- **Performance Optimization**: Balancing memory usage with processing speed
- **Code Efficiency**: Creating lean, fast code for a utility function
- **Testing Methodologies**: Comprehensive edge case testing and validation

## Applications in 42 Curriculum

This function becomes a cornerstone utility used in numerous subsequent projects:
- **ft_printf**: Reading format strings and processing input
- **minishell**: Reading command input line by line
- **cub3d**: Reading map files and configuration
- **push_swap**: Processing input sequences
- Various parsing projects requiring line-by-line file processing

## Notes

The get_next_line project represents a significant step in understanding advanced C programming concepts. It bridges the gap between basic string manipulation and complex system programming, introducing concepts that are fundamental to many real-world applications.

The function's design philosophy emphasizes memory efficiency and performance, making it suitable for integration into larger projects where reliable file processing is essential. The project demonstrates practical application of theoretical concepts in a way that provides immediate, tangible utility.

The implementation challenges encountered in this project - particularly around memory management and static variable usage - provide excellent preparation for more complex system programming tasks and demonstrate proficiency in writing production-quality C code.

---

*Developed as part of the École 42 curriculum - advancing from basic programming to sophisticated utility function development.*
