# DirDepth
Command-line utility that calculates the depth of the filesystem tree starting from the current directory. It traverses directories recursively to determine the deepest directory and provides the depth of the directory structure.
## Installation

To install the `DirDepth` utility, compile the source code and move the executable to a directory in your PATH. You can use the provided Makefile to simplify this process:

```sh
make
make install
```

## Usage

Run the `depth` command followed by the directory path you want to analyze. If no directory is specified, it will use the current directory. Use the `--verbose` flag for detailed output.

```sh
depth [--verbose] [directory_path]
```

### Examples

Calculate the depth of the current directory:

```sh
depth
```

Calculate the depth of a specified directory:

```sh
depth /path/to/directory
```

Calculate the depth of a specified directory with verbose output:

```sh
depth --verbose /path/to/directory
```