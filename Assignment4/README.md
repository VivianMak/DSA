# Assignment 4: Sorting Algorithms

## Implemented Algorithms and Time Complexity

| Algorithm | Time Complexity | Analysis
| --- | --- | --- |
| Insertion Sort | O(n²) | It scans the entire list, then shifts all n elements |
| Selection Sort | O(n²) | It scans the entire list to find the minimum so the average is n² operations |
| Heap Sort | O(n log n) | Every time a heap is built takes n operations, then the extractions is dependent on the height of the tree which yields log n |
| Radix Sort | O(d · (n + k)) | It looks at k=10 possible digits up to d times which represents the highest digits_place in your list |

<br>

# Sorting Algorithm Benchmarking

My approach to benchmarking the different algorithms was to use a giant nested for loop to test lists of 6 different sizes: `{10, 100, 1000, 10000, 100000, 200000}` across 5 trials. For Heap and Radix Sort, I tested lists with more elements. Then I took the average length (in seconds) of those trials. Below are my results:

| Size | Insertion Sort | Selection Sort | Heap Sort | Radix Sort |
| --- | --- | --- | --- | --- |
| 10 | 0.000001 | 0.000002 | 0.000003 | 0.000006 |
| 100 | 0.000032 | 0.000055 | 0.000034 | 0.000016 |
| 1000 | 0.002871 | 0.003691 | 0.000439 | 0.000146 |
| 10000 | 0.061938 | 0.121089 | 0.003440 | 0.000979 |
| 100000 | 6.141732 | 1.873824 | 0.024269 | 0.004166 |
| 200000 | 24.736893 | 48.966340 | 0.051644 | 0.007265 |
| 1000000| n/a | n/a | 0.330172 | 0.035464 |


```sh
$ cmake ..
$ make && ./benchmark
```

<br>

## Practice with the Master Theorum
[masters_theorum_worksheet.pdf](~/Assignment4/masters_theorum_worksheet.pdf)