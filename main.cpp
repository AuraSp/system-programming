#include "Person.h" // Makes the Person class and stream operators available.
#include "FileGenerator.h"
#include "ResultsWriter.h"

#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>     // For measuring elpsed time
#include <filesystem> // Allows us to find files in a folder.

int main()
{
    std::cout << "==== STUDENT GRADE CALCULATOR ====\n";

    std::string action;

    while (true)
    {
        std::cout << "1 - Calculate student grades\n"
                  << "2 - Generate a student file\n"
                  << "Choose: ";

        if (!std::getline(std::cin, action))
            return 1;

        if (action == "1" || action == "2")
            break;

        std::cout << "Please enter 1 or 2.\n";
    }

    if (action == "2")
    {
        const int sizes[] = {1000, 10000, 100000, 1000000, 10000000};
        int sizeChoice = 0;

        while (true)
        {
            std::cout << "How many students?\n"
                      << "1 - 1,000\n"
                      << "2 - 10,000\n"
                      << "3 - 100,000\n"
                      << "4 - 1,000,000\n"
                      << "5 - 10,000,000\n"
                      << "Choose: ";

            std::string line;
            if (!std::getline(std::cin, line))
                return 1;

            std::istringstream input(line);
            char extra;

            if (!(input >> sizeChoice) || (input >> extra) ||
                sizeChoice < 1 || sizeChoice > 5)
            {
                std::cout << "Please enter one whole number from 1 to 5.\n";
                continue;
            }

            break;
        }

        // Menu choices start at 1, but array indexes start at 0.
        int studentCount = sizes[sizeChoice - 1];

        std::string filename =
            "students-" + std::to_string(studentCount) + ".txt";

        std::cout << "Generating " << filename << "...\n";

        if (!generateStudentFile(filename, studentCount))
        {
            std::cerr << "Could not generate " << filename << ".\n";
            return 1;
        }

        std::cout << "Created " << filename << " with "
                  << studentCount << " students.\n";

        return 0;
    }

    std::vector<Person> students;

    int method = 0;

    while (true)
    {
        std::cout << "Calculate using: 1 - average, 2 - median: ";
        std::string line;

        if (!std::getline(std::cin, line))
            return 1;

        std::istringstream input(line);
        char extra;

        if (!(input >> method))
        {
            std::cout << "Please enter one whole number.\n";
            continue;
        }

        if (input >> extra)
        {
            std::cout << "Please enter only one whole number.\n";
            continue;
        }

        if (method != 1 && method != 2)
        {
            std::cout << "Choose 1 for average or 2 for median.\n";
            continue;
        }

        /*
        f -> cannot read as a number -> asking again
        1.5 -> reads 1, then finds extra `.` -> rejecting
        1 2 -> reads 1, then finds extra `2` after space -> rejecting
        0 -> valid integers, but not valid choice -> rejecting
        1 or 2 alone -> accepted choices
        */

        break;
    }

    int source = 0;

    while (true)
    {
        std::cout << "Read students: 1 - manual entering, 2 - file: ";

        std::string line;

        if (!std::getline(std::cin, line))
            return 1;

        std::istringstream input(line);
        char extra;

        if (!(input >> source))
        {
            std::cout << "Please enter a whole number.\n";
            continue;
        }

        if (input >> extra)
        {
            std::cout << "Please enter only one whole number.\n";
            continue;
        }

        if (source != 1 && source != 2)
        {
            std::cout << "Choose 1 for manual entering or 2 for file.\n";
            continue;
        }

        break;
    }

    double readSeconds = 0.0;

    if (source == 2)
    {
        std::string filename;
        std::vector<std::string> availableFiles;

        // Find .txt files in the folder the program is running from.
        try
        {
            for (const auto &entry : std::filesystem::directory_iterator("."))
            {
                if (!entry.is_regular_file())
                    continue;

                if (entry.path().extension() != ".txt")
                    continue;

                std::string name = entry.path().filename().string();

                // These contain results, not the original student marks.
                if (name == "passed.txt" || name == "failed.txt")
                    continue;

                availableFiles.push_back(name);
            }
        }
        catch (const std::filesystem::filesystem_error &)
        {
            availableFiles.clear();
            std::cout << "Could not list files. Use 0 to enter a filename manually.\n";
        }

        // Keep the displayed order consistent.
        std::sort(availableFiles.begin(), availableFiles.end());

        std::cout << "\nAvailable student files:\n";

        if (availableFiles.empty())
            std::cout << "No available .txt files found.\n";

        for (std::size_t i = 0; i < availableFiles.size(); ++i)
        {
            std::cout << i + 1 << ". " << availableFiles[i] << '\n';
        }

        std::cout << "0. Enter another filename or path\n";

        while (true)
        {
            std::cout << "Choose a file: ";

            std::string line;
            if (!std::getline(std::cin, line))
                return 1;

            std::istringstream input(line);
            int choice;
            char extra;

            if (!(input >> choice) || (input >> extra) ||
                choice < 0 ||
                static_cast<std::size_t>(choice) > availableFiles.size())
            {
                std::cout << "Enter one whole number from 0 to "
                          << availableFiles.size() << ".\n";
                continue;
            }

            if (choice == 0)
            {
                std::cout << "Enter the filename or path: ";

                if (!std::getline(std::cin, filename))
                    return 1;
            }
            else
            {
                // Menu numbers start at 1; vector indexes start at 0.
                filename = availableFiles[choice - 1];
            }

            break;
        }
        auto readStart = std::chrono::steady_clock::now();

        std::ifstream file(filename);

        if (!file)
        {
            std::cerr << "Could not open " << filename << ".\n";
            return 1;
        }

        std::string line;

        std::getline(file, line);

        while (std::getline(file, line))
        {
            Person student;

            std::istringstream row(line);

            if (!(row >> student))
            {
                std::cout << "Invalid student row.\n";
                return 1;
            }

            if (!student.calculate(method))
                return 1;

            students.push_back(student);
        }

        if (file.bad())
        {
            std::cerr << "An error occurred while reading the file.\n";
            return 1;
        }

        if (students.empty())
        {
            std::cerr << "The file contains no student records.\n";
            return 1;
        }

        file.close();

        auto readEnd = std::chrono::steady_clock::now();

        readSeconds =
            std::chrono::duration<double>(readEnd - readStart).count();
    }
    else if (source == 1)
    {
        std::string another = "y";

        while (another == "y" || another == "Y")
        {
            Person student;

            if (!student.read())
                return 1;

            if (!student.calculate(method))
                return 1;

            students.push_back(student);

            while (true)
            {
                std::cout << "Add another student? (y/n): ";

                if (!std::getline(std::cin, another))
                    return 1;

                if (another == "y" || another == "Y" ||
                    another == "n" || another == "N")
                {
                    break;
                }

                std::cout << "Please enter y or n.\n";
            }
        }
    }
    else
    {
        std::cout << "Invalid choice.\n";
        return 1;
    }

    int sortChoice = 0;

    std::cout << "\nSort students by:\n"
              << "1. Name A-Z\n"
              << "2. Name Z-A\n"
              << "3. Final grade: lowest first\n"
              << "4. Final grade: highest first\n"
              << "Grade sorting uses your selected average/median method.\n";

    while (true)
    {
        std::cout << "Choice: ";

        std::string line;

        if (!std::getline(std::cin, line))
            return 1;

        std::istringstream input(line);
        char extra;

        if (!(input >> sortChoice))
        {
            std::cout << "Please enter a whole number.\n";
            continue;
        }

        if (input >> extra)
        {
            std::cout << "Please enter only one whole number.\n";
            continue;
        }

        if (sortChoice < 1 || sortChoice > 4)
        {
            std::cout << "Choose a number from 1 to 4.\n";
            continue;
        }

        break;
    }

    auto sortStart = std::chrono::steady_clock::now();

    switch (sortChoice)
    {
    case 1:
        std::sort(students.begin(), students.end(),
                  [](const Person &a, const Person &b)
                  {
                      return a.getName() < b.getName();
                  });
        break;

    case 2:
        std::sort(students.begin(), students.end(),
                  [](const Person &a, const Person &b)
                  {
                      return a.getName() > b.getName();
                  });
        break;

    case 3:
        std::sort(students.begin(), students.end(),
                  [](const Person &a, const Person &b)
                  {
                      return a.getFinalGrade() < b.getFinalGrade();
                  });
        break;

    case 4:
        std::sort(students.begin(), students.end(),
                  [](const Person &a, const Person &b)
                  {
                      return a.getFinalGrade() > b.getFinalGrade();
                  });
        break;

    default:
        std::cout << "f choice. Enter 1-4.\n";
        return 1;
    }

    auto sortEnd = std::chrono::steady_clock::now();

    double sortSeconds =
        std::chrono::duration<double>(sortEnd - sortStart).count();

    auto splitStart = std::chrono::steady_clock::now();

    std::vector<Person> passed;
    std::vector<Person> failed;

    for (const Person &student : students)
    {
        if (student.getFinalGrade() < 5.0)
            failed.push_back(student);
        else
            passed.push_back(student);
    }

    auto splitEnd = std::chrono::steady_clock::now();

    double splitSeconds =
        std::chrono::duration<double>(splitEnd - splitStart).count();

    std::cout << "Passed: " << passed.size() << '\n';
    std::cout << "Failed: " << failed.size() << '\n';

    auto writeStart = std::chrono::steady_clock::now();

    if (!writeResults("passed.txt", passed, method))
    {
        std::cerr << "Could not write passed.txt.\n";
        return 1;
    }

    if (!writeResults("failed.txt", failed, method))
    {
        std::cerr << "Could not write failed.txt.\n";
        return 1;
    }

    auto writeEnd = std::chrono::steady_clock::now();

    double writeSeconds =
        std::chrono::duration<double>(writeEnd - writeStart).count();

    std::cout << "Results saved to passed.txt and failed.txt.\n";

    if (source == 2)
    {
        double totalSeconds =
            readSeconds + sortSeconds + splitSeconds + writeSeconds;

        std::cout << std::fixed << std::setprecision(6)
                  << "\nRead and calculate: " << readSeconds << " seconds\n"
                  << "Sort: " << sortSeconds << " seconds\n"
                  << "Split: " << splitSeconds << " seconds\n"
                  << "Write both files: " << writeSeconds << " seconds\n"
                  << "Total processing: " << totalSeconds << " seconds\n";
    }

    return 0;
}