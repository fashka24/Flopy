# Flopy

## Description

**Flopy** is a functional programming language designed for fast and easy interpretation. It utilizes **Just-In-Time (JIT)** compilation to achieve high performance and flexibility.

## Features

- **Functional Style**: Support for pure functions, higher-order functions, and lambda expressions.
- **JIT Compilation**: Compiles code at runtime for enhanced performance.
- **Simple Syntax**: Easily readable and understandable syntax inspired by `Python`.
- **Extensibility**: Easy to add new features and libraries.
- **Cross-Platform**: Supports various operating systems, including Windows, macOS, and Linux.

## Installation

### Requirements

- C++ compiler (>= C++17)
- Cmake
- Python (for auto-installation script)

### Installation Steps

1. Clone the repository:
```bash
git clone https://github.com/fashka24/Flopy.git
```
2. Compile project
```bash
cmake --build . --target fli -j 18
```
3. Test it
```bash
./fli example/hello-world.flp
```

## Byte-code

Byte-code has 1 argument syntax and inspired by `Python VM`.

### Source code
```python
puts("Hello world!\n")
```
### Byte code
```asm
LOAD_CONST "Hello world\n"  ;; push string to stack
LOAD_FUNCTION "puts"        ;; push function "puts" to call stack
CALL 1                      ;; call top function in call stack with 1 arguments from top of stack ("Hello world\n")
HALT                        ;; end of program for byte code interpreter
```