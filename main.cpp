#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <random>

class Person
{
private:
    std::string firstName;
    std::string surName;
    int examMark = 0;
    std::vector<int> homeworkMarks;
    double finalGrade = 0.0;
    double finalAverage = 0.0;
    double finalMedian = 0.0;

public:
    //====== CONSTRUCTOR ======//
    Person() = default; // ALLOW CREATING STUDENT WITHOUT GIVING INFO

    Person(std::string name, std::string surname)
    {
        firstName = name;
        surName = surname;
    }

    Person(const Person &other) = default; // CREATE STUDENT BY COPYING ANOTHER

    //====== COPY ASSIGNMENT ======//
    Person &operator=(const Person &other) = default; // replace student's info with a copy of another student's info

    //====== DESTRUCTOR ======//
    ~Person() = default; // AUTOMATIC CLEANUP WHEN STUDENT OBJECT IS DESTROYED

    /*
    Inside each input loop iteration:

    Person student;              // 1. Create a local student.
    student.read();              // 2. Fill it with names and marks.
    student.calculate(method);   // 3. Calculate the result.
    students.push_back(student); // 4. Store a separate copy in the vector.

    At this exact point, two student objects exist: the local student and its stored copy. When we reach the loop’s closing `}`, the local student’s lifetime ends. C++ automatically calls its destructor --> ~Person() = default . Now they clean up their storage, yet the stored copy remains untouched. MEMORY SAVING WHEN NO LONGER NEED.

    When main() ends, the students vector and its stored students
    are also destroyed.

    C++ already provided a destructor before we wrote this line.
    "= default" specifically asking C++ to keep its automatic cleanup.
    */

    //====== METHODS ======//
    const std::string &getSurname() const
    {
        return surName;
    }

    const std::string &getName() const
    {
        return firstName;
    }

    double getFinalGrade() const
    {
        return finalGrade;
    }

    void generateMarks(int count)
    {

        static std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<int> mark(1, 10);

        homeworkMarks.clear();

        for (int i = 0; i < count; ++i)
        {
            homeworkMarks.push_back(mark(generator));
        }

        examMark = mark(generator);
    }

    bool readFromLine(const std::string &line)
    {
        std::istringstream input(line);

        if (!(input >> firstName >> surName))
            return false;

        homeworkMarks.clear();

        std::string entry;

        while (input >> entry)
        {
            std::istringstream markInput(entry);
            int mark;
            char extra;

            if (!(markInput >> mark))
                return false;

            if (markInput >> extra)
                return false;

            if (mark < 1 || mark > 10)
                return false;

            homeworkMarks.push_back(mark);
        }

        if (homeworkMarks.size() < 2) // AT LEAST ONE HOMEWORK MARK AND ONE EXAM MARK
            return false;

        examMark = homeworkMarks.back();
        homeworkMarks.pop_back();

        return true;
    }

    bool read()
    {
        int homeworkMark; // temporary variable for receiving entered marks

        std::cout << "First name: ";
        std::cin >> firstName;
        std::cout << "Last name: ";
        std::cin >> surName;

        // char randomChoice;

        // std::cout << "Generate random marks? (y/n): ";
        // if (!(std::cin >> randomChoice))
        //     return false;

        // if (randomChoice == 'y')
        // {
        //     generateMarks(5);
        //     return true;
        // }

        // if (randomChoice != 'n')
        // {
        //     std::cout << "Invalid choice. Enter y or n.\n";
        //     return false;
        // }

        // std::cin.ignore(
        //     std::numeric_limits<std::streamsize>::max(), '\n');

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        std::string randomChoice;

        while (true)
        {
            std::cout << "Generate random marks? (y/n): ";

            if (!std::getline(std::cin, randomChoice))
                return false;

            if (randomChoice == "y" || randomChoice == "Y" ||
                randomChoice == "n" || randomChoice == "N")
            {
                break;
            }

            std::cout << "Please enter y or n.\n";
        }

        if (randomChoice == "y" || randomChoice == "Y")
        {
            generateMarks(5);
            return true;
        }

        while (true)
        {
            std::cout << "Exam mark (1-10): ";

            // CHECKS IF READING NUMBER FAILED
            std::string line;

            if (!std::getline(std::cin, line))
                return false;

            std::istringstream input(line);
            char extra;

            if (!(input >> examMark))
            {
                std::cout << "Please enter a whole number.\n";
                continue;
            }

            if (input >> extra)
            {
                std::cout << "Please enter only one whole number per line.\n";
                continue;
            }

            if (examMark < 1 || examMark > 10)
            {
                std::cout << "The mark must be between 1 and 10.\n";
                continue;
            }

            break;
        }
        const int minimumHomeworkCount = 5;

        while (true)
        {
            std::cout << "Homework mark (1-10, or -1 to finish): ";

            std::string line;

            if (!std::getline(std::cin, line))
                return false;

            std::istringstream input(line);
            char extra;

            if (!(input >> homeworkMark))
            {
                std::cout << "Please enter a whole number.\n";
                continue;
            }

            if (input >> extra)
            {
                std::cout << "Please enter only one whole number per line.\n";
                continue;
            }

            if (homeworkMark == -1)
            {
                if (homeworkMarks.size() < minimumHomeworkCount)
                {
                    std::cout << "At least " << minimumHomeworkCount
                              << " homework marks are required.\n";

                    std::cout << "You have entered " << homeworkMarks.size()
                              << ". Please enter " << minimumHomeworkCount - homeworkMarks.size() << " more.\n";

                    continue;
                }

                break;
            }

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

        finalAverage = homeworkAverage * 0.4 + examMark * 0.6;
        finalMedian = homeworkMedian * 0.4 + examMark * 0.6;

        if (method == 1)
        {
            finalGrade = finalAverage;
        }
        else if (method == 2)
        {
            finalGrade = finalMedian;
        }
        else
        {
            std::cout << "Invalid choice.\n";
            return false;
        }

        // IF SUCCEEDED - TELL THE MAIN() AND STORE GRADE IN FINAL
        return true;
    }

    void print(bool showBoth, std::ostream &output = std::cout) const
    // ostream& output receive outoput destination and use temrinal if none is provided. Const - printing won't change this student
    {
        output << std::left
               << std::setw(20) << firstName
               << std::setw(20) << surName
               << std::fixed << std::setprecision(2);

        if (showBoth)
        {
            output << std::setw(15)
                   << finalAverage << finalMedian << '\n';
        }
        else
        {
            output << finalGrade << '\n';
        }
    }
};

// DEFINE HOW TO PRINT A PERSON USING <<
std::ostream &operator<<(std::ostream &output, const Person &student)
// print student without changing it
{
    student.print(false, output);
    return output;
}

std::istream &operator>>(std::istream &input, Person &student)
{
    std::string line;

    if (std::getline(input, line))
    // one row
    {
        if (!student.readFromLine(line))
        // separate this row into names and marks
        {
            input.setstate(std::ios::failbit); // MARKS THE INPUT AS FAILED IF THAT METHOD REJECTS THE ROW
        }
    }

    return input;
}

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