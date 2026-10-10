#include "Person.h"
#include <random>
#include <sstream>
#include <limits>
#include <algorithm> // Provides std::sort.
#include <iomanip>   // Provides setw, setprecision, and table formatting.

// Create student with the supplied names.
Person::Person(std::string name, std::string surname)
{
    firstName = name;
    surName = surname;
}

// Return surname without copying or modifying it.
const std::string &Person::getSurname() const
{
    return surName;
}

// Return first name without copying or modifying it.
const std::string &Person::getName() const
{
    return firstName;
}

// Return previously calculated, selected final grade.
double Person::getFinalGrade() const
{
    return finalGrade;
}

void Person::generateMarks(int count)
{
    // Create and seed the generator once; reuse it on later calls.
    static std::mt19937 generator(std::random_device{}());

    // Produce whole-number marks from 1 to 10.
    std::uniform_int_distribution<int> mark(1, 10);

    // Remove any previous homework marks before generating new ones.
    homeworkMarks.clear();

    for (int i = 0; i < count; ++i)
    {
        homeworkMarks.push_back(mark(generator));
    }

    // Generate a separate exam mark.
    examMark = mark(generator);
}

bool Person::readFromLine(const std::string &line)
{
    // Read from the supplied text as an input stream.
    std::istringstream input(line);

    // The first two words must be the student's names.
    if (!(input >> firstName >> surName))
        return false;

    homeworkMarks.clear();

    std::string entry;

    // Read each remaining whitespace-separated value.
    while (input >> entry)
    {
        std::istringstream markInput(entry);
        int mark;
        char extra;

        // Reject values that cannot be read as an integer.
        if (!(markInput >> mark))
            return false;

        // Reject extra characters: "9.5" reads 9, then finds '.'.
        if (markInput >> extra)
            return false;

        if (mark < 1 || mark > 10)
            return false;

        homeworkMarks.push_back(mark);
    }

    // Require at least one homework mark and one exam mark.
    if (homeworkMarks.size() < 2)
        return false;

    // The file places the exam mark last.
    examMark = homeworkMarks.back();

    // Remove it from homework so it isn't counted there as well.
    homeworkMarks.pop_back();

    // The student's row was successfully read and validated.
    return true;
}

bool Person::read()
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

bool Person::calculate(int method)
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

void Person::print(bool showBoth, std::ostream &output) const
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
            input.setstate(std::ios::failbit); // MARKS THE INPUT AS FAILED IF THAT METHOD REJECTS THE ROW - if this sutdent row was invalid
        }
    }

    return input;
}
