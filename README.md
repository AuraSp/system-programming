# Student Grade Calculator

C++ coursework · System Programming · **V0.25**

---

A console program for calculating student grades. Students and marks can be entered manually, generated randomly, or loaded from a file.

Version V0.25 compares the performance of three C++ containers: `std::vector`, `std::list`, and `std::deque`.

## What it does

- Loads student data from a selected file.
- Generates student files containing 1,000 to 10 million records.
- Calculates final grades using the average or median.
- Sorts students by name or final grade.
- Saves students into `passed.txt` (grade ≥ 5) and `failed.txt` (grade < 5).
- Measures file reading, sorting, splitting, and writing times.
- Supports three container implementations for performance comparison.

## Grade calculation

| Method | Formula |
|---|---|
| Average | `0.4 × homework average + 0.6 × exam mark` |
| Median | `0.4 × homework median + 0.6 × exam mark` |

## Containers

Three implementations of the program were prepared:

| Container | Description |
|---|---|
| `std::vector` | Stores elements in continuous memory |
| `std::list` | Stores elements in linked nodes |
| `std::deque` | Stores elements in blocks of memory |

Each implementation performs the same operations but uses a different container for storing students.

## Build and run

The original V0.2 implementation can be compiled using:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp Person.cpp FileGenerator.cpp ResultsWriter.cpp -o students-vector
```

The `list` and `deque` implementations are compiled separately from their corresponding source versions, using the same compiler options.

The three executable versions used during testing were:

```bash
./students-vector.exe
./students-list.exe
./students-deque.exe
```

Compiler options:

- `-std=c++17` — use C++17.
- `-O2` — enable compiler optimizations.
- `-Wall -Wextra -pedantic` — show possible code problems and warnings.
- `-o` — specify the executable name.

## Using the program

1. Choose whether to calculate grades or generate a student file.
2. To generate a file, select its size. The program creates the file and exits.
3. To calculate grades, choose average or median.
4. Choose manual input or file input.
5. Enter students or select an existing file.
6. Choose how to sort the students.
7. Find the results in `passed.txt` and `failed.txt`.

Existing output files with these names are replaced.

**Manual marks:** Enter whole numbers from `1` to `10`. At least five homework marks are required. Enter `-1` to finish.

**Random marks:** The program generates five homework marks and one exam mark, each between `1` and `10`.

## File input

The first line contains the header. Each following line contains a student's first name, surname, homework marks, and exam mark last.

```text
Name    Surname    HW1 HW2 HW3 HW4 HW5 Exam
Anna    Smith      8   7   9   6   10  9
Ben     Jones      6   5   8   7   9   8
```

File input accepts one or more homework marks per student. All marks must be whole numbers between `1` and `10`.

An invalid row stops file loading and displays an error message.

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

However, only two of the five required file sizes were tested for V0.25. Larger files would be needed to make a more reliable comparison and determine how the containers perform with millions of records.

The original V0.2 benchmarks are kept separately because they were collected in an earlier testing session and should not be treated as directly comparable measurements.

Menu interaction and file generation times are not included in the benchmarks.