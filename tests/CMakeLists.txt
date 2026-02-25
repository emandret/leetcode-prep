include_directories(${leetcode_SOURCE_DIR}/include)

file(GLOB SOURCES "*.cpp")

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.8.1)

FetchContent_MakeAvailable(Catch2)

add_executable(tests ${SOURCES})
target_link_libraries(tests PRIVATE solutions Catch2::Catch2WithMain)

set_property(TARGET tests PROPERTY CXX_STANDARD 17)
set_property(TARGET tests PROPERTY CXX_STANDARD_REQUIRED ON)
