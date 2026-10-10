#include "Person.h" // Makes the Person class and stream operators available.

#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>


int main()
{
    std::cout << "==== STUDENT GRADE CALCULATOR ====\n";

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

    if (source == 2)
    {
        std::ifstream file("Students.txt");

        if (!file.is_open())
        {
            std::cout << "Could not open Students.txt.\n";
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

    std::cout
        << '\n'
        << std::left
        << std::setw(20) << "Name"
        << std::setw(20) << "Surname";

    if (source == 2)
    {
        std::cout << std::setw(15) << "Final (Avg.)"
                  << "Final (Med.)\n";
    }
    else if (method == 1)
    {
        std::cout << "Final (Avg.)\n";
    }
    else
    {
        std::cout << "Final (Med.)\n";
    }

    // GO THROUGH ALL STORED STUDENTS AND PRINT EACH ONE
    /* like in javscript
            for (const student of students) {
                student.print();
            }
    */
    for (Person &student : students)
    {
        if (source == 2)
        {
            student.print(source == 2);
        }
        else
        {
            std::cout << student;
        }
    }

    return 0;
}