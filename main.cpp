#include <iostream>
#include <string>
#include <vector>

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
    double finalGrade = 0.0;
    finalGrade = (homeworkAverage * 0.4) + (examMark * 0.6);

    std::cout << "Student: " << firstName << ' ' << surName << "\n";
    std::cout << "Exam mark for this student: " << examMark << "\n";
    std::cout << "Homework marks stored: " << homeworkMarks.size() << "\n"; // like .length() in js
    std::cout << "Homework average: " << homeworkAverage << "\n";
    std::cout << "Final grade: " << finalGrade << "\n";
    return 0;
}