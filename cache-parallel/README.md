2020-07-22

This is a simple demonstration showing the effects of cache bouncing. The idea here is that there are 2 threads modifying the same data structure. In `has-bounce`, the threads are modifying data in the same cache line. In `no-bounce`, padding is added to the data structure so the threads are modifying data in *different* cache lines. We expect `no-bounce` to run faster than `has-bounce`, so we run each target a few times and measure its average execution time.
