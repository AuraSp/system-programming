cmake_minimum_required(VERSION 3.16)

project(StudentGradeCalculator LANGUAGES CXX)

# C++17 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Vector version: source files in the main folder
add_executable(students-vector
    main.cpp
    Person.cpp
    FileGenerator.cpp
    ResultsWriter.cpp
)

# List version
add_executable(students-list
    list/main.cpp
    list/Person.cpp
    list/FileGenerator.cpp
    list/ResultsWriter.cpp
)

# Deque version
add_executable(students-deque
    deque/main.cpp
    deque/Person.cpp
    deque/FileGenerator.cpp
    deque/ResultsWriter.cpp
)

# Compiler warnings
foreach(target students-vector students-list students-deque)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic)
    endif()
endforeach()