include_directories(${leetcode_SOURCE_DIR}/include)

file(GLOB SOURCES "*.cpp")

add_library(solutions ${SOURCES})

set_property(TARGET solutions PROPERTY CXX_STANDARD 17)
set_property(TARGET solutions PROPERTY CXX_STANDARD_REQUIRED ON)
