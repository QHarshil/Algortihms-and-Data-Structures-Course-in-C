1. Insertion Sort on [0, 1, 2, 3, 4, 5]

    Big O: O(n) - Best-case scenario as the array is already sorted.
    Operations: Approximately n, with 1 comparison per element.

2. Insertion Sort on [5, 4, 3, 2, 1, 0]

    Big O: O(n²) - Worst-case scenario with the array in reverse order.
    Operations: Roughly (n*(n-1))/2, due to comparing each element with all previously sorted elements.

3. Comparison of Bubble, Selection, and Insertion Sort

    Bubble Sort:
        Best Case: O(n) (if optimized to detect no swaps with flag in loop).
        Worst Case: O(n²) (n-1 passes with pairwise comparisons).

    Selection Sort:
        Both Best and Worst Case: O(n²) (n-1 passes, finding and placing the minimum element).

    Insertion Sort:
        Best Case: O(n) (array already sorted).
        Worst Case: O(n²) (array in reverse order).

4. Which Sort is the Best?
    Overall, all three are similar for smaller data sets but when n>1000000, it is extremely inefficient.
    Qsort or merge sort is much faster in these scenerios.

    Insertion Sort:
        Best for small or nearly sorted datasets. It's stable and efficient with minimal swaps.
        Use when dealing with small lists or high swap costs.

    Bubble Sort:
        Simple and can detect an already sorted list efficiently.
        Use when data is almost sorted because of optimization with flag to check for swaps
    Selection Sort:
        Minimizes the number of swaps (good when swaps are costly).
        Use when memory write is a costly operation.
