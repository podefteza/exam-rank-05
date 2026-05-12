# bigint

## Goal
The exercise is to create an **arbitrary precision unsigned integer** class.

That means the number should not be limited by `unsigned long long` or `size_t`. You store the value yourself, usually as a `std::string`, and implement the operations manually.

The required behavior is:
- default construction gives `0`
- construction from an integer
- copy construction and assignment
- printing with `<<`
- addition with `+` and `+=`
- prefix and postfix `++`
- digit shift operators `<<`, `>>`, `<<=`, `>>=`
- comparisons: `<`, `<=`, `>`, `>=`, `==`, `!=`

## Main Idea
A bigint is easier to understand if you think of it as a string of decimal digits.

Example:
- `42` is stored as `"42"`
- `1337` is stored as `"1337"`

The class is not doing binary arithmetic. The shift operators are **digit shifts in base 10**:
- `42 << 3` becomes `42000`
- `1337 >> 2` becomes `13`

## Simple Data Representation
The easiest exam-friendly approach is:
- store the digits in normal order
- keep `"0"` as the default value
- never allow an empty string to represent zero

This makes printing very simple because the stored value is already in the correct order.

## How To Solve It

### 1. Constructor
Use `std::to_string(number)` for the constructor from an integer.

This is the simplest way to build the internal string.

### 2. Printing
The `<<` stream operator just outputs the stored string.

If you never store leading zeros, the output is already correct.

### 3. Addition
To add two bigints:
- start from the last digit of both strings
- add corresponding digits and carry
- build the result from left to right
- stop when both numbers are finished and carry is zero

This is the standard school addition algorithm.

### 4. `+=`
Implement `+=` using `+`:
- `*this = *this + other`
- return `*this`

### 5. `++`
Implement increment by reusing addition with `1`.

- prefix `++x` returns the incremented object
- postfix `x++` saves a copy first, increments, then returns the old value

### 6. Digit Shift Left
Left shift by `n` digits means append `n` zeros to the end.

Example:
- `42 << 3` -> `42000`

### 7. Digit Shift Right
Right shift by `n` digits means remove `n` digits from the end.

Example:
- `1337 >> 2` -> `13`

If the shift is larger than the number length, the result should be `0`.

### 8. Comparisons
Comparisons should not rely on normal string order alone unless lengths are equal.

Correct logic:
- if sizes differ, the longer number is larger
- if sizes are equal, compare digit by digit from left to right

That is why `9 < 10` must be handled by size first, not by raw string comparison.

## Good Mental Model For The Exam
Remember the class in this order:
1. store digits as a string
2. print the string
3. add from right to left
4. shift by adding/removing zeros
5. compare by size, then digits

If you can remember those five steps, the whole exercise becomes manageable.

## Common Mistakes
- using an empty string instead of `"0"`
- using string comparison directly for different lengths
- forgetting carry in addition
- forgetting the special case when right shift removes all digits
- making `++` mutate incorrectly or return the wrong value for postfix

## Exam Strategy
If you want the easiest version to remember, keep the implementation simple and consistent:
- normal digit order
- constructor with `std::to_string`
- add from the end
- shift with `insert` and `erase`
- compare by length first

That version is easy to reconstruct under time pressure.
