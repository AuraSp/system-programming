#include "FileGenerator.h"

#include <fstream>
#include <random>

bool generateStudentFile(
    const std::string &filename,
    int studentCount,
    int homeworkCount)
{
    if (studentCount <= 0 || homeworkCount <= 0)
        return false;

    // Open the output file. An existing file with this name is replaced.
    std::ofstream output(filename);

    if (!output)
        return false;

    // Create the generator once and reuse it.
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> mark(1, 10);

    // Write the column headings.
    output << "FirstName Surname";

    for (int j = 1; j <= homeworkCount; ++j)
        output << " HW" << j;

    output << " Exam\n";

    // Write one student per row.
    for (int i = 1; i <= studentCount; ++i)
    {
        output << "Name" << i << " Surname" << i;

        for (int j = 0; j < homeworkCount; ++j)
            output << ' ' << mark(generator);

        // The last mark in each row is the exam mark.
        output << ' ' << mark(generator) << '\n';

        if (!output)
            return false;
    }

    // Finish writing buffered data, then check whether writing succeeded.
    output.close();
    return static_cast<bool>(output);
}