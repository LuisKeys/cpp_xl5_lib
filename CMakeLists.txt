project(cpp_xl_lib)

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(sources src/main.cpp src/XLLog.cpp src/XLSort.cpp src/XLSummary.cpp )

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

include_directories(/usr/include)

link_directories(/usr/lib)
link_directories(/usr/local/lib)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

add_executable(cpp_xl_lib ${sources})

target_link_libraries(cpp_xl_lib)