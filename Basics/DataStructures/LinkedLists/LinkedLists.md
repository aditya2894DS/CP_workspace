## Linked List

A **linked list** is a linear data structure made of **nodes**, where each node stores:
- **data** – the value
- **one or more pointers (links)** – the address of the next (and/or previous) node

Unlike arrays, the nodes are **NOT stored in contiguous memory**. The order of the list comes from the **pointers**, not from where the nodes sit in memory.

```
 head
  │
  ▼
┌────┬───┐    ┌────┬───┐    ┌────┬───┐
│ 10 │ ●─┼───►│ 20 │ ●─┼───►│ 30 │ ╳ │   (╳ = nullptr)
└────┴───┘    └────┴───┘    └────┴───┘
 addr 5000     addr 1200     addr 8840   ← addresses are scattered
```

---

### Key Terminology

- **Node** – one element of the list (data + link(s)).
- **Head** – pointer to the **first** node. If `head == nullptr`, the list is **empty**.
- **Tail** – the **last** node (its `next` is `nullptr` in a non-circular list).
- **Next pointer** – address of the following node.
- **Prev pointer** – address of the preceding node (only in doubly linked lists).
- **Traversal** – visiting nodes one by one by following the links from the head.
- **Sentinel / Dummy node** – a fake node with no real data, used to remove edge cases (empty list, inserting at head).

---

### Memory: Who Decides the Addresses?

- Each node is allocated **separately** on the heap using `new` (C++) / `malloc` (C).
- The **memory allocator** chooses each node's address — **you don't**. Nodes can be anywhere in the heap.
- What **you** control is the **link**: you store the address of the next node inside the current node.
- Consequences:
  - ✅ No need for one big contiguous block → list can grow/shrink one node at a time.
  - ❌ No address formula like `base + i * size` → **no random access**, reaching the i-th node needs **O(i)** traversal.
  - ❌ Extra memory per node for pointer(s) (8 bytes per pointer on 64-bit systems).
  - ❌ Poor **cache locality** – nodes are scattered, so CPU caches help less than with arrays.

```cpp
Node* a = new Node{10, nullptr};  // allocator picks a's address
Node* b = new Node{20, nullptr};  // allocator picks b's address
a->next = b;                      // YOU store b's address inside a
```

---

### Array vs Linked List

| Feature                        | Array                         | Linked List                         |
|--------------------------------|-------------------------------|-------------------------------------|
| Memory layout                  | Contiguous                    | Scattered (linked by pointers)      |
| Size                           | Fixed (static) / amortized resize (vector) | Grows/shrinks node by node |
| Access i-th element            | **O(1)** (random access)      | **O(n)** (sequential access)        |
| Insert/Delete at beginning     | O(n) (shifting)               | **O(1)**                            |
| Insert/Delete at given node    | O(n) (shifting)               | **O(1)** (if you have the pointer)  |
| Insert at end                  | O(1) amortized                | O(1) with tail pointer, else O(n)   |
| Search                         | O(n) / O(log n) if sorted     | O(n) (binary search is not useful)  |
| Extra memory                   | None                          | 1–2 pointers per node               |
| Cache friendliness             | Excellent                     | Poor                                |
| Memory waste                   | Unused capacity possible      | Pointer overhead                    |

**Use a linked list when:** frequent insertions/deletions in the middle/front, size unknown, and you rarely need index-based access.
**Use an array when:** you need fast random access, cache performance, or binary search.

---

## Types of Linked Lists

### 1. Singly Linked List (SLL)

- Each node has **data + one pointer (`next`)**.
- Traversal is **one-directional** (head → tail).
- Last node's `next` is `nullptr`.

```
head → [10|●] → [20|●] → [30|●] → nullptr
```

```cpp
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};
```

**Pros**
- Simplest; least memory per node (1 pointer).

**Cons**
- Cannot go backwards.
- Deleting a node requires the pointer to its **previous** node → O(n) to find it if you only have the node itself.

#### Basic Operations (SLL)

```cpp
// Traverse / print — O(n)
void print(Node* head) {
    for (Node* cur = head; cur != nullptr; cur = cur->next)
        cout << cur->data << " ";
    cout << "\n";
}

// Insert at head — O(1)
Node* insertHead(Node* head, int val) {
    Node* node = new Node(val);
    node->next = head;
    return node;               // new head
}

// Insert at tail — O(n) without tail pointer
Node* insertTail(Node* head, int val) {
    Node* node = new Node(val);
    if (!head) return node;
    Node* cur = head;
    while (cur->next) cur = cur->next;
    cur->next = node;
    return head;
}

// Insert after a given node — O(1)
void insertAfter(Node* prev, int val) {
    if (!prev) return;
    Node* node = new Node(val);
    node->next = prev->next;
    prev->next = node;
}

// Delete first node with value `key` — O(n)
Node* deleteKey(Node* head, int key) {
    if (!head) return nullptr;
    if (head->data == key) {
        Node* tmp = head->next;
        delete head;
        return tmp;
    }
    Node* cur = head;
    while (cur->next && cur->next->data != key) cur = cur->next;
    if (cur->next) {
        Node* del = cur->next;
        cur->next = del->next;
        delete del;
    }
    return head;
}

// Search — O(n)
bool search(Node* head, int key) {
    for (Node* cur = head; cur; cur = cur->next)
        if (cur->data == key) return true;
    return false;
}

// Free the whole list — O(n)
void freeList(Node* head) {
    while (head) {
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
}
```

---

### 2. Doubly Linked List (DLL)

- Each node has **data + `prev` pointer + `next` pointer**.
- Traversal in **both directions**.
- `head->prev == nullptr` and `tail->next == nullptr`.

```
nullptr ← [●|10|●] ⇄ [●|20|●] ⇄ [●|30|●] → nullptr
           head                   tail
```

```cpp
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};
```

**Pros**
- Traverse forwards **and** backwards.
- Delete a node in **O(1)** when you have a pointer to it (no need to search for previous).
- Insert before a node in O(1).

**Cons**
- Extra pointer per node → more memory.
- More pointers to update on every insert/delete → more chances for bugs.

```cpp
// Insert at head — O(1)
DNode* insertHead(DNode* head, int val) {
    DNode* node = new DNode(val);
    node->next = head;
    if (head) head->prev = node;
    return node;
}

// Delete a given node — O(1)
DNode* deleteNode(DNode* head, DNode* del) {
    if (!head || !del) return head;
    if (head == del) head = del->next;
    if (del->next) del->next->prev = del->prev;
    if (del->prev) del->prev->next = del->next;
    delete del;
    return head;
}
```

**Real-world uses**
- Browser back/forward history.
- Undo/redo stacks.
- **LRU Cache** (DLL + hash map → O(1) get/put).
- `std::list` in C++ is a doubly linked list.

---

### 3. Circular Singly Linked List

- Like an SLL, but the **last node points back to the first** node (no `nullptr` at the end).
- You can start from **any** node and visit the whole list.
- Often we keep a pointer to the **last** node, because then `last->next` is the head → both head and tail in O(1).

```
   ┌──────────────────────────────┐
   ▼                              │
 [10|●] → [20|●] → [30|●] → [40|●]┘
                             last
```

**Traversal — careful, there is no `nullptr`!** Use a `do-while`, stop when you return to the start:

```cpp
void printCircular(Node* head) {
    if (!head) return;
    Node* cur = head;
    do {
        cout << cur->data << " ";
        cur = cur->next;
    } while (cur != head);
}

// Insert at beginning when we keep a `last` pointer — O(1)
Node* insertFront(Node* last, int val) {
    Node* node = new Node(val);
    if (!last) { node->next = node; return node; } // single node points to itself
    node->next = last->next;
    last->next = node;
    return last;
}

// Insert at end — O(1): same as front, but the new node becomes `last`
Node* insertEnd(Node* last, int val) {
    Node* node = new Node(val);
    if (!last) { node->next = node; return node; }
    node->next = last->next;
    last->next = node;
    return node;   // new last
}
```

**Pros**
- Head and tail both reachable in O(1) via `last`.
- Natural for **round-robin** / repeating cycles.

**Cons**
- Easy to create **infinite loops** if the stop condition is wrong.
- Slightly trickier insert/delete edge cases (single node points to itself).

**Uses**
- **Round-robin CPU scheduling**.
- Multiplayer turn-taking in games.
- **Josephus problem**.
- Circular buffers / playlists on repeat.

---

### 4. Circular Doubly Linked List

- DLL where `tail->next = head` **and** `head->prev = tail`.
- Can go around in **both** directions forever.
- Getting the tail from the head is O(1): `head->prev`.

```
   ┌────────────────────────────────────┐
   ▼                                    │
 [●|10|●] ⇄ [●|20|●] ⇄ [●|30|●] ⇄ [●|40|●]
   │                                    ▲
   └────────────────────────────────────┘
```

**Uses**
- Implementation of advanced structures like **Fibonacci heaps**.
- Music players (next/previous with wrap-around).
- `std::list` is commonly implemented as a circular DLL with a **sentinel** node internally.

---

### 5. Header (Sentinel / Dummy) Linked List

- A special **header node** sits at the front; it holds no real data (sometimes stores the list's length).
- The list is **never truly empty** (the header always exists) → insert/delete code has **no special case for the head**.
- **Grounded header list** – last node points to `nullptr`.
- **Circular header list** – last node points back to the header.

```cpp
// Classic trick in CP: dummy node simplifies building/merging lists
Node dummy(0);
Node* tail = &dummy;
// ... tail->next = new Node(x); tail = tail->next;
return dummy.next;   // real head
```

---

### 6. XOR Linked List (Memory-Efficient DLL)

- A doubly linked list that stores **only one pointer field** per node: `npx = prev XOR next`.
- To move forward: `next = prev XOR cur->npx`. You must remember where you came from.
- Saves memory (one pointer instead of two) but:
  - ❌ Not possible in languages with garbage collection (Java, Python).
  - ❌ Hard to debug; can't jump in from an arbitrary node without knowing its neighbour.
  - Mostly of **theoretical / interview** interest.

```cpp
struct XNode {
    int data;
    XNode* npx;   // XOR of prev and next addresses
};
XNode* XOR(XNode* a, XNode* b) {
    return (XNode*)((uintptr_t)a ^ (uintptr_t)b);
}
```

---

### 7. Skip List

- A **probabilistic** data structure built from **multiple layers of sorted linked lists**.
- **Level 0** contains **all** elements in sorted order; each higher level is an "express lane" containing a **subset** of the level below.
- When inserting, a node is promoted to the next level with probability **p** (usually **1/2**) — like flipping a coin.
- Search starts at the **top-left**, moves **right** while the next value is ≤ target, otherwise moves **down** one level.

```
Level 3:  H ──────────────────────────────► 50 ─────────────────► nullptr
Level 2:  H ──────────► 20 ───────────────► 50 ─────────────────► nullptr
Level 1:  H ──► 10 ───► 20 ──────► 35 ────► 50 ──────► 70 ──────► nullptr
Level 0:  H ──► 10 ─► 15 ─► 20 ─► 30 ─► 35 ─► 40 ─► 50 ─► 60 ─► 70 ─► nullptr
```

Search for 40: L3: H→50 too big, go down → L2: H→20 ok, 20→50 too big, down → L1: 20→35 ok, 35→50 too big, down → L0: 35→40 ✅

| Operation | Average      | Worst case |
|-----------|--------------|------------|
| Search    | **O(log n)** | O(n)       |
| Insert    | **O(log n)** | O(n)       |
| Delete    | **O(log n)** | O(n)       |
| Space     | **O(n)** expected (≈ 2n nodes for p = 1/2) | O(n log n) |

```cpp
const int MAX_LEVEL = 16;
struct SkipNode {
    int key;
    vector<SkipNode*> forward;   // forward[i] = next node at level i
    SkipNode(int k, int lvl) : key(k), forward(lvl + 1, nullptr) {}
};

int randomLevel() {
    int lvl = 0;
    while ((rand() & 1) && lvl < MAX_LEVEL) lvl++;   // coin flips
    return lvl;
}

bool searchSkip(SkipNode* header, int level, int target) {
    SkipNode* cur = header;
    for (int i = level; i >= 0; i--)
        while (cur->forward[i] && cur->forward[i]->key < target)
            cur = cur->forward[i];
    cur = cur->forward[0];
    return cur && cur->key == target;
}
```

**Pros**
- O(log n) expected search/insert/delete **like a balanced BST**, but much **simpler to implement** (no rotations).
- Easy to make **concurrent / lock-free**.
- Supports ordered iteration and range queries naturally.

**Cons**
- Performance is probabilistic (bad luck → worse, but extremely unlikely).
- Extra memory for multiple forward pointers.

**Real-world uses**
- **Redis** sorted sets (`ZSET`).
- **LevelDB / RocksDB** MemTable.
- Java's `ConcurrentSkipListMap`.

---

### 8. Unrolled Linked List

- Each node stores a **small array of elements** (e.g., up to 64) instead of a single element.
- Combines arrays and linked lists:
  - Better **cache locality** than a normal linked list.
  - Fewer pointers → less memory overhead.
- When a node gets full, it **splits** into two; when it gets too empty, it **merges** with a neighbour.
- Access to the i-th element: O(n / k) where k = node capacity.
- Related idea in CP: **sqrt decomposition** on lists (blocks of size √n).

```cpp
const int CAP = 64;
struct UNode {
    int count;
    int elems[CAP];
    UNode* next;
};
```

---

### 9. Multilevel / Multilinked List

- A node can have a **`child`** pointer to another linked list (in addition to `next`).
- Forms a hierarchical structure; common problem: **flatten a multilevel list**.
- **Multi-linked list** – a node is part of several lists at once (e.g., sorted by name AND by age via two different `next` pointers).
- **Sparse matrix** representation: each non-zero element is a node linked in both its row list and column list.

```cpp
struct MNode {
    int data;
    MNode* next;
    MNode* child;
};
```

---

### 10. Self-Organizing List

- A list that **reorders itself** based on access patterns so frequently used items move near the head.
- Strategies:
  - **Move-to-Front (MTF)** – accessed node is moved to the head.
  - **Transpose** – accessed node swaps with its predecessor.
  - **Count** – each node keeps an access count; list stays sorted by count.
- Improves average search time when some keys are accessed much more than others.
- Uses: caches, symbol tables in compilers.

---

### Summary of Types

| Type                    | Pointers per node | Direction        | End points to  | Key benefit                          |
|-------------------------|-------------------|------------------|----------------|--------------------------------------|
| Singly                  | 1 (`next`)        | Forward          | `nullptr`      | Simple, low memory                   |
| Doubly                  | 2 (`prev`,`next`) | Both             | `nullptr`      | O(1) delete given node, back-traversal |
| Circular Singly         | 1                 | Forward (loops)  | Head           | Round-robin, O(1) head & tail        |
| Circular Doubly         | 2                 | Both (loops)     | Head / Tail    | Wrap-around both ways                |
| Header / Sentinel       | 1 or 2            | Depends          | `nullptr`/header | No empty-list edge cases           |
| XOR                     | 1 (XOR'd)         | Both             | `nullptr`      | DLL with half the pointer memory     |
| Skip List               | Many (levels)     | Forward          | `nullptr`      | O(log n) expected search             |
| Unrolled                | 1 + array         | Forward          | `nullptr`      | Cache-friendly                       |
| Multilevel              | 2+ (`next`,`child`) | Forward + down | `nullptr`      | Hierarchical data                    |
| Self-organizing         | 1 or 2            | Depends          | `nullptr`      | Faster access to frequent items      |

---

### Time Complexity of Operations (Singly / Doubly)

| Operation                              | Singly LL           | Doubly LL           |
|----------------------------------------|---------------------|---------------------|
| Access i-th element                    | O(n)                | O(n) (O(n/2) from nearer end if size & tail known) |
| Search                                 | O(n)                | O(n)                |
| Insert at head                         | **O(1)**            | **O(1)**            |
| Insert at tail (with tail pointer)     | **O(1)**            | **O(1)**            |
| Insert at tail (no tail pointer)       | O(n)                | O(n)                |
| Insert after given node                | **O(1)**            | **O(1)**            |
| Insert before given node               | O(n)                | **O(1)**            |
| Delete head                            | **O(1)**            | **O(1)**            |
| Delete tail                            | O(n) (need prev)    | **O(1)** (with tail) |
| Delete given node                      | O(n) (need prev)*   | **O(1)**            |
| Space                                  | O(n)                | O(n)                |

\* Trick: in an SLL you can "delete" a given non-tail node in O(1) by **copying the next node's data into it and deleting the next node**.

---

### C++ STL Linked Lists

| Container                | Type              | Notes                                                     |
|--------------------------|-------------------|-----------------------------------------------------------|
| `std::list<T>`           | Doubly linked     | `push_front/back`, `pop_front/back`, `insert`, `erase`, `splice`, `sort`, `reverse` |
| `std::forward_list<T>`   | Singly linked     | Lower memory; `push_front`, `insert_after`, `erase_after`; **no `size()`** |

```cpp
#include <list>
list<int> l = {1, 2, 3};
l.push_front(0);           // 0 1 2 3
l.push_back(4);            // 0 1 2 3 4
auto it = next(l.begin(), 2);
l.insert(it, 99);          // 0 1 99 2 3 4   (O(1) once you have the iterator)
l.erase(it);               // removes 2      (O(1))
l.reverse();
l.sort();                  // use member sort; std::sort needs random-access iterators
```

- Iterators of `std::list` stay **valid** after insertions/erasures of **other** elements (unlike `vector`).
- `splice` moves nodes between lists in **O(1)** (no copying).

---

### Important Techniques / Patterns

- **Dummy (sentinel) node** – avoids special-casing the head when building, merging, or deleting.
- **Two pointers (slow & fast / Floyd's tortoise and hare)**
  - Find the **middle**: slow moves 1, fast moves 2; when fast reaches the end, slow is at the middle.
  - **Detect a cycle**: if slow and fast ever meet → cycle exists.
  - **Find cycle start**: after they meet, reset one pointer to head; move both 1 step at a time; where they meet is the start.
- **Gap pointers** – find the **k-th node from the end**: move `fast` k steps ahead, then move both until `fast` reaches the end.
- **In-place reversal** – keep `prev`, `cur`, `next`:

```cpp
Node* reverse(Node* head) {
    Node* prev = nullptr;
    Node* cur = head;
    while (cur) {
        Node* nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;   // new head
}

Node* middle(Node* head) {
    Node* slow = head; Node* fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    return slow;
}

bool hasCycle(Node* head) {
    Node* slow = head; Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next; fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

- **Recursion** – many list problems have neat recursive solutions (reverse, merge, print in reverse), but recursion depth = n → may overflow the stack for very long lists.
- **Hashing** – store visited node addresses in an `unordered_set` (cycle detection, intersection) — O(n) extra space.

---

### Classic Problems (Practice List)

- Reverse a linked list (iterative & recursive)
- Reverse in groups of k
- Find the middle node
- Detect cycle / find start of cycle / length of cycle
- Remove n-th node from end
- Merge two sorted lists
- Merge k sorted lists (min-heap)
- Sort a linked list (**merge sort** is the best fit — O(n log n), no random access needed)
- Check if a list is a palindrome (find middle → reverse second half → compare)
- Intersection point of two lists
- Remove duplicates (sorted / unsorted)
- Add two numbers represented as linked lists
- Rotate list by k
- Partition list around a value x
- Copy list with random pointer
- Flatten a multilevel list
- Odd-even linked list
- **LRU Cache** (DLL + hash map)
- **Josephus problem** (circular list)

---

### Common Mistakes / Pitfalls

- **Dereferencing `nullptr`** – always check `cur` / `cur->next` before using `->`.
- **Losing the rest of the list** – save `cur->next` **before** changing `cur->next`.
- **Memory leaks** – every `new` needs a `delete` when the node is removed.
- **Dangling pointers** – don't use a node after `delete`-ing it; set pointers to `nullptr`.
- **Forgetting to update `head`** when inserting/deleting at the front (return the new head or pass `Node*&` / `Node**`).
- **Infinite loops in circular lists** – use `do-while` and compare against the start node, not `nullptr`.
- **Uninitialized `next`** – a local `Node n;` has a garbage `next`; always set it to `nullptr` (use a constructor).
- **Stack nodes vs heap nodes** – nodes created as local variables (e.g., `LinkedList llNode2;`) die when the function returns; use `new` for lists that must outlive the function.
- **Updating both links in a DLL** – forgetting to fix `prev` on one side is the #1 DLL bug.

---

### Advantages & Disadvantages (Summary)

**Advantages**
- Dynamic size; no need to know the number of elements beforehand.
- O(1) insertion/deletion at the front or at a known position.
- No memory shifting/reallocation when growing.
- Building block for stacks, queues, deques, hash-table chaining, adjacency lists (graphs), LRU caches.

**Disadvantages**
- No random access → O(n) to reach the i-th element.
- Extra memory for pointers.
- Poor cache locality → often slower than arrays in practice even when big-O looks the same.
- Reverse traversal impossible in SLL.
- More complex code; pointer bugs are easy to make.

---

### Applications

- Implementing **stacks** and **queues** (push/pop at head in O(1)).
- **Hash tables** with separate chaining (each bucket is a list).
- **Adjacency lists** for graphs.
- **Polynomial representation** (each node = coefficient + exponent).
- **Big-integer arithmetic** (digits stored in nodes).
- **Memory management** – free lists in allocators.
- **Undo/redo**, browser history, music playlists, image viewers.
- **OS scheduling** (circular list for round-robin).
