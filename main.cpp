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
        std::cout << "Student: " << firstName << ' ' << surName << "\n";
        std::cout << "Final grade: " << finalGrade << "\n";
    }
};

int main()
{
    std::cout << "==== STUDENT GRADE CALCULATOR ====\n";

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