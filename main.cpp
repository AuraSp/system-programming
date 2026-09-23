#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <cstdlib> // rand() and srand()
#include <ctime>   // time()

class Person
{
private:
    std::string firstName;
    std::string surName;
    int examMark = 0;
    std::vector<int> homeworkMarks;
    double finalGrade = 0.0;

public:
    //====== METHODS ======//
    const std::string &getSurname() const
    {
        return surName;
    }

    void generateMarks(int count)
    {
        homeworkMarks.clear();

        for (int i = 0; i < count; ++i)
        {
            int mark = std::rand() % 10 + 1;
            homeworkMarks.push_back(mark);
        }

        examMark = std::rand() % 10 + 1;
    }

    bool read()
    {
        int homeworkMark; // temporary variable for receiving entered marks

        std::cout << "First name: ";
        std::cin >> firstName;
        std::cout << "Last name: ";
        std::cin >> surName;

        char randomChoice;

        std::cout << "Generate random marks? (y/n): ";
        if (!(std::cin >> randomChoice))
            return false;

        if (randomChoice == 'y')
        {
            generateMarks(5);
            return true;
        }

        if (randomChoice != 'n')
        {
            std::cout << "Invalid choice. Enter y or n.\n";
            return false;
        }

        while (true)
        {
            std::cout << "Exam mark (1-10): ";

            // CHECKS IF READING NUMBER FAILED
            if (!(std::cin >> examMark))
            {
                if (std::cin.eof() || std::cin.bad()) // IF INPUT ENDED OR SOMETHING HAPPENED WHILE READING IT - STOP THIS METHOD
                    return false;

                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'); // reset the error -> discard the wrong entry -> ask again

                std::cout << "Please enter a whole number.\n";
                continue;
            }

            if (examMark < 1 || examMark > 10)
            {
                std::cout << "The mark must be between 1 and 10.\n";
                continue;
            }

            break;
        }

        while (true)
        {
            std::cout << "Homework mark (1-10, or -1 to finish): ";

            if (!(std::cin >> homeworkMark))
            {
                if (std::cin.eof() || std::cin.bad())
                    return false;

                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Please enter a whole number.\n";
                continue;
            }

            if (homeworkMark == -1)
                break;

            if (homeworkMark < 1 || homeworkMark > 10)
            {
                std::cout << "The mark must be between 1 and 10.\n";
                continue;
            }

            homeworkMarks.push_back(homeworkMark);
        }

        if (homeworkMarks.empty())
        {
            std::cout << "No homework marks entered. Cannot calculate a grade.\n";
            return false;
        }

        return true;
    }

    bool calculate(int method)
    {
        double homeworkSum = 0.0;
        double homeworkAverage = 0.0;
        double homeworkMedian = 0.0;

        // GO THROUGH EACH HOMEWORK MARKS AT A TIME
        for (int mark : homeworkMarks)
            homeworkSum += mark; // ADD MARK TO THE TOTAL
        homeworkAverage = homeworkSum / homeworkMarks.size();

        std::sort(homeworkMarks.begin(), homeworkMarks.end()); // FROM SMALLEST TO LARGEST MARKS
        auto middleIndex = homeworkMarks.size() / 2;           // FIND MIDDLE MARK FROM ALL MARKS.LENGTH()

        if (homeworkMarks.size() % 2 != 0)
        {
            homeworkMedian = homeworkMarks[middleIndex]; // GET THAT MIDDLE MARK FROM MIDDLE POSITION AFTER USING .SIZE()
        }
        else
        {
            homeworkMedian = (homeworkMarks[middleIndex - 1] + homeworkMarks[middleIndex]) / 2.0;
        }

        if (method == 1)
        {
            finalGrade = (homeworkAverage * 0.4) + (examMark * 0.6);
        }
        else if (method == 2)
        {
            finalGrade = (homeworkMedian * 0.4) + (examMark * 0.6);
        }
        else
        {
            std::cout << "Invalid choice.\n";
            return false;
        }

        // IF SUCCEEDED - TELL THE MAIN() AND STORE GRADE IN FINAL
        return true;
    }

    void print()
    {
        std::cout << std::left
                  << std::setw(20) << firstName
                  << std::setw(20) << surName
                  << std::fixed << std::setprecision(2)
                  << finalGrade << '\n';
    }
};

int main()
{
    std::cout << "==== STUDENT GRADE CALCULATOR ====\n";

    std::srand(std::time(nullptr));
    std::vector<Person> students;

    int method = 0;
    std::cout << "Calculate using: 1 - average, 2 - median: ";
    std::cin >> method;

    char another = 'y';

    while (another == 'y')
    {
        // CREATE FRESH STUDENT FOR THIS INPUT
        Person student;

        // IF INPUT METHOD READS FAILURE - IT ENDS THE PROGRAM
        if (!student.read())
        {
            return 1;
        }

        // IF WRONG INPUT CHOICE OR FAILS TO RUN THE METHOD - RETURNS FALSE
        if (!student.calculate(method))
        {
            // REPORTS AN ERROR AND ENDS THE PROGRAM
            return 1;
        }

        // DO A COPY AND STORE IT FOR 'THIS' STUDENT, INCLUDING HIS MARKS AND RESULT
        students.push_back(student);

        std::cout << "Add another student? (y/n): ";
        std::cin >> another;
    }

    std::sort(students.begin(), students.end(),
              // LAMBDA FUNCTION - Should student 'a' come before student 'b'?
              [](const Person &a, const Person &b)
              {
                  return a.getSurname() < b.getSurname();
              });

    std::cout
        << '\n'
        << std::left
        << std::setw(20) << "Name"
        << std::setw(20) << "Surname";

    if (method == 1)
        std::cout << "Final (Avg.)\n";
    else
        std::cout << "Final (Med.)\n";

    // GO THROUGH ALL STORED STUDENTS AND PRINT EACH ONE
    /* like in javscript
            for (const student of students) {
                student.print();
            }
    */
    for (Person &student : students)
    {
        student.print();
    }

    return 0;
}