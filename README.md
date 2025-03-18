# SegmentsDistance
Example code for calculating the distance between 3d segments

Currently, this library can provide precision corresponding to the double type.
The code was tested on Windows 10 using MSYS2.

You can test it by following a few steps (assuming you have gtest installed beforehand)

1. Clone the project to the desired folder.
2. Open MSYS2 Shell in that folder
3. cd SegmentsDistance
4. mkdir build && cd build
5. cmake ..
6. cmake --build .
7. ./tests.exe

You should see output indicating that the appropriate tests passed, ending with something similar to
[----------] Global test environment tear-down
[==========] 36 tests from 3 test suites ran. (1 ms total)
[  PASSED  ] 36 tests.
