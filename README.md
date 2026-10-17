<h1 align="center">Student Grade Calculator</h1>
<p align="center">C++ coursework · System programming · v0.2</p>

---

A console program for calculating student grades. Enter students and marks yourself or generate random marks, or load student data from a file.

## What it does

- Loads student data from a file you choose.
- Generates student files containing 1,000 to 10 million records.
- Saves sorted students into `passed.txt` (grade ≥ 5) and `failed.txt` (grade < 5).
- Shows how long file processing takes.

## Grade calculation

| Method | Formula |
| --- | --- |
| Average | `0.4 × homework average + 0.6 × exam mark` |
| Median | `0.4 × homework median + 0.6 × exam mark` |

## Build and run

Open a terminal in the project folder and compile:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp Person.cpp FileGenerator.cpp ResultsWriter.cpp -o students
```

- `-std=c++17` — use C++17.
- `-O2` — enable optimizations to help the program run faster.
- `-Wall -Wextra -pedantic` — show warnings about possible problems in the code.
- `-o students` — name the finished program `students`.

Then run it:

```bash
./students
```

## Using the program

1. Choose whether to calculate grades or generate a student file.
2. To generate a file, choose its size. The program creates it and exits.
3. To calculate grades, choose average or median.
4. Choose manual input or file input.
5. Enter the students yourself, or enter the input filename.
6. Choose how to sort the students.
7. Find the results in `passed.txt` and `failed.txt`.

Each output file shows the final grade calculated using your chosen method.
Existing output files with these names are replaced.

**Manual marks:** enter one whole number from `1` to `10` per line. At least five homework marks are required; enter `-1` when finished. You can enter more than five.

**Random marks:** the program generates five homework marks and one exam mark, all between `1` and `10`.

## File input

Enter the filename when asked, for example `students-test.txt` or
`students-1000.txt`. You do not need to rename it to `Students.txt`.
Filenames are case-sensitive on Linux.

The first line is a header. Each following line contains a first name, surname, homework marks, and the exam mark **last**. Use spaces or tabs between values; each name must be a single word.

```text
Name    Surname    HW1 HW2 HW3 HW4 HW5 Exam
Anna    Smith      8   7   9   6   10  9
Ben     Jones      6   5   8   7   9   8
```

File input accepts one or more homework marks per student, followed by an exam mark. All marks must be whole numbers from `1` to `10`. An invalid student row stops file loading with an error message.


## Benchmarking

I tested five file sizes, from 1,000 to 10 million students.
I ran each test three times and calculated the average time.

For every test, I chose the average-based final grade and sorted students
from the lowest grade to the highest. I compiled the program with `-O2`,
which enables compiler optimizations to help it run faster.

The table shows how long each step took, in **seconds**:

- **Read + calculate:** load students from the file and calculate their grades.
- **Sort:** put students in order by their final grade.
- **Split:** separate students into passed and failed groups.
- **Write both files:** save those groups to `passed.txt` and `failed.txt`.
- **Total:** add together the time taken by these four steps.

| Students | Read + calculate | Sort | Split | Write both files | Total |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 1,000 | 0.002805 | 0.000474 | 0.000311 | 0.000832 | 0.004421 |
| 10,000 | 0.024016 | 0.005469 | 0.002940 | 0.004038 | 0.036465 |
| 100,000 | 0.196390 | 0.061814 | 0.019878 | 0.029285 | 0.307368 |
| 1,000,000 | 1.786808 | 0.655694 | 0.222855 | 0.298374 | 2.963732 |
| 10,000,000 | 10.828244 | 4.559837 | 1.221706 | 1.821977 | 18.431765 |

Reading the students and calculating their grades took the longest.
Sorting was the next slowest step.

For 10 million students, these steps took about **18.43 seconds** in total.

Time spent choosing menu options is not included.