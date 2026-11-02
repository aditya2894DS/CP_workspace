# Backtracking

**Backtracking** is recursion that builds a solution one choice at a time, and **undoes** the last choice when it leads nowhere. It explores every possibility, but cuts off a branch as soon as it is clear that branch can't give a valid answer.

Think of it as walking through a maze: go forward, hit a dead end, step back to the last junction and try the next path.

---

## 1. The three steps: choose, explore, un-choose

| Step | What it does |
|---|---|
| **Choose** | Pick one option and add it to the current partial solution |
| **Explore** | Recurse to make the next choice |
| **Un-choose** | Remove that option so the state is clean for the next option |

The un-choose step is what makes it *backtracking*. Without it, choices from one branch leak into the next.

```cpp
void solve(State& state) {
    if (isComplete(state)) {          // base case: a full solution
        record(state);
        return;
    }
    for (Choice c : choicesFor(state)) {
        if (!isValid(state, c)) continue;   // pruning
        apply(state, c);                    // choose
        solve(state);                       // explore
        undo(state, c);                     // un-choose
    }
}
```

### Questions to answer before writing code
1. **What is the state?** What partial solution am I carrying? (current subset, current permutation, board…)
2. **What are the choices** at each step?
3. **When is the state complete?** That's the base case.
4. **When is a choice invalid?** That's the pruning condition.
5. **What do I undo?** Exactly the change made in "choose".

---

## 2. The recursion tree

Backtracking walks a tree of decisions depth-first. Each node is a partial solution; each edge is a choice; each leaf is a complete (or dead) state.

Subsets of `{1, 2, 3}` (take / skip each element):

```
                         []
              take 1 /        \ skip 1
                 [1]            []
            /       \        /      \
         [1,2]      [1]    [2]       []
         /   \     /  \    /  \     /  \
    [1,2,3][1,2][1,3][1][2,3][2]  [3]  []     ← 8 leaves = 2^3 subsets
```

**Pruning** means not going down a branch at all once you know it fails. Good pruning is what makes backtracking fast enough in practice.

---

## 3. Classic patterns

### 3.1 Subsets (include / exclude)

Each element is either in or out → `2^n` subsets.

```cpp
void subsets(int i, vector<int>& nums, vector<int>& cur, vector<vector<int>>& ans) {
    if (i == nums.size()) {
        ans.push_back(cur);
        return;
    }
    cur.push_back(nums[i]);          // choose: take nums[i]
    subsets(i + 1, nums, cur, ans);  // explore
    cur.pop_back();                  // un-choose
    subsets(i + 1, nums, cur, ans);  // skip nums[i]
}
```

**Time:** O(2^n · n) (2^n subsets, copying each costs up to n).

### 3.2 Permutations (used[] array)

Every position can take any element not already used → `n!` permutations.

```cpp
void permute(vector<int>& nums, vector<bool>& used, vector<int>& cur, vector<vector<int>>& ans) {
    if (cur.size() == nums.size()) {
        ans.push_back(cur);
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        if (used[i]) continue;
        used[i] = true;  cur.push_back(nums[i]);   // choose
        permute(nums, used, cur, ans);             // explore
        used[i] = false; cur.pop_back();           // un-choose
    }
}
```

Alternative: swap `nums[idx]` with each `nums[i]` for `i >= idx`, recurse on `idx + 1`, then swap back.

**Time:** O(n! · n).

### 3.3 Combinations / combination sum (start index)

Pass a `start` index so you never pick an earlier element again; this avoids duplicates like `[1,2]` and `[2,1]`.

```cpp
void combSum(int start, int target, vector<int>& c, vector<int>& cur, vector<vector<int>>& ans) {
    if (target == 0) { ans.push_back(cur); return; }
    for (int i = start; i < c.size(); i++) {
        if (c[i] > target) break;                    // prune (c is sorted)
        cur.push_back(c[i]);
        combSum(i, target - c[i], c, cur, ans);      // i, not i+1: reuse allowed
        cur.pop_back();
    }
}
```

Use `i + 1` instead of `i` when each element may be used only once.

### 3.4 Handling duplicates in the input

Sort first, then skip an element equal to the previous one **at the same level** of the tree:

```cpp
for (int i = start; i < nums.size(); i++) {
    if (i > start && nums[i] == nums[i - 1]) continue;  // same value already tried here
    ...
}
```

For permutations with duplicates: `if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;`

### 3.5 N-Queens (constraint checking)

Place one queen per row; a column is valid if no queen shares its column or either diagonal.

```cpp
int n;
vector<bool> col, diag1, diag2;   // diag1: r+c, diag2: r-c+n-1

void place(int r, int& count) {
    if (r == n) { count++; return; }
    for (int c = 0; c < n; c++) {
        if (col[c] || diag1[r + c] || diag2[r - c + n - 1]) continue;  // prune
        col[c] = diag1[r + c] = diag2[r - c + n - 1] = true;
        place(r + 1, count);
        col[c] = diag1[r + c] = diag2[r - c + n - 1] = false;
    }
}
```

The boolean arrays make each validity check O(1) instead of scanning the board.

### 3.6 Grid / maze search

Mark a cell visited before exploring from it, unmark it when you return, so other paths may use it.

```cpp
bool exist(vector<vector<char>>& g, string& w, int r, int c, int k) {
    if (k == w.size()) return true;
    if (r < 0 || c < 0 || r >= g.size() || c >= g[0].size() || g[r][c] != w[k]) return false;
    char saved = g[r][c];
    g[r][c] = '#';                                   // choose: mark visited
    bool found = exist(g, w, r + 1, c, k + 1) || exist(g, w, r - 1, c, k + 1)
              || exist(g, w, r, c + 1, k + 1) || exist(g, w, r, c - 1, k + 1);
    g[r][c] = saved;                                 // un-choose
    return found;
}
```

### 3.7 Sudoku (fill-the-blanks)

Find an empty cell, try digits 1–9 that are valid in its row, column and box, recurse; if nothing works, reset the cell and return `false` so the caller tries its next digit. Return `true` the moment the board is full to stop searching.

---

## 4. Patterns at a glance

| Problem | State | Choices per step | Base case | Typical time |
|---|---|---|---|---|
| Subsets | index, current list | take / skip | index == n | O(2^n · n) |
| Permutations | current list, used[] | any unused element | size == n | O(n! · n) |
| Combinations (k of n) | start, current list | elements from start | size == k | O(C(n,k) · k) |
| Combination sum | start, remaining target | elements from start | target == 0 | exponential |
| N-Queens | row, col/diag sets | column in this row | row == n | O(n!) |
| Word search / maze | cell, visited marks | 4 neighbours | word matched / exit | O(R·C·4^L) |
| Sudoku | board | digits 1–9 | no empty cell | O(9^empty) |

---

## 5. Find all vs. find one vs. count

| Goal | Return type | What changes |
|---|---|---|
| **All solutions** | `void`, push into `ans` | Explore every branch |
| **Any one solution** | `bool` | `if (solve(...)) return true;` stops at the first success |
| **Count solutions** | `int` or a counter | Add counts from children instead of storing lists |

---

## 6. Backtracking vs. plain recursion vs. DP

| | Plain recursion | Backtracking | DP |
|---|---|---|---|
| Purpose | Compute a value from smaller values | Search through all candidate solutions | Optimise / count with overlapping sub-problems |
| Undo step | No | Yes | No |
| Pruning | No | Yes | Not usually |
| Cost | Depends | Exponential in the worst case | Polynomial (states × transitions) |

If the same sub-problem is reached from many paths and only a number (count, min, max) is needed, try DP. If you need the actual list of solutions, or the constraints don't break into reusable sub-problems, backtracking is the tool.

---

## 7. Common mistakes

- **Forgetting to undo**: the state from one branch leaks into the next.
- **Pushing a reference instead of a copy**: `ans.push_back(cur)` copies in C++, but storing pointers or reusing one array without copying gives wrong results.
- **Generating duplicates**: use a `start` index for combinations, and sort + skip equal neighbours for duplicate inputs.
- **Checking validity too late**: prune *before* recursing, not at the leaf.
- **Passing big state by value**: pass by reference and undo, instead of copying vectors on every call.
- **Not stopping early** in "find one" problems: return `true` up the stack as soon as a solution is found.

---

## 8. Practice problems

1. Subsets / Subsets II (with duplicates)
2. Permutations / Permutations II
3. Combinations, Combination Sum I / II / III
4. Letter Combinations of a Phone Number
5. Generate Parentheses
6. Palindrome Partitioning
7. Word Search
8. N-Queens / N-Queens II
9. Sudoku Solver
10. Rat in a Maze
