1: Quicksort Space Usage

a. Items Iterated
For each call to quicksort, the function iterates over n-1 elements to partition the array based on the pivot.

b. Extra Space Usage
In each call, quicksort operates in-place and doesn't create new arrays for the less than or greater than partitions. The space used is mainly due to the recursive call stack. The maximum additional space required in a single call is for the recursive calls, which in the worst case could be O(n) due to n recursive calls each needing space on the call stack.

c. Total Additional Space
The total space used by quicksort is dictated by the depth of the recursion. For balanced splits, the depth is log n, resulting in a space complexity of O(log n). However, in the worst case of unbalanced splits, each recursive call only reduces the problem size by one, leading to a space complexity of O(n).

2: Mergesort Worst Case

Worst-case Array for Mergesort:
{12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}

This array causes the worst-case performance for mergesort because it requires the maximum number of comparisons and movements. Each merge step has to compare every element from the left subarray with every element in the right subarray, resulting in a significant amount of work for each merge operation. This array ensures that each merge operation is as involved as possible, demonstrating the worst-case time complexity of mergesort.The time complexity remains O(n log n) because the merge operations are consistently the same regardless of the array's initial order.
