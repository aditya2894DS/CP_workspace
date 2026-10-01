# C++ Cheatsheet

A quick reference for C++ syntax and common features.

## Table of Contents

- [Basic Structure](#basic-structure)
- [Comments](#comments)
- [Data Types](#data-types)
- [Variables & Constants](#variables--constants)
- [Input / Output](#input--output)
- [Operators](#operators)
- [Conditionals](#conditionals)
- [Loops](#loops)
- [Functions](#functions)
- [Arrays](#arrays)
- [Strings](#strings)
- [Pointers & References](#pointers--references)
- [Dynamic Memory](#dynamic-memory)
- [Structures & Enums](#structures--enums)
- [Object-Oriented Programming](#object-oriented-programming)
- [Templates](#templates)
- [STL Containers](#stl-containers)
- [STL Algorithms](#stl-algorithms)
- [File Handling](#file-handling)
- [Exception Handling](#exception-handling)
- [Modern C++ Features](#modern-c-features)

---

## Basic Structure

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

- `#include` adds header files to the program.
- `main()` is where the program starts running.
- `return 0;` tells the OS that the program ended successfully.

---

## Comments

```cpp
// Single-line comment

/*
   Multi-line
   comment
*/
```

---

## Data Types

| Type     | Example               | Typical Size |
|----------|-----------------------|--------------|
| `int`    | `int a = 10;`         | 4 bytes      |
| `float`  | `float f = 3.14f;`    | 4 bytes      |
| `double` | `double d = 3.14159;` | 8 bytes      |
| `char`   | `char c = 'A';`       | 1 byte       |
| `bool`   | `bool ok = true;`     | 1 byte       |
| `void`   | Means "no value"      | –            |

**Modifiers:** `short`, `long`, `long long`, `signed`, `unsigned`

```cpp
unsigned int u = 42;
long long big = 9000000000LL;
```

---

## Variables & Constants

```cpp
int age = 21;               // variable
const double PI = 3.14159;  // constant (cannot be changed)
constexpr int SIZE = 100;   // compile-time constant
auto x = 5;                 // the type is worked out automatically (int)
#define MAX 50              // preprocessor macro
```

---

## Input / Output

```cpp
int n;
cin >> n;                       // read a value
cout << "Value: " << n << "\n"; // print a value

string line;
getline(cin, line);             // read a whole line, including spaces
```

Formatted output with `<iomanip>`:

```cpp
#include <iomanip>
cout << fixed << setprecision(2) << 3.14159; // 3.14
cout << setw(10) << 42;                      // right-aligned in a 10-character field
```

---

## Operators

| Category   | Operators                                  |
|------------|--------------------------------------------|
| Arithmetic | `+  -  *  /  %`                            |
| Relational | `==  !=  >  <  >=  <=`                     |
| Logical    | `&&  \|\|  !`                              |
| Bitwise    | `&  \|  ^  ~  <<  >>`                      |
| Assignment | `=  +=  -=  *=  /=  %=`                    |
| Increment  | `++x  x++  --x  x--`                       |
| Ternary    | `cond ? a : b`                             |
| Misc       | `sizeof`, `&` (address), `*` (dereference) |

---

## Conditionals

### if / else if / else

```cpp
if (x > 0) {
    cout << "Positive";
} else if (x < 0) {
    cout << "Negative";
} else {
    cout << "Zero";
}
```

### Ternary

```cpp
string result = (x % 2 == 0) ? "Even" : "Odd";
```

### switch

```cpp
switch (day) {
    case 1:  cout << "Monday";  break;
    case 2:  cout << "Tuesday"; break;
    default: cout << "Other day";
}
```

---

## Loops

### for

```cpp
for (int i = 0; i < 5; i++) {
    cout << i << " ";
}
```

### Range-based for

```cpp
vector<int> v = {1, 2, 3};
for (int x : v) cout << x;
for (auto &x : v) x *= 2;   // use a reference to change the elements
```

### while

```cpp
int i = 0;
while (i < 5) {
    cout << i++;
}
```

### do-while

```cpp
int i = 0;
do {
    cout << i++;
} while (i < 5);   // the body always runs at least once
```

### break & continue

```cpp
for (int i = 0; i < 10; i++) {
    if (i == 3) continue; // skip this iteration
    if (i == 7) break;    // leave the loop
}
```

---

## Functions

```cpp
int add(int a, int b) {
    return a + b;
}
```

### Default arguments

```cpp
void greet(string name = "Guest") {
    cout << "Hello, " << name;
}
```

### Pass by value vs. by reference

```cpp
void byValue(int x)      { x = 10; } // works on a copy; the original is unchanged
void byRef(int &x)       { x = 10; } // changes the original
void byPtr(int *x)       { *x = 10; } // changes the original through a pointer
void readOnly(const string &s) {}    // no copy and no changes allowed
```

### Function overloading

```cpp
int    area(int s)            { return s * s; }
double area(double l, double b) { return l * b; }
```

### Inline & recursive functions

```cpp
inline int square(int x) { return x * x; }

int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
```

### Lambda expressions

```cpp
auto sum = [](int a, int b) { return a + b; };
cout << sum(2, 3);   // 5

int k = 10;
auto addK = [k](int x) { return x + k; };   // capture by value
auto incK = [&k]() { k++; };                // capture by reference
```

---

## Arrays

```cpp
int arr[5] = {1, 2, 3, 4, 5};
cout << arr[0];                         // first element
int len = sizeof(arr) / sizeof(arr[0]); // number of elements

int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
cout << matrix[1][2];  // 6
```

---

## Strings

```cpp
#include <string>

string s = "Hello";
s.length();            // 5
s += " World";         // join strings
s.substr(0, 5);        // "Hello"
s.find("World");       // index of the match, or string::npos if not found
s.replace(0, 5, "Hi"); // replace part of the string
s.empty();             // true if the string is empty
s[0];                  // access a character
to_string(42);         // int -> string
stoi("123");           // string -> int
stod("3.14");          // string -> double
```

---

## Pointers & References

```cpp
int x = 10;
int *p = &x;   // p holds the address of x
cout << *p;    // 10 (dereference)
*p = 20;       // x is now 20

int &ref = x;  // ref is another name for x
ref = 30;      // x is now 30

int *np = nullptr;  // a pointer that points to nothing
```

### Pointer arithmetic

```cpp
int arr[3] = {10, 20, 30};
int *ptr = arr;
cout << *(ptr + 1);  // 20
```

---

## Dynamic Memory

```cpp
int *p = new int(5);       // allocate one int
delete p;                  // free it

int *arr = new int[10];    // allocate an array
delete[] arr;              // free the array
```

### Smart pointers (prefer these to raw `new` / `delete`)

```cpp
#include <memory>

auto up = make_unique<int>(10);   // single owner
auto sp = make_shared<int>(20);   // shared ownership (reference counted)
weak_ptr<int> wp = sp;            // non-owning reference to a shared_ptr
```

---

## Structures & Enums

```cpp
struct Point {
    int x, y;
};
Point p = {3, 4};
cout << p.x;

enum Color { RED, GREEN, BLUE };
Color c = GREEN;

enum class Status { Active, Inactive };  // scoped enum (safer)
Status st = Status::Active;
```

---

## Object-Oriented Programming

### Class & object

```cpp
class Car {
private:
    string brand;
    int year;

public:
    Car(string b, int y) : brand(b), year(y) {}  // constructor
    ~Car() {}                                     // destructor

    void show() const {
        cout << brand << " " << year << endl;
    }

    string getBrand() const { return brand; }     // getter
    void setYear(int y) { year = y; }             // setter
};

Car c("Toyota", 2022);
c.show();
```

### Access specifiers

| Specifier   | Accessible from                       |
|-------------|---------------------------------------|
| `public`    | Anywhere                              |
| `private`   | Only inside the class (the default)   |
| `protected` | The class and its derived classes     |

### Inheritance

```cpp
class Animal {
public:
    void eat() { cout << "Eating\n"; }
};

class Dog : public Animal {
public:
    void bark() { cout << "Woof\n"; }
};

Dog d;
d.eat();   // inherited from Animal
d.bark();
```

### Polymorphism (virtual functions)

```cpp
class Shape {
public:
    virtual double area() const = 0;  // pure virtual -> Shape is abstract
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() const override { return 3.14159 * r * r; }
};

Shape *s = new Circle(2);
cout << s->area();
delete s;
```

### Operator overloading

```cpp
class Vec {
public:
    int x, y;
    Vec(int x, int y) : x(x), y(y) {}
    Vec operator+(const Vec &o) const { return Vec(x + o.x, y + o.y); }
};
```

### Static members & friend functions

```cpp
class Counter {
public:
    static int count;            // shared by every object
    Counter() { count++; }
    friend void reveal(const Counter &c);  // may access private members
};
int Counter::count = 0;
```

---

## Templates

```cpp
template <typename T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}
maxOf<int>(3, 7);
maxOf(2.5, 1.5);   // the type is deduced

template <typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T get() const { return value; }
};
Box<string> b("hi");
```

---

## STL Containers

### vector (dynamic array)

```cpp
#include <vector>
vector<int> v = {1, 2, 3};
v.push_back(4);
v.pop_back();
v.size();
v.front(); v.back();
v.insert(v.begin() + 1, 10);
v.erase(v.begin());
v.clear();
```

### list, deque

```cpp
#include <list>
#include <deque>
list<int> l = {1, 2};  l.push_front(0);
deque<int> dq;         dq.push_back(1); dq.push_front(0);
```

### stack, queue, priority_queue

```cpp
#include <stack>
#include <queue>

stack<int> st;  st.push(1); st.top(); st.pop();
queue<int> q;   q.push(1);  q.front(); q.pop();

priority_queue<int> maxHeap;                            // largest on top
priority_queue<int, vector<int>, greater<int>> minHeap; // smallest on top
```

### set, map, and unordered versions

```cpp
#include <set>
#include <map>
#include <unordered_map>

set<int> s = {3, 1, 2};     // sorted, unique values
s.insert(5);
s.count(3);                 // 1 if present, 0 if not

map<string, int> m;         // sorted by key
m["apple"] = 3;
for (auto &[key, val] : m) cout << key << ": " << val << "\n";

unordered_map<string, int> um;  // hash table, average O(1) lookup
um["x"] = 1;
if (um.find("x") != um.end()) { /* found */ }
```

### pair & tuple

```cpp
pair<int, string> pr = {1, "one"};
cout << pr.first << pr.second;

tuple<int, char, double> t = {1, 'a', 2.5};
cout << get<0>(t);
```

---

## STL Algorithms

```cpp
#include <algorithm>
#include <numeric>

vector<int> v = {5, 2, 8, 1};

sort(v.begin(), v.end());                   // ascending
sort(v.begin(), v.end(), greater<int>());   // descending
reverse(v.begin(), v.end());
*max_element(v.begin(), v.end());
*min_element(v.begin(), v.end());
accumulate(v.begin(), v.end(), 0);          // sum
count(v.begin(), v.end(), 2);
find(v.begin(), v.end(), 8);                // returns an iterator
binary_search(v.begin(), v.end(), 5);       // the range must be sorted
lower_bound(v.begin(), v.end(), 5);
upper_bound(v.begin(), v.end(), 5);
```

---

## File Handling

```cpp
#include <fstream>

// Write to a file
ofstream out("data.txt");
out << "Hello File\n";
out.close();

// Read a file line by line
ifstream in("data.txt");
string line;
while (getline(in, line)) {
    cout << line << endl;
}
in.close();

// Append to a file
ofstream app("data.txt", ios::app);
app << "More text\n";
```

| Mode          | Meaning                        |
|---------------|--------------------------------|
| `ios::in`     | Open for reading               |
| `ios::out`    | Open for writing               |
| `ios::app`    | Add to the end of the file     |
| `ios::trunc`  | Clear the file's contents      |
| `ios::binary` | Binary mode                    |

---

## Exception Handling

```cpp
#include <stdexcept>

try {
    int d = 0;
    if (d == 0) throw runtime_error("Division by zero");
} catch (const runtime_error &e) {
    cout << "Error: " << e.what() << endl;
} catch (...) {
    cout << "Unknown error" << endl;
}
```

Common exceptions: `std::runtime_error`, `std::invalid_argument`, `std::out_of_range`, `std::bad_alloc`

---

## Modern C++ Features

```cpp
auto x = 3.14;                         // type deduction (C++11)
for (auto &e : container) {}           // range-based for (C++11)
int *p = nullptr;                      // nullptr (C++11)
auto [a, b] = make_pair(1, 2);         // structured bindings (C++17)

#include <optional>
optional<int> maybe = nullopt;         // a value that may be missing (C++17)
if (maybe) cout << *maybe;

string s1 = "big data";
string s2 = move(s1);                  // move instead of copy (C++11)

if (auto it = m.find("k"); it != m.end()) {}  // if with an initializer (C++17)
```

---



Happy coding!
