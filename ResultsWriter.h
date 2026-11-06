#ifndef RESULTS_WRITER_H
#define RESULTS_WRITER_H

#include "Person.h"
#include <string>
#include <list>

bool writeResults(
    const std::string &filename,
    const std::vector<Person> &students,
    int method);

#endif