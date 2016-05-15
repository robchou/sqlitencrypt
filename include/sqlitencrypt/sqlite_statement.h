/*
 * Copyright (C) 2016, Robin Chou (robin.m.chou@gmail.com)
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SQLITE_STATEMENT_H
#define SQLITE_STATEMENT_H

#include <string>
#include <sqlite3.h>

using std::string;

class SQLiteStatement
{
public:
    SQLiteStatement(sqlite3* sqlite3_handler, const string& stmt);
    virtual ~SQLiteStatement();
    int bind(const int index, const bool& value);
    int bind(const int index, const int32_t& value);
    int bind(const int index, const int64_t& value);
    int bind(const int index, const double& value);
    int bind(const int index, const string& value);
    int bind(const int index, const char* value);
    int bind(const int index, const void* value, const int size);
    int bind(const int index);

private:
    sqlite3_stmt* stmt_;
};

#endif /* SQLITE_STATEMENT_H */
