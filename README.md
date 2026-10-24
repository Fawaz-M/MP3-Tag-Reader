# MP3 Tag Reader and Editor in C

## Project Overview

The MP3 Tag Reader and Editor is a command-line application developed using the C programming language. It allows users to read and modify metadata stored in MP3 audio files.

MP3 files contain ID3 tags that store information about a song, such as its title, artist, album, release year, genre, and comments. This project demonstrates how to access and update metadata using file handling and binary file operations in C.

## Features

- View metadata information from an MP3 file.
- Edit supported metadata fields.
- Use command-line arguments to select operations.
- Validate command-line arguments and file extensions.
- Perform file handling using C.
- Work with ID3 metadata and binary file operations.
- Display help information for command usage.

## Technologies Used

- Programming Language: C
- Concepts: File Handling, Pointers, Structures, Arrays, Strings, Command-Line Arguments
- File Format: MP3
- Metadata Standard: ID3 tags
- Development Environment: Linux / GCC

## Project Structure

```text
MP3-Tag-Reader/
├── main.c
├── view.c
├── edit.c
├── Help.c
├── oprcheck.c
├── sizecon.c
└── mp3.h
```

## Compilation

Open a terminal in the project directory.

Compile the source files using GCC:

```bash
gcc main.c view.c edit.c Help.c oprcheck.c sizecon.c -o mp3reader
```

If your project uses additional source files or different function definitions, adjust the compilation command accordingly.

## How to Run the Program

The application uses command-line arguments. These arguments are entered in the terminal after the executable name.

### 1. Display Help

```bash
./mp3reader -h
```

This option displays the available operations and usage instructions, if supported by your implementation.

### 2. View MP3 Metadata

```bash
./mp3reader -v sample.mp3
```

Here:

- `./mp3reader` runs the compiled application.
- `-v` selects the view operation.
- `sample.mp3` is the MP3 file whose metadata you want to read.

The program should display the metadata fields supported by your implementation.

### 3. Edit MP3 Metadata

The following is an example of the general command-line format:

```bash
./mp3reader -e -t "New Song Title" sample.mp3
```

In this example:

- `-e` selects the edit operation.
- `-t` represents a title option **only if your program implements it**.
- `"New Song Title"` is the new title.
- `sample.mp3` is the target MP3 file.

The exact editing syntax depends on the options implemented in your source code. Refer to the help output from `./mp3reader -h` for the supported flags.

## Understanding Command-Line Arguments in C

Command-line arguments allow users to provide input when starting a program, without entering each value interactively.

The `main()` function commonly accepts two parameters:

```c
int main(int argc, char *argv[])
```

- `argc`: The number of command-line arguments, including the program name.
- `argv`: An array of strings containing the arguments.

For example:

```bash
./mp3reader -v sample.mp3
```

The arguments are conceptually:

| Argument | Value |
|---|---|
| `argv[0]` | `./mp3reader` |
| `argv[1]` | `-v` |
| `argv[2]` | `sample.mp3` |
| `argc` | `3` |

Your program can inspect these values to determine which operation to perform and which file to process.

## Sample Workflow

1. Compile the source files using GCC.
2. Run the program with `-h` to inspect the available options.
3. Pass an MP3 filename with the view option to inspect its metadata.
4. Use the supported edit options to update metadata.
5. Open the MP3 file in a media player or tag editor to verify the changes.

## Learning Outcomes

Through this project, I gained practical experience with:

- File handling in C.
- Command-line argument processing.
- Structures, pointers, and string manipulation.
- Binary file operations.
- Reading and modifying MP3 metadata.
- Modular programming across multiple source
