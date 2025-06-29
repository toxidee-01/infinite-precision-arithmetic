## Readme

Infinite Arithmetic Library  
This library provides two classes which can be used to create large instances of Integers which can't be used using the basic datatypes and hence performing arbitrary precision arithmetic operations on integers and floating point numbers created by the class.

### 1 Arbitrary size

The integer class as well as the float class represents integers of arbitrary size without having an overflow or underflow.

### 2 Private variables

If we want to use the integer or the float value outside that of a class function we can do it by using a val function that is described in the library.

### 3 Outstream

If we want to print an Integer which is a private variable it is ok to directly use a `cout` because we have overloaded the `<<` operator making it easy for us to print the outcome after using the overloaded functions.

### 4 Operator overloading

We can do addition, subtraction, multiplication, and division for various objects as we are returning the same object again after performing the operation and hence multiple operations between Integers or between Floats is possible.

### 5 Constructor

The Constructor has been made such that when not given any value the default Constructor is called and the values are initialized.

#### 5.1 Integers

The Constructor is such that the leading zeroes are removed by itself when called using that Constructor.

```cpp
Integer a("1234567");
Integer b = Integer::parse("-009876321");
// leading 0s in b are removed

Integer c = a + b;
Integer d = a - b;
Integer e = a * b;
Integer f = a / b;

std::cout << "a = " << a << std::endl;
// can directly print it
```

#### 5.2  Floats

The Constructor when given a string only can itself remove all the trailing and leading zeroes and also find the place value of the decimal and initiates it. If we have been given a Float without a decimal point then it automatically adds a decimal point and a 0 after that so we don't have to worry about it being given an integer value.

```cpp
Float a("123.4567");
Float b = Integer::parse("-009876.3210");
// leading and trailing 0s in b are removed
Float c = a + b;
Float d = a - b;
Float e = a * b;
Float f = a / b;
std::cout << "a = " << a << std::endl;
// can directly print it
```
