```markdown
# CIS3360 Checksum Calculator

A C++ program to compute 8, 16, or 32-bit checksums for text files, as assigned in **CIS3360: Security in Computing** at the University of Central Florida (Summer 2025).

This project demonstrates file I/O, command-line argument handling, bit manipulation, and checksum algorithms with overflow management.

## Project Overview

- Takes an input file and checksum size (8/16/32) as command-line arguments.
- Echoes input text (80 characters per line).
- Pads with 'X' if needed for word alignment.
- Computes checksum by summing words (ignoring overflow).
- Outputs result in hexadecimal format.

## My Implementation

Implemented solo:
- Validated command-line arguments and file access.
- Echoed input with proper line wrapping.
- Handled padding and checksum calculation using bit masks (e.g., 0xFF for 8-bit).
- Simulated big-endian behavior as required.

## How to Build and Run

### Requirements
- G++ compiler

### Compilation
```bash
g++ -o pa01 pa01.cpp
```

### Execution
```bash
./pa01 input.txt 16
```
- Replace `input.txt` with your own test file and choose checksum size (8, 16, or 32).

## Credits & Attribution

- Assignment guidelines by Michael McAlpin, UCF CIS3360.
- Implemented as a solo academic project – shared for portfolio purposes only.

## License / Usage Note

Developed for UCF coursework. Feel free to view and learn from it, but do not use it to complete active assignments in CIS3360 or similar courses.

---

**Christopher Otto**  
Computer Science B.S. Candidate, Class of 2027  
University of Central Florida
