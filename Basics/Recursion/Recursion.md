# Recursion

A function is **recursive** when it calls itself. It solves a problem by solving a smaller version of the *same* problem, until the problem is small enough to answer directly.

---

## 1. The two parts every recursive function needs

| Part | What it does | If it's missing |
|---|---|---|
| **Base case** | Answers the smallest input directly, with no further call | Infinite recursion → stack overflow (crash) |
| **Recursive case** | Calls itself on a *smaller* input and uses that result | Nothing gets solved |

Each recursive call must move **towards** the base case (smaller `n`, next index, half the range…).

```cpp
int factorial(int n) {
    if (n <= 1) return 1;            // base case
    return n * factorial(n - 1);     // recursive case: n shrinks by 1
}
```

### Characteristics of a recursive algorithm

| Trait | Meaning |
|---|---|
| Problem decomposition | The problem splits into smaller sub-problems of the same shape |
| Base condition | Guarantees the calls eventually stop |
| Call-stack usage | Each call adds a stack frame, so deep recursion costs memory |

### How to think about it ("leap of faith")
1. Write down what the function **returns** for an input, in one sentence.
   *`factorial(n)` returns n!*
2. **Assume** it already works for smaller inputs.
   *`factorial(n-1)` gives (n-1)!*
3. Use that smaller answer to build the answer for `n`.
   *n! = n × (n-1)!*
4. Add the base case where step 3 stops making sense.

Don't try to trace every call in your head. Trust the smaller call.

### When to use recursion
- Hierarchical or tree-shaped data (trees, graphs, file systems, nested JSON)
- Problems that naturally shrink into smaller copies of themselves
- Backtracking (N-Queens, Sudoku, permutations, maze solving)
- Divide and conquer (merge sort, quick sort, binary search)

---

## 2. What happens in memory: the call stack

Every call gets its own **stack frame** holding its parameters, local variables and the place to return to. Frames pile up until a base case is hit, then they return one by one in reverse order.

```
factorial(4)
└─ 4 * factorial(3)
       └─ 3 * factorial(2)
              └─ 2 * factorial(1)
                     └─ returns 1          ← base case
              ← returns 2 * 1 = 2
       ← returns 3 * 2 = 6
← returns 4 * 6 = 24
```

- **Winding** (going down): calls are made, frames pile up.
- **Unwinding** (coming back): results are returned and combined.

**Stack overflow:** the stack is limited (1 MB by default on Windows, often 8 MB on Linux). A depth of roughly **10⁵ or more** levels can crash, especially in a debug (`-O0`) build. (Python is stricter: its default recursion limit is about 1000.)

> **Debugging tip (VS Code):** set a breakpoint inside the function, press F5 and open the **Call Stack** panel. You can see one entry per active call. Use F11 to step into a call and Shift+F11 to step out.

---

## 3. Types of recursion

### 3.1 Direct vs. indirect

**Direct:** the function calls itself.
```cpp
void countdown(int n) {
    if (n == 0) return;
    cout << n << " ";
    countdown(n - 1);
}
```

**Indirect (mutual):** A calls B, and B calls A.
```cpp
bool isOdd(int n);

bool isEven(int n) {
    if (n == 0) return true;
    return isOdd(n - 1);
}
bool isOdd(int n) {
    if (n == 0) return false;
    return isEven(n - 1);
}
```
Common in parsers (expression → term → factor → expression).

---

### 3.2 Linear recursion
Each call makes **at most one** recursive call. The calls form a straight chain of depth `n`.

```cpp
int sumArray(const vector<int>& a, int i) {
    if (i == (int)a.size()) return 0;
    return a[i] + sumArray(a, i + 1);
}
```
Time O(n), stack space O(n).

---

### 3.3 Tail recursion
The recursive call is the **very last thing** the function does. Nothing is left to compute after it returns.

```cpp
// Tail recursive: the result is carried forward in an accumulator
int factorialTail(int n, int acc = 1) {
    if (n <= 1) return acc;
    return factorialTail(n - 1, n * acc);   // nothing to do after this call
}
```

Compare with the normal factorial: `return n * factorial(n - 1);` is **not** tail recursive, because the multiplication happens *after* the call returns.

**Why it matters:** with optimization (`-O2`), the compiler can turn tail recursion into a loop (*tail-call optimization*). That reuses one stack frame, so space drops from O(n) to O(1). C++ doesn't **guarantee** this, and it doesn't happen at `-O0`. Scheme guarantees it and Scala offers `@tailrec`; **Python and Java never do it**.

Example from this folder: the sorted-array check is naturally tail recursive.
```cpp
bool isSorted(const vector<int>& a, int i = 0) {
    if (i + 1 >= (int)a.size()) return true;        // no pair left
    if (a[i + 1] < a[i]) return false;               // pair out of order
    return isSorted(a, i + 1);                       // tail call
}
```

---

### 3.4 Head recursion
The recursive call comes **first**, and the work happens after it returns (during unwinding).

```cpp
void printAscending(int n) {
    if (n == 0) return;
    printAscending(n - 1);   // call first
    cout << n << " ";        // work after → prints 1 2 3 ... n
}
```
Moving the `cout` before the call turns it into a tail call and prints `n ... 3 2 1`.
**Where you put the work (before or after the call) decides the order.**

---

### 3.5 Tree (multiple) recursion
Each call makes **two or more** recursive calls, so the calls branch like a tree.

```cpp
long long fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
```

```
                fib(4)
            /           \
        fib(3)          fib(2)
       /     \          /    \
   fib(2)  fib(1)   fib(1) fib(0)
   /    \
fib(1) fib(0)
```

- Time: **O(2ⁿ)** (exponential). `fib(2)` is computed twice, and repeats grow fast.
- Stack space: only **O(n)**, the depth of the tree, not its size.

Fix the repeated work with memoization (see 3.8).

**Tower of Hanoi** is another tree recursion: move `n` disks from `src` to `dst` using `aux`, never placing a larger disk on a smaller one.

```cpp
void hanoi(int n, char src, char dst, char aux) {
    if (n == 0) return;
    hanoi(n - 1, src, aux, dst);                 // move n-1 disks out of the way
    cout << "Move disk " << n << " from " << src << " to " << dst << "\n";
    hanoi(n - 1, aux, dst, src);                 // put them back on top
}
```
Moves: 2ⁿ − 1. Time: O(2ⁿ). Here the subproblems don't overlap, so memoization can't help: every move really has to be printed.

---

### 3.6 Nested recursion
The *argument* to the recursive call is itself a recursive call.

```cpp
int mcCarthy91(int n) {          // returns 91 for every n <= 100
    if (n > 100) return n - 10;
    return mcCarthy91(mcCarthy91(n + 11));
}
```
Rare in practice, but it shows up in theory and trick questions. Its behaviour is hard to predict without tracing.

---

### 3.7 Divide and conquer
**Split** the problem into independent parts, **solve** each part recursively, and **combine** the results.

```cpp
void mergeSort(vector<int>& a, int l, int r) {   // sorts a[l..r]
    if (l >= r) return;                           // 0 or 1 element: already sorted
    int m = l + (r - l) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    inplace_merge(a.begin() + l, a.begin() + m + 1, a.begin() + r + 1);
}
```

```cpp
// Fast exponentiation: a^n in O(log n)
long long power(long long a, long long n) {
    if (n == 0) return 1;
    long long half = power(a, n / 2);
    return (n % 2 == 0) ? half * half : half * half * a;
}
```

```cpp
// Binary search on a sorted array: O(log n) time, O(log n) stack
int binarySearch(const vector<int>& a, int target, int lo, int hi) {
    if (lo > hi) return -1;                       // empty range: not found
    int mid = lo + (hi - lo) / 2;
    if (a[mid] == target) return mid;
    if (a[mid] < target) return binarySearch(a, target, mid + 1, hi);
    return binarySearch(a, target, lo, mid - 1);
}
```
Other examples: quick sort, closest pair of points, segment trees.

---

### 3.8 Recursion with memoization (top-down DP)
A tree recursion whose subproblems **repeat** can store each answer the first time it's computed.

```cpp
vector<long long> memo(91, -1);

long long fibMemo(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];            // already solved
    return memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
}
```
Time drops from O(2ⁿ) to **O(n)**. Each state is computed once.

**Memoization works when:**
- the same arguments always give the same answer (no hidden state), and
- subproblems overlap (the same call shows up more than once).

---

### 3.9 Backtracking
Build a solution step by step. At each step **choose** an option, **recurse**, then **undo** the choice and try the next one.

```cpp
// Print all subsets of a
void subsets(const vector<int>& a, int i, vector<int>& cur) {
    if (i == (int)a.size()) {                     // made a choice for every element
        for (int x : cur) cout << x << " ";
        cout << "\n";
        return;
    }
    subsets(a, i + 1, cur);                       // choice 1: skip a[i]

    cur.push_back(a[i]);                          // choice 2: take a[i]
    subsets(a, i + 1, cur);
    cur.pop_back();                               // undo the choice
}
```
Used for permutations, subsets, N-Queens, Sudoku, combination sum and maze paths.
Add **pruning** (return early when a partial solution already can't work) to cut the search tree.

---

### 3.10 Recursion on structures (trees and graphs)
The data itself is recursive: a tree is a node plus smaller trees.

```cpp
// DFS on a graph
vector<vector<int>> adj;
vector<bool> vis;

void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u])
        if (!vis[v]) dfs(v);
}
```
```cpp
// Height of a binary tree
int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}
```
```cpp
// Binary tree traversals: the only difference is where the "visit" goes
void preorder(Node* node) {      // root, left, right
    if (!node) return;
    cout << node->val << " ";
    preorder(node->left);
    preorder(node->right);
}
void inorder(Node* node) {       // left, root, right (sorted order for a BST)
    if (!node) return;
    inorder(node->left);
    cout << node->val << " ";
    inorder(node->right);
}
void postorder(Node* node) {     // left, right, root
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->val << " ";
}
```
Traversals: time O(n), stack space O(h), where h is the tree height (O(log n) if balanced, O(n) if it's a chain).

---

## 4. Types at a glance

| Type | Calls per invocation | Typical time | Stack depth | Example |
|---|---|---|---|---|
| Linear | 1 | O(n) | O(n) | sum of array, factorial |
| Tail | 1 (last statement) | O(n) | O(n), or O(1) with TCO | sorted check, gcd |
| Head | 1 (first statement) | O(n) | O(n) | print 1..n |
| Tree | 2+ | often O(2ⁿ) | O(n) | naive Fibonacci, Tower of Hanoi |
| Nested | call inside argument | varies | varies | McCarthy 91 |
| Indirect | A → B → A | varies | varies | isEven/isOdd, parsers |
| Divide & conquer | 2+ on halves | O(n log n), O(log n) | O(log n) | merge sort, power, binary search |
| Memoized | 2+, cached | O(states × work) | O(depth) | DP problems |
| Backtracking | many, with undo | exponential (pruned) | O(depth) | subsets, N-Queens |

---

## 5. Analysing time complexity

Write a **recurrence**: the cost for `n` in terms of the cost for smaller inputs.

| Recurrence | Example | Result |
|---|---|---|
| T(n) = T(n−1) + O(1) | factorial, linear scan | O(n) |
| T(n) = T(n/2) + O(1) | binary search, fast power | O(log n) |
| T(n) = 2T(n/2) + O(n) | merge sort | O(n log n) |
| T(n) = 2T(n−1) + O(1) | tower of Hanoi | O(2ⁿ) |
| T(n) = T(n−1) + T(n−2) + O(1) | naive Fibonacci | O(φⁿ) ≈ O(1.618ⁿ) |

Quick rule: **time ≈ (number of calls) × (work per call)**. Draw the recursion tree and count the nodes.
**Space** = maximum depth × memory per frame (plus any extra arrays).

---

## 6. Recursion vs. loop

| | Loop | Recursion |
|---|---|---|
| Code style | often longer, more explicit | short, mirrors the definition |
| Speed (same algorithm) | same or a bit faster | function-call overhead |
| Extra memory | O(1) | O(depth) stack |
| Risk | none | stack overflow on deep inputs |
| Debugging | easy to step through | harder to trace (use the Call Stack panel) |
| Best for | straight-line work (arrays, counters) | trees, backtracking, divide and conquer |

- Recursion is **not faster by itself**. When a recursive solution is faster, it's because of a better *algorithm* (divide and conquer, memoization), and that algorithm can also be written with loops.
- For DFS and backtracking, recursion is often **simpler and as fast or faster** than a loop with a hand-made `std::stack`.
- Any tail recursion can be turned into a loop directly:

```text
// tail recursive                       // equivalent loop
bool isSorted(a, i):                     for (int i = 0; i + 1 < n; i++)
    if (i + 1 >= n) return true;             if (a[i+1] < a[i]) return false;
    if (a[i+1] < a[i]) return false;     return true;
    return isSorted(a, i + 1);
```

### Advantages and disadvantages

| Advantages | Disadvantages |
|---|---|
| Short, readable code | Extra memory for each stack frame |
| Maps naturally to recursive structures (trees, graphs) | Risk of stack overflow on deep inputs |
| Makes divide-and-conquer and backtracking easy to express | Can be very slow when sub-problems overlap (naive Fibonacci) |
| | Harder to trace and debug |

### Optimizing recursion
1. **Memoize** when subproblems overlap (3.8): exponential → polynomial.
2. **Make it tail recursive** with an accumulator (3.3), so the compiler *may* reuse the frame.
3. **Convert to a loop** (or an explicit `std::stack`) when the depth can be large:
```cpp
long long factorialIter(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}
```

---

## 7. Common mistakes

1. **Missing or wrong base case:** infinite recursion and a crash. Check the smallest inputs (`n = 0`, `n = 1`, empty array).
2. **Not shrinking the input:** e.g. calling `f(n)` from `f(n)`, or `f(n + 1)` when the base case is at 0.
3. **Forgetting `return`:** writing `f(n - 1);` instead of `return f(n - 1);` throws away the result. If the function then reaches its end without returning, that's undefined behaviour.
4. **Passing big objects by value:** `void f(vector<int> a)` copies the vector on **every** call. Use `const vector<int>&` (or `vector<int>&` if you modify it).
5. **Forgetting to undo in backtracking:** a `push_back` without its matching `pop_back` corrupts the later branches.
6. **Exponential repeats:** tree recursion on overlapping subproblems needs memoization.
7. **Too deep:** ~10⁵+ levels can overflow the stack. Convert to a loop, or use an iterative version for large `n`.
8. **Overflow in results:** factorial and Fibonacci outgrow `int` quickly (13! > 2³¹). Use `long long` or a modulus.

---

## 8. Checklist before writing a recursive function

- [ ] What does `f(args)` **return/do**, in one sentence?
- [ ] What's the **smallest** input, and what's its answer? (base case)
- [ ] How does the answer for `n` use the answers for **smaller** inputs?
- [ ] Does every call get **closer** to the base case?
- [ ] Are large parameters passed **by reference**?
- [ ] Do subproblems **repeat**? → memoize.
- [ ] How **deep** can it go? Is that safe for the input limits?

---

## 9. Real-world applications

- **Operating systems:** walking directory trees
- **Compilers:** parsing expressions and syntax trees
- **AI and games:** minimax, game-tree search, backtracking solvers
- **Graphics:** fractals, flood fill, spatial trees (quadtrees, BVH)
- **Mathematics:** combinatorics, divide-and-conquer algorithms, recurrences

---

## 10. Practice problems (easy → hard)

1. Print 1..n and n..1 (head vs. tail)
2. Factorial, sum of digits, power `a^n`
3. Check if an array is sorted
4. Reverse a string / check palindrome
5. Fibonacci (naive → memoized)
6. Binary search (recursive)
7. Tree traversals (pre/in/post-order), tree height
8. Tower of Hanoi
9. Generate all subsets / all permutations
10. Merge sort, quick sort
11. N-Queens, Sudoku solver, rat in a maze
