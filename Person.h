#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

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

    Person(std::string name, std::string surname);

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

    //====== GETTERS ======//
    const std::string &getSurname() const;
    const std::string &getName() const;
    double getFinalGrade() const;

    //====== METHODS ======//
    void generateMarks(int count);
    bool readFromLine(const std::string &line);
    bool read();
    bool calculate(int method);
    void print(bool showBoth, std::ostream &output = std::cout) const;
};

//====== STREAM OPERATORS ======//
std::ostream &operator<<(std::ostream &output, const Person &student);
std::istream &operator>>(std::istream &input, Person &student);

#endif