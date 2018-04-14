# Summary

* This is a simple alignment performance test.
* Use the `__attribute__((packed, aligned(1)))`to compress struct size and cause misalignment.
* Use macro to reuse measurement function.
* In modern Intel processors, there is apparently no performance impact on misaligned memory accesses.

# Build
* `$ make`

## Target
Intel(R) Core(TM) i5-3210M CPU @ 2.50GHz
Raspberry pi Cortex-A53

## Structure format
```
struct align_struct{
    char a;
    int b;
    short c;
};

struct small_align_struct{
    int b;
    char a;
    short c;
};

struct non_align_struct{
    char a;
    short c;
    int b;
}__attribute__((packed, aligned(1)));

```

## Result of execution
```
/*i5-3210M*/
size of align : 12
size of small : 8
size of non : 7
align:       18384 us
small:       11939 us
non:         11628 us

/*raspberry pi cortex-a53*/
size of align : 12
size of small : 8
size of non : 7
align:       83704 us
small:       54211 us
non:         120929 us

```

# License
`align_test` is freely redistributable under the two-clause BSD License.
Use of this source code is governed by a BSD-style license that can be found
in the `LICENSE` file.
