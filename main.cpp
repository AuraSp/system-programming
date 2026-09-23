#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    bool read()
    {
        int homeworkMark; // temporary variable for receiving entered marks

        std::cout << "First name: ";
        std::cin >> firstName;
        std::cout << "Last name: ";
        std::cin >> surName;

        std::cout << "Exam mark: ";
        std::cin >> examMark;

        std::cout << "Add homework marks (-1 to finish): ";
        while (std::cin >> homeworkMark)
        {
            if (homeworkMark == -1)
            {
                break;
            }
            // appends a copy of entered value to the end of the vector
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

        for (int mark : homeworkMarks)
        {
            homeworkSum += mark;
        }
        double homeworkAverage = 0.0;
        homeworkAverage = homeworkSum / homeworkMarks.size();

        std::sort(homeworkMarks.begin(), homeworkMarks.end());

        auto middleIndex = homeworkMarks.size() / 2;
        double homeworkMedian = 0.0;

        if (homeworkMarks.size() % 2 != 0)
        {
            homeworkMedian = homeworkMarks[middleIndex];
        }
        else
        {
            homeworkMedian =
                (homeworkMarks[middleIndex - 1] + homeworkMarks[middleIndex]) / 2.0;
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

        return true;
    }

    void print()
    {
        std::cout << "Student: " << firstName << ' ' << surName << "\n";
        std::cout << "Final grade: " << finalGrade << "\n";
    }
};

int main()
{

    std::cout << "Student grade calculator\n";

    Person student;

    if (!student.read())
    {
        return 1;
    }

    int method = 0;
    std::cout << "Calculate using: 1 - average, 2 - median: ";
    std::cin >> method;

    if (!student.calculate(method))
    {
        return 1;
    }

    student.print();

    return 0;
}