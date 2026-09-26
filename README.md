<h1 align="center">Student Grade Calculator</h1>
<p align="center">C++ coursework · System programming · v0.1</p>

---

A console program for calculating student grades. Enter students and marks yourself or generate random marks, or load student data from a file.

## What it does

- Calculates final grades using the homework **average or median**.
- Generates five homework marks and an exam mark using `std::mt19937`.
- Reads student data from `Students.txt` and displays both calculation results.
- Sorts students by first name or final grade, in either direction.
- Checks numeric input and displays grades with two decimal places.

## Grade calculation

| Method | Formula |
| --- | --- |
| Average | `0.4 × homework average + 0.6 × exam mark` |
| Median | `0.4 × homework median + 0.6 × exam mark` |

## Build and run

With `g++` installed, open a terminal in the project folder.

**Compile:**

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o students

# -Wall        Shows common warnings about possible mistakes
# -Wextra      Shows additional warnings
# -pedantic    Warns about extensions outside standard C++17
```

**Run on Linux or macOS:**

```bash
./students
```

## Using the program

1. Choose average or median.
2. Choose manual entering or file input.
3. For manual input, enter a first name and surname, then choose again manual or random marks.
4. Choose how to sort the results.

**Manual marks:** enter one whole number from `1` to `10` per line. At least five homework marks are required; enter `-1` when finished. You can enter more than five.

**Random marks:** the program generates five homework marks and one exam mark, all between `1` and `10`.

> Sorting by final grade uses the average or median selected at the start, including when both results are displayed for file input.

## File input

A file `Students.txt` is already placed in the folder from which you'll run the program. The filename is case-sensitive on Linux.

The first line is a header. Each following line contains a first name, surname, homework marks, and the exam mark **last**. Use spaces or tabs between values; each name must be a single word.

```text
Name    Surname    HW1 HW2 HW3 HW4 HW5 Exam
Anna    Smith      8   7   9   6   10  9
Ben     Jones      6   5   8   7   9   8
```

File input accepts one or more homework marks per student, followed by an exam mark. All marks must be whole numbers from `1` to `10`. An invalid student row stops file loading with an error message.

To try other test files, name one of them `Students.txt`.