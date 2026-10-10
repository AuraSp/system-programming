#include "ResultsWriter.h"

#include <fstream>
#include <iomanip>

bool writeResults(
    const std::string &filename,
    const std::vector<Person> &students,
    int method)
{
    std::ofstream output(filename);

    if (!output)
        return false;

    // Label the final grade using the selected calculation method.
    output << std::left
           << std::setw(20) << "First name"
           << std::setw(20) << "Surname"
           << (method == 1 ? "Final (average)" : "Final (median)")
           << '\n';

    for (const Person &student : students)
    {
        output << student;

        if (!output)
            return false;
    }

    output.close();
    return static_cast<bool>(output);
}