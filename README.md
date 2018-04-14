# Summary

* This is a simple alignment performance test.
* Use the `__attribute__((packed, aligned(1)))`to compress struct size and cause misalignment.
* Use macro to reuse measurement function.
* In modern Intel processors, there is apparently no performance impact on misaligned memory accesses.

# Build
* `$ make`

## Result of execution
```
size of align : 12
size of small : 8
size of non : 7
align:       18384 us
small:       11939 us
non:         11628 us
```

# License
`align_test` is freely redistributable under the two-clause BSD License.
Use of this source code is governed by a BSD-style license that can be found
in the `LICENSE` file.
