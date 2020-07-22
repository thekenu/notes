A 2D array in C is inherently one-dimensional, which means the order in which the array is accessed affects cache performance.

Consider a 3 x 3 matrix (e.g. `int arr[3][3]`). Its memory layout looks like

Low Address  --->  High Address
[0][0] [0][1] [0][2] [1][0] [1][1] [1][2] [2][0] [2][1] [2][2]

Note that this memory layout is called row-major order, which is an instrinsic property of the C language. On the contrary, Fortran uses column-major order.

The following loop accesses the array using the order in which the elements are laid out in memory. This reduces cache misses.

```
for (int i = 0; i < 3; i++) {
  for (int j = 0; j < 3; j++) {
    arr[i][j] = 0;
}
```

If we were to swap the inner and outer loop, cache misses will be more frequent and the execution time will be longer. This can be reliably measured using `perf` and `time`.

```
for (int j = 0; j < 3; j++) {
  for (int i = 0; i < 3; i++) {
    arr[i][j] = 0;
}
```

References:
[1] https://en.wikipedia.org/wiki/Loop_interchange#The_utility_of_loop_interchange 
[2] https://developers.redhat.com/blog/2014/03/10/determining-whether-an-application-has-poor-cache-performance-2/
