#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H

#include <string>

// Create a file containing student names, homework marks, and exam marks.
// Return true if the file was successfully written.
bool generateStudentFile(
    const std::string &filename,
    int studentCount,
    int homeworkCount = 5);

#endif