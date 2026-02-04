_This project has been created as part of the 42 curriculum by kugurlu._

# Get Next Line

## Description

This project involves programming a function that returns a line read from a file descriptor. The goal is to learn how to handle static variables in C and manage memory allocation efficently.

## Instructions

### Compilation

- Complie the code using the following flags:

	```bash
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c <your_c_file.c> -o <saved_file_name>
	```

- If you want to compile the project with bonus features:

	```bash
	cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c <your_c_file.c> -o <saved_file_name>
	```

**Note**: The `BUFFER_SIZE` can be modified at compile time.

### Usage

- Include the header in your C files:

	- Without bonus:
		```C
		#include "get_next_line.h"
		```
	- With bonus:
		```C
		#include "get_next_line_bonus.h"
		```


- Call the function in a loop to read a file line by line:
	```C
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_putstr_fd(line, 1);
		free(line);
	}
	```

## Algorithm Selection

To maintain state through function calls the algorithm uses a static variable. The algorithm reads from a file descriptor and classifies the chunks based on `BUFFER_SIZE` appending it to the current remainder, and searches for a new line  character `\n`. When it finds that character, it returns the substring up to that character and saves any characters remaining into the static variable to use next time through the function.

## Resources

- **C Documentation**: File descriptors and `read()` function.
- **W3Schools** for getting know for static variables.
- **AI Usage**: AI was used for explaining of project instructions and debugging. I also got help for writing README.md.
