project(cpp_xl5_lib)

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(sources main.cpp src/XL5Log src/XL5Sort src/XL5Summary src/XL5Test)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

include_directories(/usr/include)

link_directories(/usr/lib)
link_directories(/usr/local/lib)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_executable(cpp_xl5_lib ${sources})

target_link_libraries(cpp_xl5_lib)
