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

#ifndef _SQLITEDB_H
#define _SQLITEDB_H

#include <string>
#include <vector>

#include <sqlite3.h>
#include "content_values.h"
#include "sqlite_table.h"

class SQLiteDB {
public:
    SQLiteDB();

    ~SQLiteDB();

    /**
     * @param db_path
     * @param db_name
     * @param password
     */
    int Open(const std::string& db_path, const std::string& db_name,
            const std::string& password = "");

    /**
     * @param sqlite_table
     */
    int Create(const SQLiteTable& sqlite_table);

    /**
     * @param table_name
     * @param columns
     */
    int Create(const std::string& table_name, const std::string& columns);

    /**
     * @param table_name
     * @param column_name
     * @param where_condition
     * @param result_table
     */
    int Query(const std::string& table_name, const std::string& column_name,
            const std::string& where_condition, SQLiteTable* result_table);

    /**
     * @param table_name
     * @param column_names
     * @param where_condition
     * @param result_table
     */
    int Query(const std::string& table_name, const std::vector<std::string>& column_names,
            const std::string& where_condition, SQLiteTable* result_table);

    /**
     * @param table_name
     * @param values
     */
    int Insert(const std::string& table_name, const ContentValues& values);

    /**
     * @param table_name
     * @param values
     * @param where_condition
     */
    int Update(const std::string& table_name, const ContentValues& values,
            const std::string& where_condition);

    /**
     * @param table_name
     * @param where_condition
     */
    int Delete(const std::string& table_name, const std::string& where_condition);

    /**
     * @param statement
     * @param result_table
     */
    int ExecSQL(const std::string& statement, SQLiteTable* result_table = nullptr);

    int Begin();

    int Commit();

    int RollBack();

    static const std::string SQLiteCodeAsString(int error_code);

    static int SelectCallback(void *data, int num_fields,
            char **fields, char **column_names);

private:
    sqlite3* sqlite3_handler_;
};

#endif  // _SQLITEDB_H
