# Sorting Algorithm Complexity

## Bubble Sort

- **Worst-Case:** O(n^2) - each element compared with every other.
- **Best-Case:** O(n^2) without optimization. With optimization, O(n) - check for swaps with flag.

## Selection Sort

- **Worst-Case:** O(n^2) - searches for minimum element for each element.
- **Best-Case:** O(n^2) - same number of comparisons regardless of array order.
- **Additional Storage:** None - in-place sorting algorithm.

## C Library Sort (`qsort`)

- **Complexity:** Generally O(n log n). May vary as it can use quicksort, mergesort, or introsort.
- **Efficiency:** Balances worst-case performance, average-case performance, and practical considerations.

