cmake_minimum_required(VERSION 3.5)
project(company)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
add_definitions(-DSQLITE_HAS_CODEC)
set(company_files
    ${sqlitencypt_source_dir}/examples/company.cpp)
include_directories(${sqlitencypt_source_dir}/src)
add_executable(company ${company_files})
target_link_libraries(company sqlitencypt)
