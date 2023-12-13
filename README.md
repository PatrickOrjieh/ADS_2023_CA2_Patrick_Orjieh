# Project Title: XML-Based Directory Tree File Manager

## Description
This project is an XML-Based Directory Tree Visualizer developed as part of Algorithms and Data Structures. It parses an XML file representing a directory structure, including files and subdirectories, and provides a command-line interface (CLI) for various operations. Additionally, the project uses the  SFML library for graphical representation of the directory tree(Not fully implemented).

## Features
1. **XML Parsing**: Reads an XML file to construct a tree representing the directory structure.
2. **CLI Operations**: Perform operations such as counting items in a folder, determining memory usage, pruning empty directories, and finding files/folders.
3. **SFML Integration**: Visual representation of the root directory.
4. **Breadth-First Search (BFS) Algorithm**: Used for memory calculation and tree traversal.
5. **Depth-First Search (DFS) Algorithm**: Implemented for searching files or folders in the tree.

## Installation
1. **Clone the Repository**: `git clone https://github.com/PatrickOrjieh/ADS_2023_CA2_Patrick_Orjieh.git`


## Usage
Run the compiled executable. The program will prompt you to enter the path to an XML file. After loading the file, it will display a menu with various options. Choose an option by entering the corresponding number.

For graphical display, select the SFML option from the menu. This will open a new window showing the directory tree.

## Project Structure
- `main.cpp`: Entry point of the application.
- `XMLValidator.h/cpp`: Validates the XML file.
- `XMLParser.h/cpp`: Parses XML files and constructs the directory tree.
- `Tree.h/cpp` and `TreeIterator.h/cpp`: Implements the tree data structure and iterator.
- `Dir.h/cpp` and `File.h/cpp`: Represents directory and file nodes.
- `TreeUtilities.h/cpp`: Provides utility functions for tree operations.
- `DirectoryVisual.h/cpp`: Handles SFML-based graphical display of the tree.

- **Author**: Patrick Orjieh
- **Institution**: Dundalk Institute of Technology




