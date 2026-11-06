#ifndef RESULTS_WRITER_H
#define RESULTS_WRITER_H

#include "Person.h"
#include <string>
#include <deque>

bool writeResults(
    const std::string &filename,
    const std::deque<Person> &students,
    int method);

#endif