# Image Template Class

A comprehensive C++ template class for working with 2D images (rectangular arrays) with arbitrary width, height, and element type.

## Overview

This project implements a generic `Image<T>` template class that provides a flexible and efficient way to work with 2D arrays of any data type. The implementation demonstrates advanced C++ template programming concepts including:

- Template specialization
- Type deduction and common type handling
- Operator overloading
- Variadic templates
- SFINAE principles

## Features

### Core Functionality

- **Multiple constructors**: Default, copy, parameter-based, and type-conversion constructors
- **Element access**: Safe pixel access with support for negative indices (counting from the end)
- **Dimension queries**: Get width and height of images
- **Input/Output**: Console-based input and formatted output methods

### Arithmetic Operations

#### Image-to-Image Operations
- Addition (`+`): Element-wise addition of two images
- Subtraction (`-`): Element-wise subtraction
- Multiplication (`*`): Element-wise multiplication
- Division (`/`): Element-wise division with zero-division protection

#### Scalar Operations
- Addition, subtraction, multiplication, and division with scalar values
- Automatic type promotion for mixed-type operations

### Image Manipulation

- **Type Conversion**: Convert image elements to different data types
- **Scaling**: Upscale images by integer factors (different for width and height)
- **Concatenation**: Horizontal and vertical image merging
- **Subimage Extraction**: Extract rectangular regions with template parameters
- **Dynamic Cropping**: Runtime-based subimage extraction

### Advanced Features

- **Variadic Templates**: Unite multiple images in a single function call
- **Image Builder**: Create images from parameter lists with compile-time size checking
- **Type Safety**: Automatic result type deduction using `std::common_type`
- **Exception Handling**: Comprehensive error checking for invalid operations

## Project Structure

```
├── image.h         # Header file with class declaration
├── image.hpp       # Implementation file with method definitions
├── task.cpp        # Demo program with interactive menu
└── README.md       # This file
```

## Usage Examples

### Basic Usage

```cpp
#include "image.h"

// Create a 3x3 integer image filled with value 5
Image<int> img1(3, 3, 5);

// Create an image from another image with type conversion
Image<double> img2(img1);

// Access pixels (supports negative indices)
img1.setPixel(0, 0, 10);
int value = img1.getPixel(0, 0);
int lastPixel = img1.pixel(-1, -1); // Bottom-right corner
```

### Arithmetic Operations

```cpp
Image<int> img1(2, 2, 3);
Image<int> img2(2, 2, 2);

// Image arithmetic
auto sum = img1 + img2;        // Element-wise addition
auto diff = img1 - img2;       // Element-wise subtraction
auto product = img1 * img2;    // Element-wise multiplication
auto quotient = img1 / img2;   // Element-wise division

// Scalar arithmetic
auto scaled = img1 * 2.0;      // Multiply all elements by 2
auto shifted = img1 + 10;      // Add 10 to all elements
```

### Image Manipulation

```cpp
// Type conversion
Image<int> intImg(3, 3, 5);
auto doubleImg = intImg.convert<double>();

// Scaling (template parameters: height_scale, width_scale)
auto enlarged = intImg.upscale<2, 3>(); // 2x height, 3x width

// Concatenation
Image<int> left(2, 2, 1);
Image<int> right(2, 3, 2);
auto combined = left.concatHorizontal(right); // 2x5 result

// Subimage extraction
auto cropped = img.subimageDynamic(0, 1, 0, 1); // Extract 2x2 region
```

### Advanced Features

```cpp
// Create image from values with compile-time checking
auto img = make_image<2, 3, int>(1, 2, 3, 4, 5, 6);

// Unite multiple images horizontally
auto united = unite_horizontal(img1, img2, img3, img4);
```

## Interactive Demo

The project includes a comprehensive demo program (`task.cpp`) with an interactive menu system that allows you to:

1. Create images
2. Display images
3. Perform horizontal/vertical merging
4. Execute arithmetic operations
5. Crop images
6. Test scalar operations

To run the demo:

```bash
g++ -std=c++17 task.cpp -o demo
./demo
```

## Template Parameters and Type Safety

The class uses advanced template metaprogramming:

- **Type Deduction**: Automatic result type calculation using `std::common_type`
- **SFINAE**: Compile-time type checking and constraint enforcement
- **Variadic Templates**: Support for operations on multiple images
- **Template Specialization**: Optimized implementations for specific types

## Error Handling

The implementation includes comprehensive error checking:

- Dimension mismatch validation for binary operations
- Bounds checking for pixel access
- Division by zero protection
- Invalid parameter validation for cropping operations

## Requirements

- C++17 or later
- Standard Template Library (STL)
- Compiler with template support (GCC, Clang, MSVC)

## Building

```bash
# Compile the demo program
g++ -std=c++17 -Wall -Wextra task.cpp -o image_demo

# Run the interactive demo
./image_demo
```

## Implementation Highlights

### Template Design
- Extensive use of SFINAE for type constraints
- Automatic type promotion in mixed-type operations
- Compile-time parameter validation

### Memory Management
- Efficient 2D vector-based storage
- Copy-on-write semantics where applicable
- No manual memory management required

### Performance Features
- Template instantiation minimizes runtime overhead
- Efficient element access patterns
- Optimized copying and assignment operations

## Contributing

This project was developed as part of an Object-Oriented Programming course. The implementation demonstrates:

- Modern C++ template techniques
- Object-oriented design principles
- Generic programming best practices
- Exception safety and error handling

## Acknowledgments

Special thanks to the course instructor for guidance on advanced C++ template programming techniques and object-oriented design principles.
