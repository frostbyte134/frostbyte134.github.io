---
layout: post
title:  "The C Programming Language (TCPL)"
date:   2019-9-11 09:00:05 +0800
categories: coding
use_math: true
tags: coding c
---

### Chap 1
- C is a general-purpose programming anguage. It has been closely associated with the UNIX system where it was developed, since both the system and most of the programs that run on it are written in C

- A `preprocessing step` performs macro substitution on program text, inclusion of other source files, and `conditional compilation`
  - a `#define` line defines a `symbolic name` or symbolic constant to be a particular string of characters \\[\text\{#define name replacement\} \\] any occurance of `name` (not in quotes and not part of another name) will be __replaced__ by the corresponding `replacement` text.

- C offers only straightforward, __single-thread control flow__: tests, loops, grouping, and subprograms, but not multiprogramming, parallel operations, synchronization, of coroutines.
- `printf("6.2f\n", float_val);`
  - `%o` for octal, `%x` for hexadecimal, `%%` for % itself

#### Call by value
- In C, __all function arguments are passed "by value"__. This means that the called function is given the values of its arguments in temporary variables (copy), rather than the originals.
> Call by value is an asset, however, not a liability. It usually leads to more compact programs with fewer extraneous variables, because parameters can be treated as conveniently initilaized local variables in the called routine.

No call by reference, but we can bypass it by using pointer
- When necessary, it is possible to arrange for a function (called routine) to modify a variable in a calling routine. The called function must __declare the parameter to be a pointer__, and access the variable indirectly through it.
- When the name of an array is used as an argument, the value passed to the function is the location or address of the beginning of the array - there is no copying of array elements.

#### Variables
The scope (lifetime) of variables may be
- internal to a function, (automatic)
- external but known only within a single source file, (static)
- or visible to the entire program (external)

1. local variables
   - We will use the term `automatic` henceforth to refer to these __local variables__
   - come and go with function invocation
2. external variable
   - variables that are external to all fuctnions (can be accessed by name by any function)
   - retain their values even after the functions that set them have returned
   - __an external variable must be defined, exactly once, outside of any function__
   - the variable must also be decared in each function that wants to access it;
     - `extern int N;`
     - In certain circumstances, the `extern` declaration can be omitted.
     - If the __definition__ of  an external variable occurs in the source file before its use in a particular function, then there is no need for an extern declaration in the function (vars outside main function, in PS)
     - If the program is in several source files, and a variable is defined in file1 and used in file2 or 3, then `extern` declarations are needed in file2, 3.
     - The _usual practice_ is to collect extern declarations of variables and functions in a separate header file, that is included by `#include` at the front of each source file.
     - `static global variable`: when we define static variable outside any function, the `static` keyword restricts the lifecycle of the variable within the file. (not golbally accessble, even though it is defined outside of any function)

- `Definition` refers to the place where the variable is created or assigned storage
- `declaration` refers to places where the nature of the variable is stated, but no storage is allocated

> Relying too heavily on external variables is fraught with peril since it leads to programs whose data connections are not at all obvious - variables can be changed in unexpected and even inadvertent ways, and the program is hard to modify.


### Chap 2 Types, Operators and Expressions
- floating-point operations may be done in single precision(?); there is also a `long double` type for extended precision
- __string constants may be concatenated at compile time__  
  `printf("Hello, " /* Cruel */ "World!\n");` gives Hello World
- > Don't begin variable names with underscore, however, since library routines often use such names
- `short` and `long` apply to integers. The intent is that they should provide different lengths of integers __where practical__(!!!);
- `short`s and `ints` are at least 16 bits
- `long`s are at least 32bits
- `short` is no longer than int, which is no longer than `long`. Therefore, int can be 16 or 32, but short/longs are not
- as with integers, __the sizes of floating-point objects are implementation-defined__; `float`, `double` and `long double` could represnet 1, 2 or 3 distinct sizes

#### Constants
- `1234` or `1234` = int
- `1234L` or `1234l` = long
- `1234UL` or `1234ul` = unsigned long
- `1234.5` or `1234.5` = double
- `1234.5f` or `1234.5F` = float
- `1234.5l` or `1234.5L` = long double
- leading `0` = octal, `0x` or `0X` = hexidecimal 
  - `0XFUL`: unsigned long constant with value 15 decimal.
- `\\0` = 0 = null character
- a `string constant`, or `string literal`, is a sequence of zero or more chars surrounded by double quotes.
  - Technically, a string constant is an array of chars. The internal represnetation of a string has a null char 0 at the end ~~. This representation means that __there is no limit to how long a string can be__, but programs must scan a string completely to determine its length.
  - __be careful to distinguish__ between a char constant 'x' and a string that contains a single character "x". the former is an integer, used to produce the numeric value of the letter x in the machine's char set. The latter is an array of chars that contains one character and a 0.

#### Declarations
* a var may also be initialized in its declaration. if the name is followed by an equal sign and an expression, the expression serves as an initializer.
* If the var in question is not automatic, the initializeon is done once only, __conceptually b4 the program starts executing__, and the initializer must be a constant expression.
* An explicitly initialized automatic variable is initialized each time the function or block it is in is entered;

> External and static variables are initialized to zero by default. Automatic vars for which there is no explicit initializer have undefiend (i.e. garbage) values.

#### Arithmetic operators
* the `%` operator cannot be applied to `float` or `double`
* The direction of truncation for `/` and the sign of the result for `%` are machine-dependent for negative operands, as is the action taken on overflow or underflow (????).

#### Relational operators
- short-curcuit

#### Type casting
* Skipped the upper part
* Notice that `floats` in an expression __are not automatically converted to__ `double`.
* In general, math functions like those in `<math.h>` will use double precision.
* comparison between signed and unsigned values are machine-dependent, b/c they depend on the sizes of the various integer types. (example follows)
* Longer integers are converted to shorter ones or to `chars` by __dropping the excess high-order bits__.
* When `double` is converted to `float`, whether the value is rounded or truncated is implementation-dependent

#### assignment
assignment statement has a value and can occur in expressions

#### example
* `x &= (x-1);` deletes the rightmost 1-bit in `x`
* `a[i] = i++;` compilers can interpret this in different ways, and generate different answers depending on their interpretation. __The standard intentionally leaves most such matters unspecified.__