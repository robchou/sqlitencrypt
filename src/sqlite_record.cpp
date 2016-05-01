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

#include <string>
#include <map>

#include "sqlitencrypt/sqlite_record.h"
#include "sqlitencrypt/log.h"

using std::string;
using std::map;

SQLiteRecord::SQLiteRecord() { }

SQLiteRecord::~SQLiteRecord() { }

void SQLiteRecord::SetColumnValue(const string& key, const string& value) {
    if (key.length()) {
        fields_[key] = value;
    } else {
        LOGE("%s", "Column name is NULL");
    }
}

/**
 * @param column_name
 * @return bool
 */
bool SQLiteRecord::GetBool(const string& column_name) {
    return std::stoi(fields_[column_name]);
}

/**
 * @param column_name
 * @return int32_t
 */
int32_t SQLiteRecord::GetInt32(const string& column_name) {
    return std::stoi(fields_[column_name]);
}

/**
 * @param column_name
 * @return int64_t
 */
int64_t SQLiteRecord::GetInt64(const string& column_name) {
    return std::stoll(fields_[column_name]);
}

/**
 * @param column_name
 * @return double
 */
double SQLiteRecord::GetDouble(const string& column_name) {
    return std::stod(fields_[column_name]);
}

/**
 * @param column_name
 * @return const string
 */
const string SQLiteRecord::GetText(const string& column_name) {
    return fields_[column_name];
}

/**
 * @return const string
 */
const string SQLiteRecord::RecordAsSQLQueryResultString() const {
    if (fields_.size() == 0) {
        return "";
    }
    string record;
    map<string, string>::const_iterator it;
    for (it = fields_.cbegin(); it != fields_.cend(); ++it) {
        record += it->second;
        record += "|";
    }

    record = record.substr(0, record.length() - 1);

    return record;
}

/**
 * @return const string
 */
const string SQLiteRecord::ColumnNamesAsSQLQueryResultString() const {
    if (fields_.size() == 0) {
        return "";
    }

    string column_names;
    map<string, string>::const_iterator it;
    for (it = fields_.cbegin(); it != fields_.cend(); ++it) {
        column_names += it->second + "|";
    }

    column_names = column_names.substr(0, column_names.length() - 1);

    return column_names;
}

/**
 * @return size_t
 */
size_t SQLiteRecord::GetColumnsCount() const {
    return fields_.size();
}

