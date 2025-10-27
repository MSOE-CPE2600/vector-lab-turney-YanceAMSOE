# Vector Lab (Turney-YanceAMSOE)

## Overview

**Vector Lab** is a C application for creating and manipulating named 3D vectors from the command line. Users can define vectors, perform arithmetic (addition, subtraction, scalar multiplication), list vectors, and save or clear them. It features a menu-driven interface and optionally supports dynamic memory management for flexible scaling.

---

## Building

Use the included Makefile for ease, or compile manually:

**With Makefile:**
```sh
make
```

**Manual gcc compile:**
```sh
gcc -o vectorlab vect.c DM.c
```

---

## Running

Launch the lab in a terminal:

```sh
./vectorlab
```

The prompt appears as:
```
VectorLab>
```
Enter commands interactively after that.

---

## Commands

| Example                       | What It Does                                  |
|-------------------------------|-----------------------------------------------|
| `name = x y z`                | Store or update vector (e.g. `a = 1 2 3`)     |
| `name`                        | Display a vector’s value (`a`)                |
| `a + b`                       | Add vectors                                   |
| `a - b`                       | Subtract vectors                              |
| `a * s` or `s * a`            | Multiply by scalar                            |
| `c = a + b`                   | Store sum in new or existing vector           |
| `c = a - b`                   | Store difference in vector                    |
| `c = a * s` or `c = s * a`    | Store scalar product in named vector          |
| `list`                        | List all vectors                              |
| `clear`                       | Remove all vectors from memory                |
| `save`                        | Save vectors to .csv file                     |
| `-h`                          | Display help                                  |
| `quit`                        | Exit program                                  |

- Names: Up to 30 characters.
- Numbers: Decimals supported.

---

## Usage Examples

- `a = 1 2 3`    # Set vector `a`
- `b = 4 5 6`
- `a + b`        # Show sum
- `list`         # List vectors
- `save`         # Save to file
- `clear`        # Wipe memory
- `quit`         # Exit

---

## Dynamic Memory Notes

Out of the box, the lab keeps up to 10 vectors using a fixed array. For dynamic growth, support files (`DM.c`, `DM.h`) let you enable heap-based storage, so you can store more than 10 vectors. To experiment with dynamic resizing and memory management, enable the relevant calls in your vector functions.

You can explore both static and dynamic management patterns by modifying which version you compile and how you handle vectors behind the scenes.

---
