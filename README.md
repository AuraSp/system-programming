# Student Grade Calculator

C++ coursework · System Programming · **V1.0**

---

A console program for calculating student grades. Enter students manually, generate random marks or student files, or load students from an existing file.

V1.0 compares three containers and two ways of separating students into passed and failed groups. It also compares a manual splitting loop with standard library algorithms.

## Releases

| Version | Main changes |
|---|---|
| V0.1 | Student class, average and median calculations, input validation, random marks, file input, and sorting. |
| V0.2 | Code separated into header and source files, large student-file generation, passed/failed output files, and processing timers. |
| V0.25 | Separate vector, list, and deque implementations for comparison. The earlier recorded tests covered 1,000 and 10,000 students. |
| V0.25.1 | Corrected release containing the list and deque source folders. |
| V1.0 | Two splitting strategies, tests across all five file sizes, an algorithm-based splitting comparison, peak-memory measurements, and Make/CMake builds. |

## What it does

- Loads student data from a file-selection menu, with option `0` for a filename or path entered manually.
- Generates files containing 1,000, 10,000, 100,000, 1 million, or 10 million students.
- Calculates final grades using the homework average or median.
- Sorts students by name or final grade, in either direction.
- Separates students into **passed** (final grade ≥ 5.0) and **failed** (final grade < 5.0).
- Saves the groups into `passed.txt` and `failed.txt`.
- Reports reading/calculation, sorting, splitting, and writing times for file processing.


## Grade calculation

| Method | Formula |
|---|---|
| Average | `0.4 × homework average + 0.6 × exam mark` |
| Median | `0.4 × homework median + 0.6 × exam mark` |

The selected method is used for grade sorting and deciding whether a student passes.

## Project structure

| Files or folder | Purpose |
|---|---|
| Root `main.cpp` | Vector version: menus and processing steps. |
| `Person.h` / `Person.cpp` | Student data, input, grade calculations, and student output. |
| `FileGenerator.h` / `FileGenerator.cpp` | Generates student input files. |
| `ResultsWriter.h` / `ResultsWriter.cpp` | Writes the passed and failed groups with headers. |
| `list/` | List version, with its own source and header files. |
| `deque/` | Deque version, with its own source and header files. |
| `Makefile` | Builds all three versions on Unix systems. |
| `CMakeLists.txt` | Configures builds for different operating systems and compilers. |

`std::vector` stores student objects in contiguous memory. `std::list` stores them in linked nodes. `std::deque` stores them in blocks. These descriptions refer to the student objects themselves; their strings and homework vectors can allocate additional memory.

## Build and run

### Make — Unix

Requirements: a C++17 compiler and Make. Open a terminal in the project folder and run:

```bash
make
```

This builds all three programs. Run the version you want:

```bash
./students-vector
./students-list
./students-deque
```

You can also build just one version:

```bash
make students-list
```

To remove the three compiled programs and rebuild:

```bash
make clean
make
```

`make clean` does not remove source files or student data. If Make reports that nothing needs doing, the programs are already up to date.

The Makefile uses these compiler options:

- `-std=c++17` — use C++17.
- `-O2` — enable compiler optimizations; this is the setting used for the timing comparisons below.
- `-Wall -Wextra -pedantic` — show warnings about possible code problems.

### CMake — Linux, Windows, or macOS

Requirements: CMake 3.16 or newer, a C++17 compiler, and build tools supported by that compiler.

From the project folder:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

The first command prepares the build directory. The second compiles the programs. Release mode enables optimizations, but its exact compiler flags can differ from the Makefile's `-O2` setting.

On Ubuntu, run:

```bash
./build/students-vector
```

With a Visual Studio generator on Windows, run from PowerShell:

```powershell
.\build\Release\students-vector.exe
```

With a single-configuration Windows generator, such as Ninja, the executable is normally directly inside `build`. Replace `students-vector` with `students-list` or `students-deque` to run the other versions.

Run from the project folder if you want the program to find input files there and save its results there. Files are read or written relative to the terminal's current folder, not necessarily the executable's folder.


## Using the program

1. Start one of the three programs.
2. Choose **calculate student grades** or **generate a student file**.
3. For generation, select a size. The program creates `students-1000.txt`, `students-10000.txt`, `students-100000.txt`, `students-1000000.txt`, or `students-10000000.txt`, then exits. Run it again to process that file.
4. For calculation, choose **average** or **median**.
5. Choose a splitting strategy and the input source. The vector version asks for the strategy before the source; the list and deque versions ask after reading the students.
6. For manual input, enter the students. For file input, choose a listed file, or enter `0` to type a filename or path.
7. Choose sorting by name A–Z, name Z–A, lowest final grade first, or highest final grade first.
8. Open `passed.txt` and `failed.txt` to see the sorted groups and their headers. For file input, the terminal also shows processing times.

**Output files are replaced on each run.** Copy or rename them first if you want to keep an earlier result. Generated input files with the same name are also replaced.

**Manual marks:** Enter one whole number from `1` to `10` per line. At least five homework marks are required; enter `-1` when finished. You can enter more than five.

**Random marks:** During manual student entry, the program can generate five homework marks and one exam mark. You still enter the student's names. The separate file-generation option supplies names such as `Name1 Surname1` automatically.


## File input

The first line is a header. Each following line contains a first name, surname, homework marks, and the exam mark **last**. Use spaces or tabs between values; each name must be a single word.

```text
Name    Surname    HW1 HW2 HW3 HW4 HW5 Exam
Anna    Smith      8   7   9   6   10  9
Ben     Jones      6   5   8   7   9   8
```

File input accepts one or more homework marks per student, followed by an exam mark. All marks must be whole numbers between `1` and `10`. An invalid row stops loading and displays an error.

The file menu lists `.txt` candidates; a `.txt` extension alone does not guarantee valid student data. Input files are not included as large datasets in the repository: generate one first or provide your own. On Linux, filenames are case-sensitive.

## Splitting strategies

| Strategy | What happens | Where passed students remain |
|---|---|---|
| 1 | Keep the original container and copy each student into either a new passed group or a new failed group. | New `passed` container. |
| 2 | Put failed students into a separate container and remove them from the original group. | Original `students` container. |

In strategy 1, each student is copied into **one** of the two new groups, not both. The original copy remains too.

For strategy 2, vector and deque keep passed students together by shifting them towards the beginning, then resizing the container. Failed students are copied to the failed group. This avoids repeatedly deleting from the middle. List uses `splice()` to transfer existing nodes into the failed group without copying the student objects.

Both strategies preserve the order established by sorting. List uses its member `sort()`; vector and deque use `std::sort`. Students with equal sorting keys may appear in different orders across container types.

## Benchmarking — V1.0

### Test setup

- Linux x86-64, kernel `6.17.0-41-generic`.
- GCC / g++ `15.2.0`.
- Compiler options: `-std=c++17 -O2 -Wall -Wextra -pedantic`.
- Average-based final grade; sorting by final grade, lowest first.
- The same input file for each container and strategy at each size.
- Five sizes: 1,000, 10,000, 100,000, 1 million, and 10 million students.
- Three runs per combination, run sequentially; the tables show the averages.

The initial comparison contains **90 runs**: five sizes × three containers × two strategies × three repeats. The algorithm comparison adds **15 runs** for deque strategy 1.

Times are in **seconds**:

- **Read + calculate:** load student records and calculate their grades.
- **Sort:** order the students using the selected sorting rule.
- **Split:** divide them into passed and failed groups.
- **Write:** save both result files.
- **Total:** sum of these four measured steps.

Compilation, menu interaction, file generation, process startup, and result checks are excluded. Input files were read before testing, so operating-system caching may affect the results. Other programs and system activity can also affect timings. Independently rounded columns may not add up exactly to the displayed total.

### Original splitting implementation

These tables show the initial implementations, before replacing the deque strategy 1 loop with algorithms.

#### 1,000 students

| Container | Strategy | Read + calculate | Sort | Split | Write | Total |
|---|---:|---:|---:|---:|---:|---:|
| Vector | 1 | 0.002508 | 0.000407 | 0.000256 | 0.000445 | 0.003616 |
| Vector | 2 | 0.002213 | 0.000389 | 0.000109 | 0.000440 | 0.003150 |
| List | 1 | 0.002122 | 0.000173 | 0.000168 | 0.000481 | 0.002944 |
| List | 2 | 0.002177 | 0.000171 | 0.000010 | 0.000447 | 0.002805 |
| Deque | 1 | 0.002137 | 0.000498 | 0.000133 | 0.000411 | 0.003180 |
| Deque | 2 | 0.002182 | 0.000424 | 0.000088 | 0.000410 | 0.003105 |

#### 10,000 students

| Container | Strategy | Read + calculate | Sort | Split | Write | Total |
|---|---:|---:|---:|---:|---:|---:|
| Vector | 1 | 0.020801 | 0.004270 | 0.002216 | 0.003179 | 0.030467 |
| Vector | 2 | 0.021745 | 0.004070 | 0.001239 | 0.002949 | 0.030003 |
| List | 1 | 0.020692 | 0.002301 | 0.001504 | 0.003531 | 0.028028 |
| List | 2 | 0.019955 | 0.001877 | 0.000113 | 0.003065 | 0.025010 |
| Deque | 1 | 0.021209 | 0.004942 | 0.001162 | 0.003173 | 0.030486 |
| Deque | 2 | 0.018631 | 0.004254 | 0.000675 | 0.002896 | 0.026455 |

#### 100,000 students

| Container | Strategy | Read + calculate | Sort | Split | Write | Total |
|---|---:|---:|---:|---:|---:|---:|
| Vector | 1 | 0.161195 | 0.040274 | 0.016468 | 0.024482 | 0.242419 |
| Vector | 2 | 0.153084 | 0.037847 | 0.009543 | 0.021719 | 0.222193 |
| List | 1 | 0.146893 | 0.027669 | 0.013147 | 0.023912 | 0.211621 |
| List | 2 | 0.147339 | 0.027692 | 0.004717 | 0.031004 | 0.210752 |
| Deque | 1 | 0.168599 | 0.047424 | 0.010210 | 0.024083 | 0.250315 |
| Deque | 2 | 0.161292 | 0.045256 | 0.006282 | 0.022423 | 0.235253 |

#### 1,000,000 students

| Container | Strategy | Read + calculate | Sort | Split | Write | Total |
|---|---:|---:|---:|---:|---:|---:|
| Vector | 1 | 1.188105 | 0.448466 | 0.144794 | 0.166289 | 1.947653 |
| Vector | 2 | 1.103485 | 0.375600 | 0.067998 | 0.165484 | 1.712567 |
| List | 1 | 1.080877 | 0.850860 | 0.275726 | 0.277073 | 2.484536 |
| List | 2 | 1.166623 | 0.796875 | 0.233067 | 0.428382 | 2.624947 |
| Deque | 1 | 1.158385 | 0.414485 | 0.069198 | 0.169205 | 1.811272 |
| Deque | 2 | 1.183052 | 0.412016 | 0.050597 | 0.168997 | 1.814662 |

#### 10,000,000 students

| Container | Strategy | Read + calculate | Sort | Split | Write | Total |
|---|---:|---:|---:|---:|---:|---:|
| Vector | 1 | 10.941676 | 4.495339 | 1.285383 | 1.575143 | 18.297541 |
| Vector | 2 | 10.869933 | 4.596450 | 0.609851 | 1.607881 | 17.684115 |
| List | 1 | 9.879201 | 18.522673 | 2.708293 | 1.688331 | 32.798497 |
| List | 2 | 10.193884 | 18.556290 | 2.556258 | 4.057654 | 35.364086 |
| Deque | 1 | 10.187072 | 4.967016 | 0.665646 | 1.605510 | 17.425244 |
| Deque | 2 | 10.333730 | 5.193507 | 0.486529 | 1.696823 | 17.710590 |

### What the timings show

List strategy 2 had the lowest average total time for 1,000, 10,000, and 100,000 students. Vector strategy 2 was fastest at 1 million. Deque strategy 1 had the lowest average total at 10 million: **17.43 seconds**.

Deque strategy 1 was selected for the algorithm comparison because it had the lowest total on the largest file. Its lead over vector strategy 2 was only about **1.5%**, and individual run times overlapped, so this does not establish deque as the fastest container in every situation.

For 10 million students, sorting was the largest cost for list. List strategy 2 split faster than list strategy 1, but its writing stage took longer, so its total was higher. The measurements show the difference; they do not isolate its underlying cause.

### Replacing the loop with algorithms

In deque strategy 1, the original loop was replaced by two calls to `std::remove_copy_if`, using `std::back_inserter` to append results:

- Copy students to `passed`, skipping grades below 5.0.
- Copy students to `failed`, skipping grades at or above 5.0.

The original students remain unchanged. This keeps strategy 1's behavior and the order inside each group. Both implementations were checked on the small test file and produced identical result files.

The original loop visits each student once. The new version visits the students twice. Standard algorithms can express an operation clearly, but do not automatically make it faster.

| Students | Original split | Algorithm split | Original total | Algorithm total |
|---:|---:|---:|---:|---:|
| 1,000 | 0.000133 | 0.000154 | 0.003180 | 0.003404 |
| 10,000 | 0.001162 | 0.001090 | 0.030486 | 0.026761 |
| 100,000 | 0.010210 | 0.012061 | 0.250315 | 0.267394 |
| 1,000,000 | 0.069198 | 0.077256 | 1.811272 | 1.860085 |
| 10,000,000 | 0.665646 | 0.813961 | 17.425244 | 17.605476 |

The algorithm version's splitting stage was slower at four of the five sizes. At 10 million students, splitting took about **22% longer**: 0.666 seconds versus 0.814 seconds. Total processing rose from 17.43 to 17.61 seconds, about **1%**. The full run includes unchanged stages and normal timing variation, so not every total-time difference can be attributed to splitting.

The deque strategy 1 source retains this algorithm version for the assignment comparison. The original timing tables above remain clearly separate from the results after the change.

### Peak memory usage

Memory was measured separately using the same **1-million-student file**, average-based grades, and lowest-grade-first sorting. Each table entry is an individual run, not a three-run average.

On Ubuntu, the command was:

```bash
/usr/bin/time -f "\nPeak RAM: %M KiB" ./students-vector
```

The command was repeated for each strategy and for `students-list` and `students-deque`. It reports the **whole process's peak resident memory**, not just memory allocated during splitting. The deque measurements were taken after the algorithm change.

| Container | Strategy 1 (KiB) | Strategy 2 (KiB) | Strategy 1 (MiB) | Strategy 2 (MiB) | Reduction |
|---|---:|---:|---:|---:|---:|
| Vector | 399,232 | 262,500 | 389.9 | 256.3 | 34.2% |
| List | 347,548 | 175,736 | 339.4 | 171.6 | 49.4% |
| Deque | 312,164 | 221,916 | 304.8 | 216.7 | 28.9% |

Strategy 2 used less peak RAM for all three containers in these tests. It avoids keeping a second full set of student objects, which supports the assignment's memory-efficiency claim.

For vector, `resize()` reduces the number of elements but does not reduce its capacity. Allocators can also retain freed memory. Therefore, removing students does not mean the same amount of RAM is immediately returned to the operating system. List's `splice()` reuses existing nodes rather than creating student copies.

## Earlier benchmark results

The following V0.2 and V0.25 results are preserved from earlier testing sessions. They should not be treated as direct speed comparisons with V1.0 because the testing environment and implementation may differ.

## Benchmarking — V0.2

The original version was tested using five file sizes, from 1,000 to 10 million student records.

Each test was performed three times, and average execution times were calculated.

The tests used average-based final grades and sorting from the lowest grade to the highest. The program was compiled with `-O2`.

All times are in **seconds**.

| Students | Read + calculate | Sort | Split | Write | Total |
|---:|---:|---:|---:|---:|---:|
| 1,000 | 0.002805 | 0.000474 | 0.000311 | 0.000832 | 0.004421 |
| 10,000 | 0.024016 | 0.005469 | 0.002940 | 0.004038 | 0.036465 |
| 100,000 | 0.196390 | 0.061814 | 0.019878 | 0.029285 | 0.307368 |
| 1,000,000 | 1.786808 | 0.655694 | 0.222855 | 0.298374 | 2.963732 |
| 10,000,000 | 10.828244 | 4.559837 | 1.221706 | 1.821977 | 18.431765 |

Reading and calculating grades took the longest, followed by sorting.

Processing 10 million students took approximately **18.43 seconds**.

## Benchmarking — V0.25

For V0.25, the program was tested using three different containers:

- `std::vector`
- `std::list`
- `std::deque`

I tested files containing 1,000 and 10,000 student records. Each container was tested three times with the same input file.

The following settings were used:

- Final grade calculated using the average.
- Students sorted by final grade, lowest first.
- The same input file used for every container.
- Execution times measured separately for reading, sorting, splitting, and writing.

All results below are averages of three runs, measured in seconds.

### 1,000 students

| Operation | Vector | List | Deque |
|---|---:|---:|---:|
| Read + calculate | 0.005773 | 0.005237 | 0.006537 |
| Sort | 0.000197 | 0.000241 | 0.000862 |
| Split | 0.000322 | 0.000371 | 0.000268 |
| Write both files | 0.011950 | 0.005388 | 0.005685 |
| **Total** | **0.018243** | **0.011237** | **0.013352** |

### 10,000 students

| Operation | Vector | List | Deque |
|---|---:|---:|---:|
| Read + calculate | 0.045606 | 0.043711 | 0.039340 |
| Sort | 0.003134 | 0.002718 | 0.015871 |
| Split | 0.004023 | 0.003300 | 0.002320 |
| Write both files | 0.030008 | 0.029290 | 0.032323 |
| **Total** | **0.082771** | **0.079019** | **0.089854** |

### Results and observations

The `std::list` container had the lowest average total processing time for both tested file sizes.

For 1,000 students, `std::vector` had the fastest sorting time. However, its third test had a much longer file-writing time, which increased the total average.

For 10,000 students, `std::list` had the fastest sorting time, while `std::deque` had the fastest reading and splitting times.

These differences are small, and execution times can be affected by other processes running on the computer, memory allocation, and file operations.

### Conclusion

The results show that all three containers can be used to process student records, but their execution times differ depending on the operation.

For the tested datasets, `std::list` achieved the lowest average total processing time.

Only two of the five required file sizes were recorded for V0.25. The V1.0 tests above now cover all five sizes for every container and both splitting strategies; they are reported as new V1.0 measurements, not historical V0.25 results.

The original V0.2 benchmarks are kept separately because they were collected in an earlier testing session and should not be treated as directly comparable measurements.

Menu interaction and file generation times are not included in the benchmarks.