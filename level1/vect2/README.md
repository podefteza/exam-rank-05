# C++ Exercise: vect2 - Operator Overloading Guide

## 1. General Overview

The `vect2` exercise is a fundamental C++ project designed to teach and test your understanding of **Object-Oriented Programming (OOP)**, specifically **operator overloading**.

The main goal is to create a class that represents a 2D vector (with `x` and `y` coordinates) and make it behave like a native C++ type (like `int` or `float`). This means you'll be able to use standard arithmetic (`+`, `*`), comparison (`==`), and stream (`<<`) operators directly on your `vect2` objects.

---

## 2. The "Trick": A Logical Implementation Strategy

The most efficient way to tackle this exercise is to build and test it incrementally. Don't try to write all the code at once. The "trick" is to start with a minimal, testable skeleton and add one operator at a time.

### Step 1: Create the Skeleton

Your first goal is to get something compiling that you can print. This provides an immediate feedback loop.

1.  **`vect2.hpp`:**
    *   Define the `vect2` class.
    *   Add private integer members: `int x;` and `int y;`.
    *   Declare a default constructor `vect2();` and a parameterized one `vect2(int x, int y);`.
    *   **Crucially, declare the stream insertion operator as a `friend`:**
        ```cpp
        friend std::ostream &operator<<(std::ostream &os, const vect2 &v);
        ```

2.  **`vect2.cpp`:**
    *   Implement the two constructors. Initialize `x` and `y` to `0` in the default constructor.
    *   **Implement `operator<<`:** This is your most important debugging tool. Make it print the vector in the required format, e.g., `{x, y}`.
        ```cpp
        std::ostream &operator<<(std::ostream &os, const vect2 &v) {
            os << "{" << v.x << ", " << v.y << "}";
            return os;
        }
        ```

At this point, you can write a `main` that creates `vect2` objects and prints them with `std::cout`. You can now verify every subsequent step.

### Step 2: Implement Incrementally

Now, add features one by one, compiling and testing after each addition.

1.  **Orthodox Canonical Form:** Add and implement the copy constructor, copy assignment operator (`operator=`), and destructor.
2.  **Subscript Operator (`[]`):** Implement `int &operator;` and its `const` counterpart. This is often used by the subject's `main` for testing.
3.  **Simple Arithmetic (`+`, `-`, `*`):** These operators should return a *new* `vect2` object by value.
4.  **Compound Assignment (`+=`, `-=`, `*=`):** These modify the current object (`*this`) and **must return a reference (`vect2 &`)** to allow for chaining (e.g., `v1 += v2 += v3;`).
5.  **Increment/Decrement (`++`, `--`):** Implement both prefix and postfix versions. This is a common place for errors (see "Tricks" below).
6.  **Commutative Multiplication:** Add the non-member free function `operator*(int scalar, const vect2 &v)` to handle cases where the scalar is on the left.

---

## 3. Key Concepts & Common "Tricks"

Pay close attention to these details, as they are the core of the evaluation.

*   **Prefix vs. Postfix Increment/Decrement:**
    *   **Prefix (`++v`):** Modifies the object first, then returns a reference to the *modified* object (`vect2 &`).
    *   **Postfix (`v++`):** Must store a temporary copy of the object's original state, modify the actual object, and then return the *unmodified copy* by value (`vect2`). The signature is differentiated by a dummy `int` parameter: `vect2 operator++(int);`.

*   **Return Types are Critical:**
    *   Compound assignment operators (`+=`, `-=`, `*=`) and prefix increment/decrement (`++v`, `--v`) must return `vect2 &`.
    *   Arithmetic operators (`+`, `-`, `*`) and postfix increment/decrement (`v++`, `v--`) must return `vect2` by value.

*   **Commutativity with Non-Member Functions:**
    *   A member function like `operator*(int scalar)` handles `v * 5`.
    *   It cannot handle `5 * v` because the integer is on the left. You **must** implement this as a non-member (global) function.
    *   **Best Practice:** Have the non-member function simply call the member function to avoid duplicating code: `return v * scalar;`.

*   **The `operator[]` Overloads:**
    *   The non-`const` version must return `int &` to allow assignment (e.g., `v[0] = 42;`).
    *   You must also provide a `const` version that returns `const int &` for use with constant `vect2` objects.

*   **`operator<<` as a `friend`:**
    *   The stream insertion operator must be a non-member function.
    *   To access the private `x` and `y` members of your class, it needs to be declared as a `friend` inside the class definition.
    *   It must return `std::ostream &` to allow chaining (`std::cout << v1 << v2;`).

*   **`const`-Correctness:**
    *   Any member function that does not modify the state of the object should be marked as `const`. This includes getters, comparison operators, and arithmetic operators.
