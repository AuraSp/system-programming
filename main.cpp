#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{

    std::cout << "Student grade calculator\n";

    std::string firstName;
    std::string surName;
    int examMark;
    std::vector<int> homeworkMarks;
    int homeworkMark;

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
        return 0;
    }
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

    int method = 0;
    std::cout << "Calculate using: 1 - average, 2 - median: ";
    std::cin >> method;

    double finalGrade = 0.0;

    if(method == 1) {
        finalGrade = (homeworkAverage * 0.4) + (examMark * 0.6);
    }
    else if (method == 2)
    {
        finalGrade = (homeworkMedian * 0.4) + (examMark * 0.6);
    }
    else
    {
        std::cout << "Invalid choice.\n";
        return 1;
    }

    std::cout << "Student: " << firstName << ' ' << surName << "\n";
    std::cout << "Exam mark for this student: " << examMark << "\n";
    std::cout << "Homework marks stored: " << homeworkMarks.size() << "\n"; // like .length() in js
    std::cout << "Homework average: " << homeworkAverage << "\n";
    std::cout << "Final grade: " << finalGrade << "\n";
    return 0;
}