# Copyright (C) 2016, Robin Chou (robin.m.chou@gmail.com)
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
add_library(sqlitencypt SHARED ${libsqlitencrypt_files})
target_link_libraries(sqlitencypt pthread dl)

add_subdirectory(examples)
