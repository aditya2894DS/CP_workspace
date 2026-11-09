## Arrays

An **array** is a collection of elements of the **same data type** stored in **contiguous (adjacent) memory locations**. Each element is identified by an **index** (0-based in C/C++/Java/Python).

To store the elements of an array, a single memory block is allocated. **Accessing any particular element in the  array is achieved in constant time by using the index of the element as the subscript.**

Q. Why constant time in accessing array elements?
Ans. Because all elements are the same size and sit next to each other in memory, the address of any element can be computed directly with a formula — no traversal is needed:

```
address(arr[i]) = base_address + i * sizeof(element)
```

Example: `int arr[5]` starting at address `1000`, with `sizeof(int) = 4`:

| Index   | 0    | 1    | 2    | 3    | 4    |
|---------|------|------|------|------|------|
| Address | 1000 | 1004 | 1008 | 1012 | 1016 |

`arr[3]` → `1000 + 3 * 4 = 1012`. This is one multiplication and one addition, regardless of whether `i` is 3 or 3,000,000 — hence **O(1)**. This is called **random access**.

---

### Declaration (C++)

```cpp
int arr[5];                     // static array, size fixed at compile time (garbage values if local)
int arr2[5] = {1, 2, 3, 4, 5};  // initialized
int arr3[5] = {0};              // all elements 0
int* arr4 = new int[n];         // dynamic array on heap (size decided at runtime)
delete[] arr4;                  // must free manually

#include <vector>
std::vector<int> v(n, 0);       // dynamic (resizable) array — preferred in CP
```

---

### Types of Arrays

1. **One-dimensional** – `int a[n];`
2. **Multi-dimensional** – `int grid[r][c];` (stored in **row-major** order in C/C++)
   - `address(a[i][j]) = base + (i * c + j) * sizeof(element)`
3. **Static array** – size fixed at compile time (stack memory).
4. **Dynamic array** – size decided at runtime / can grow (`new[]`, `std::vector`).

---

### Time Complexity of Operations

| Operation                          | Time Complexity | Reason |
|------------------------------------|-----------------|--------|
| Access by index `arr[i]`           | **O(1)**        | Direct address calculation |
| Update by index `arr[i] = x`       | **O(1)**        | Same as access |
| Search (unsorted, linear search)   | **O(n)**        | May need to check every element |
| Search (sorted, binary search)     | **O(log n)**    | Halve the search space each step |
| Insert at end (space available)    | **O(1)**        | Just write at next free index |
| Insert at beginning / middle       | **O(n)**        | Shift elements right to make room |
| Delete at end                      | **O(1)**        | Just reduce size |
| Delete at beginning / middle       | **O(n)**        | Shift elements left to fill gap |
| Traversal                          | **O(n)**        | Visit each element once |

**Dynamic array (`std::vector`) `push_back`:** **O(1) amortized**. When capacity is full, a bigger block (usually 2x) is allocated and all elements are copied — that single push is O(n), but averaged over many pushes it is O(1).

### Space Complexity

- Storing `n` elements: **O(n)**
- No extra memory per element (unlike linked lists, which store pointers).

---

### Advantages

1. **O(1) random access** – any element can be read/written directly by index.
2. **Cache friendly** – contiguous memory means elements are loaded into the CPU cache together (spatial locality), so traversal is very fast in practice.
3. **No memory overhead** – only the data is stored; no pointers per element.
4. **Simple to use** – easy to declare, index, and iterate.
5. **Enables efficient algorithms** – binary search, sorting, two pointers, sliding window, prefix sums, etc. all rely on index-based access.
6. **Basis for other structures** – stacks, queues, heaps, hash tables, matrices are commonly built on arrays.

### Disadvantages

1. **Fixed size (static arrays)** – size must be known in advance; cannot grow or shrink.
2. **Memory wastage** – if you allocate more than you use, the extra space is wasted.
3. **Costly insertion/deletion** – inserting or deleting in the beginning/middle needs shifting elements: O(n).
4. **Needs contiguous memory** – a large array may fail to allocate even if enough total free memory exists (fragmentation).
5. **Homogeneous** – all elements must be the same type.
6. **Resizing dynamic arrays is costly** – reallocation copies all elements (O(n)), and invalidates pointers/iterators to old elements.
7. **No bounds checking in C/C++** – `arr[10]` on a size-5 array is undefined behaviour (no error thrown).

---

### Arrays vs Linked Lists (quick comparison)

| Feature                  | Array            | Linked List         |
|--------------------------|------------------|---------------------|
| Memory                   | Contiguous       | Scattered (nodes)   |
| Access by index          | O(1)             | O(n)                |
| Insert/Delete at front   | O(n)             | O(1)                |
| Insert/Delete in middle  | O(n) (shifting)  | O(1) if node known, O(n) to find it |
| Extra memory             | None             | Pointer(s) per node |
| Cache performance        | Excellent        | Poor                |
| Size                     | Fixed (static)   | Dynamic             |

---

### When to Use Arrays

- You need **fast access by index**.
- The number of elements is **known or bounded**.
- Mostly **reading/traversing**, few insertions/deletions in the middle.
- Performance-critical code where **cache locality** matters.

### Common CP Tips

- Global arrays in C++ are auto-initialized to `0`; local arrays contain garbage values.
- Large arrays (e.g. `int a[1e6]`) should be declared **globally** to avoid stack overflow.
- Prefer `std::vector` for runtime sizes; use `v.reserve(n)` to avoid repeated reallocation.
- Passing an array to a function passes a **pointer** (O(1)) — `sizeof(arr)` inside the function gives pointer size, not array size.
- Watch for **off-by-one** errors: valid indices are `0` to `n-1`.
