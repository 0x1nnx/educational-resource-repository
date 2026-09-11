# Resource Management System

A simple command-line application written in **C** for managing educational or online resources. The program allows users to add, update, delete, search, and list resources stored in a text file.

## Features

- Add new resources
- Update existing resources by ID
- Delete resources by ID
- Display all saved resources
- Search for a resource by ID
- File-based data storage
- Simple menu-driven interface

## Technologies Used

- C Programming Language
- CS50 Library
- Standard C Libraries
  - stdio.h
  - stdlib.h
  - string.h

## Project Structure

```
.
├── main.c            # Source code
├── resources.txt     # Database file (created automatically)
├── README.md
```

## Resource Structure

Each resource contains the following information:

| Field | Description |
|--------|-------------|
| ID | Unique identifier |
| Title | Resource title |
| Author | Author or creator |
| Topic | Subject/category |
| URL | Resource link |
| Description | Short description |

Resources are stored in `resources.txt` using the following format:

```text
1 "Introduction to C" "Dennis Ritchie" "Programming" "https://example.com" "Basic C programming tutorial"
```

## Requirements

- GCC Compiler
- CS50 Library

### Installing the CS50 Library

#### Ubuntu / Debian

```bash
sudo apt update
sudo apt install libcs50
```

#### macOS

```bash
brew install cs50
```

## Compilation

Compile the program using:

```bash
gcc main.c -o resources -lcs50
```

Or with the CS50 compiler:

```bash
make main
```

## Running the Program

```bash
./resources
```

## Menu

```
------------- Resource Management Program -------------

1. Add Resource
2. Update Resource
3. Delete Resource
4. List Resources
5. Search Resource
```

## Function Descriptions

### Add Resource

Prompts the user to enter:

- ID
- Title
- Author
- Topic
- URL
- Description

The resource is appended to `resources.txt`.

---

### Update Resource

Updates an existing resource by its ID.

The program:

1. Reads all resources.
2. Finds the matching ID.
3. Prompts for new information.
4. Saves the updated data into a temporary file.
5. Replaces the original file.

---

### Delete Resource

Deletes a resource by ID.

The program copies every resource except the selected one into a temporary file and replaces the original file.

---

### List Resources

Displays every resource stored in `resources.txt`.

Example:

```
ID: 1
Title: Introduction to C
Author: Dennis Ritchie
Topic: Programming
URL: https://example.com
Description: Basic C programming tutorial
```

---

### Search Resource

Searches for a resource using its ID and displays its information if found.

## File Storage

The application uses plain text storage.

Example:

```text
1 "C Programming" "Dennis Ritchie" "Programming" "https://example.com" "Introduction to C"
2 "Data Structures" "Mark Allen Weiss" "Computer Science" "https://example2.com" "Learning data structures"
```

## Program Workflow

```
Start
   │
   ▼
Display Menu
   │
   ▼
Select Option
   │
   ├── Add Resource
   ├── Update Resource
   ├── Delete Resource
   ├── List Resources
   └── Search Resource
   │
   ▼
Read/Write resources.txt
   │
   ▼
Return to Menu
```

## Known Limitations

- IDs are not checked for uniqueness.
- The program does not validate URLs.
- There is no confirmation before deleting a resource.
- Searching is only possible by ID.
- Error handling for invalid input is limited.
- The menu does not currently include an exit option, although the loop is designed to terminate when `0` is entered.

## Possible Improvements

- Add an Exit option to the menu.
- Validate user input.
- Prevent duplicate IDs.
- Search by title, author, or topic.
- Sort resources alphabetically.
- Export resources to CSV or JSON.
- Improve error handling.
- Store data using a binary file or database.
- Implement pagination for large collections.

## Example Usage

```
Choose option: 1

Enter ID: 10
Enter Title: Learn C
Enter Author: CS50
Enter Topic: Programming
Enter URL: https://cs50.harvard.edu
Enter Description: Free introduction to C
```

Later:

```
Choose option: 4

ID: 10
Title: Learn C
Author: CS50
Topic: Programming
URL: https://cs50.harvard.edu
Description: Free introduction to C
```

## License

This project is intended for educational purposes and may be modified and distributed freely.