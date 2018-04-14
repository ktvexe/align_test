# Summary

* This is a simple alignment performance test.
* Use the `__attribute__((packed, aligned(1)))`to compress struct size and cause misalignment.
* Use macro to reuse measurement function.
* In modern Intel processors, there is apparently no performance impact on misaligned memory accesses.

# Build
* `$ make`

## Target
Intel(R) Core(TM) i5-3210M CPU @ 2.50GHz
Raspberry pi (Cortex-A53)
Nvidia Jetson TX2 (Nvidia Denver+ Cortex-A57)

## Structure format
```
struct align_struct{
    char a;
    long b;
    short c;
};

struct small_align_struct{
    long b;
    char a;
    short c;
};

struct non_align_struct{
    char a;
    short c;
    long b;
}__attribute__((packed, aligned(1)));

```

## Result of execution
```
/*i5-3210M*/
size of align : 24
size of small : 16
size of non : 11
align:       16558.890000 us
small:       16595.660000 us
non:         16428.910000 us

/*raspberry pi cortex-a53*/
size of align : 12
size of small : 8
size of non : 7
align:       142991.250000 us
small:       142419.390000 us
non:         230372.380000 us

/*Nvidia Jetson TX2*/
size of align : 24
size of small : 16
size of non : 11
align:       67109.010000 us
small:       66879.990000 us
non:         81452.380000 us

```

# License
`align_test` is freely redistributable under the two-clause BSD License.
Use of this source code is governed by a BSD-style license that can be found
in the `LICENSE` file.
