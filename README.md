# Ls(1) Command Implementation - Midterm Project

## Overview

This project is a simplified version of the UNIX `ls(1)` command implemented in C. It reads directory contents, extracts file metadata, and formats the output based on various command-line options.

## Implemented Features

The program supports the core behaviors described in the manual page, including:

- **Display Options**: `-a` (all files), `-A` (almost all), `-d` (directory as file).
- **Format Options**: `-l` (long format), `-n` (numeric UID/GID), `-h` (human-readable sizes), `-i` (inode), `-s` (blocks allocated), `-F` (file type indicators).
- **Sorting Options**: `-t` (sort by time), `-S` (sort by size), `-r` (reverse sort), `-f` (no sort).
- **Recursive**: `-R` (recursively list subdirectories).

## Project Structure

- `main.c`: Handles command-line argument parsing and triggers the core logic.
- `myls.c`: Contains the core implementation for reading directories, extracting file statistics, sorting, and formatting.
- `myls.h`: Header file containing struct definitions and function prototypes.
- `Makefile`: Script to automate the compilation process.

## How to Compile and Run

1. Run `make` in the terminal to compile the program.
2. Execute the program: `./myls [options] [directory]`
   - Example 1: `./myls -l -a`
   - Example 2: `./myls -lhS`
   - Example 3: `./myls -R`
3. Run `make clean` to remove the compiled object files and binaries.
