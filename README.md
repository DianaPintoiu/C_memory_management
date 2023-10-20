# C_memory_management


## Implementation

### Main Function:

In the main function, I dynamically allocated the data structure and the line read from the keyboard. I implemented a while loop that continues until the "exit" command is entered, at which point the program exits using a "break" statement.

The first word in each line, typically "insert," "insert_at," "delete_at," "find," "print," or "exit," is compared to determine the action to be taken.

- If the first word is "insert," a variable `len` is initialized to 0. It increases with each addition to the data vector within the structure. I use `strtok` to move to the next word, which represents the note type. This type is stored in the data structure as `structure->head->type`. Memory is allocated for the data vector (length determined by `len`), and the first word from the line (i.e., the name of the dedication giver) is copied using `memcpy`. Depending on the note type (1, 2, or 3), I define data types of different sizes (i.e., int8_t, int16_t, or int32_t) to store the two notes. The character read is converted to an integer using `atoi` and then stored in the data vector using `memmove`, updating `len` accordingly.

- If the first word is "insert_at," it is similar to "insert" but includes a character indicating the position where the data will be inserted. This character is converted to an integer using `atoi` and passed as an argument when calling the `add_at` function.

- If the first word is "delete_at," an additional character indicating the index to delete is read. This index is also converted to an integer using `atoi`, and the `delete_at` function is called to remove the element at the specified position.

- If the first word is "find," it includes an additional character representing the index of the element to display (if it exists). The `find` function is called with this index.

- If the first word is "print," the `print` function is called.

- If the first word is "exit," the program releases the allocated memory from the structure's data vector and the vector used for reading each line. It then exits the while loop.

### Function `add_last`:

This function is responsible for adding a new element to the data vector within the structure, following certain formatting rules.

- If `len` is 0 (indicating an empty data vector), memory is allocated for the vector with a length determined by the incoming data plus 5 bytes for the type. Otherwise, I iterate through the data vector to find the terminators and calculate the lengths of elements.

- The function performs a similar process to that in the main function, calculating element lengths and determining note types (1, 2, or 3). Then, it reallocates the memory to accommodate the new data element, updates the type, length, and data, and increases `len` to reflect the addition of a new element.

### Function `add_at`:

This function is used to insert data at a specified index in the data vector. If the index is invalid, it returns -1. Otherwise, it follows a similar process as the `add_last` function, but it calculates the lengths and positions differently, considering the index.

### Function `find`:

The `find` function is responsible for displaying the element at a specified index in a specific format. If the index is invalid, it exits without displaying anything. Otherwise, it iterates through the elements and displays the content of the element at the specified index. The element content is printed in a formatted manner.

### Function `delete_at`:

This function is used to delete an element at a specified index in the data vector. If the index is invalid, it returns -1. If the index is at the end of the vector, the `add_last` function is used to reallocate memory. Otherwise, it calculates the lengths and positions correctly and reallocates memory without the element to be deleted, updating the `len` variable accordingly.

### Function `print`:

The `print` function displays all elements in the data vector. It iterates through the data vector, and for each element, it formats and prints the content.

## Final Thoughts

This assignment was quite challenging, and receiving clarifications somewhat late didn't help. However, in the end, I'm happy that I managed to complete it. The project helped me learn how to use GDB effectively. Once you understand what is required and expected, the task becomes manageable. The well-structured problem statement made the entire experience more manageable.
