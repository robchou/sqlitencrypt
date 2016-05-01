cmake_minimum_required(VERSION 3.5)
project(sqlitencypt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(sqlitencypt_source_dir ${PROJECT_SOURCE_DIR})
set(libsqlitencrypt_files
${sqlitencypt_source_dir}/src/content_values.cpp
${sqlitencypt_source_dir}/src/sqlite_db.cpp
${sqlitencypt_source_dir}/src/sqlite_record.cpp
${sqlitencypt_source_dir}/src/sqlite_table.cpp
${sqlitencypt_source_dir}/src/utils.cpp
${sqlitencypt_source_dir}/wxsqlite3/sqlite3/secure/src/sqlite3secure.c)

add_definitions(-DSQLITE_HAS_CODEC)
include_directories(${sqlitencypt_source_dir}/include)
add_library(sqlitencypt ${libsqlitencrypt_files})
target_link_libraries(sqlitencypt pthread dl)

add_subdirectory(examples)
