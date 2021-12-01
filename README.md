# adventofcode2021 - 01 Part 2

Part 2 is equivalent to part 1, except that now not single values are compared but sliding windows of 3. These 3 values are accumulated and compared. The output again is the number of 3 value sets that are greater than the 3 value set preceeding it.

## How to compile

All programs are written in C++ and can be built using CMake. Therefore, to make an out-of-source build, enter
``` bash
mkdir build && cd build
cmake ..
make
```
