# How Stack Frames Work

## Sample code

```cpp
#include <bits/stdc++.h>
using namespace std;

bool checkPositive(int a, int b){
    return (a>=0 && b >=0);
}

int add(int x, int y){
    bool chck = checkPositive(x, y);
    if(chck) return x+y;
    return -1;
}

int main() {
    int a = 5, b = 6;
    int c = add(a, b);
    cout << c << endl;
    return 0;
}
```

## What a stack frame is

Each time a function is **called**, the program sets aside a block of memory for it on the **call stack**. That block is the function's **stack frame**. It typically holds:

| Part | Purpose |
|---|---|
| **Parameters** | Copies of the arguments passed in (`x`, `y`) |
| **Return address** | The instruction in the caller to go back to when this function finishes |
| **Saved base pointer** | A link to the caller's frame, so the caller's frame can be restored |
| **Local variables** | Variables declared inside the function (`chck`) |

When the function **returns**, its frame is **popped** (thrown away) and control goes back to the return address. Frames follow LIFO order: the last function called is the first one to finish.

## Step-by-step trace

### Step 1: The program starts and `main()` gets a frame

```
|-----------------------|
| main()                |
|   a = 5               |
|   b = 6               |
|   c = ??? (not set)   |
|-----------------------|   <- bottom of stack
```

### Step 2: `main` calls `add(a, b)`

A new frame is pushed. The values of `a` and `b` are **copied** into `x` and `y` (pass by value). The return address records "come back to the line `int c = ...` in main and store the result in `c`".

```
|-----------------------|
| add(x, y)             |   <- top (currently running)
|   x = 5               |
|   y = 6               |
|   chck = ???          |
|   return addr -> main |
|-----------------------|
| main()                |
|   a = 5, b = 6        |
|   c = ???             |
|-----------------------|
```

### Step 3: `add` calls `checkPositive(x, y)`

`add` pauses partway through its first line, and another frame is pushed on top:

```
|-------------------------------|
| checkPositive(a, b)           |   <- top (currently running)
|   a = 5                       |   (a different 'a' from main's!)
|   b = 6                       |
|   return addr -> add          |
|-------------------------------|
| add(x, y)                     |   (paused, waiting)
|   x = 5, y = 6                |
|   chck = ???                  |
|-------------------------------|
| main()                        |   (paused, waiting)
|   a = 5, b = 6, c = ???       |
|-------------------------------|
```

**Key point:** the `a` and `b` inside `checkPositive` are separate variables from the `a` and `b` in `main`. They have the same names, but they live in different frames. This is exactly why each recursive call gets its own copy of its variables.

### Step 4: `checkPositive` returns `true`, and its frame is popped

The return value (`true`) is passed back, usually in a CPU register. Execution jumps to the saved return address inside `add`.

```
|-----------------------|
| add(x, y)             |   <- top again
|   x = 5, y = 6        |
|   chck = true         |   <- filled in now
|-----------------------|
| main()                |
|   a = 5, b = 6, c=??? |
|-----------------------|
```

### Step 5: `add` returns `11`, and its frame is popped

```
|-----------------------|
| main()                |   <- top again
|   a = 5, b = 6        |
|   c = 11              |   <- filled in now
|-----------------------|
```

### Step 6: `main` finishes

`main` prints `11`, returns `0`, and its frame is popped. The stack is empty and the program ends.

## Stack depth over time

```
time ──────────────────────────────────────────────►

                  [checkPositive]
         [ add  ][     add      ][ add ]
[ main  ][ main ][     main     ][ main][ main ]
  start   call     call            ret    ret → end
          add      checkPositive
```

## How this connects to recursion

Recursion works the same way. The only difference is that the function calls **itself**, so you get many frames of the **same function** stacked up, and each frame has its own copies of the parameters and locals:

```cpp
int fact(int n) {
    if (n == 0) return 1;
    return n * fact(n - 1);
}
```

`fact(3)` builds up this stack:

```
| fact(n=0) |  -> returns 1             (base case: stack stops growing)
| fact(n=1) |  -> waiting for fact(0), then 1*1 = 1
| fact(n=2) |  -> waiting for fact(1), then 2*1 = 2
| fact(n=3) |  -> waiting for fact(2), then 3*2 = 6
| main      |
```

- **Going down** (the calls) pushes frames.
- **Coming back up** (the returns) pops frames and finishes the "pending" work, like `n * ...`.
- **Without a base case**, frames keep getting pushed until the stack runs out of memory. That crash is a **stack overflow**.

## A detail about real hardware

On x86-64, the first few arguments are usually passed in **CPU registers** instead of being pushed onto the stack. Also, the stack physically grows **toward lower memory addresses**. Neither of these changes the mental model above. If you compile without optimisation (`-O0`) and step through in the VS Code debugger, the **Call Stack** panel shows these frames, and clicking each one shows that frame's own variables.
