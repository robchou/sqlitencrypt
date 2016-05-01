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

#include "sqlitencrypt/content_values.h"
#include "sqlitencrypt/utils.h"

using std::string;
using std::map;
using std::make_pair;
using std::to_string;

ContentValues::ContentValues() { }

ContentValues::~ContentValues() { }

/**
 * @param key
 * @param value
 * @return void
 */
void ContentValues::PutBool(const string& key, const bool& value) {
    values_[key] = to_string(value);
}

/**
 * @param key
 * @param value
 * @return void
 */
void ContentValues::PutInt32(const string& key, const int32_t& value) {
    values_[key] = to_string(value);
}

/**
 * @param key
 * @param value
 * @return void
 */
void ContentValues::PutInt64(const string& key, const int64_t& value) {
    values_[key] = to_string(value);
}

/**
 * @param key
 * @param value
 * @return void
 */
void ContentValues::PutDouble(const string& key, const double& value) {
    values_[key] = to_string(value);
}

/**
 * @param key
 * @param value
 * @return void
 */
void ContentValues::PutText(const string& key, const string& value) {
    values_[key] = to_sql_text(value);
}

/**
 * @param key
 * @return void
 */
void ContentValues::PutNULL(const string& key) {
    values_[key] = "NULL";
}

/**
 * @return void
 */
void ContentValues::ClearValues() {
    values_.clear();
}

/**
 * @return size_t
 */
size_t ContentValues::GetValuesCount() const {
    return values_.size();
}

/**
 * @return const string
 */
const string ContentValues::ValuesAsSQLInsertString() const {
    string column_names;
    string values;
    map<string, string>::const_iterator it;
    for (it = values_.cbegin(); it != values_.cend(); ++it) {
        column_names += it->first + ", ";
        values += it->second + ", ";
    }
    column_names = column_names.substr(0, column_names.length() - 2);
    values = values.substr(0, values.length() - 2);

    return "(" + column_names + ")" + "VALUES" + "(" + values + ")";
}

/**
 * @return const string
 */
const string ContentValues::ValuesAsSQLUpdateString() const {
    string values;
    map<string, string>::const_iterator it;

    for (it = values_.cbegin(); it != values_.cend(); ++it) {
        values += it->first + " = " + it->second + ", ";
    }

    values = values.substr(0, values.length() - 2);

    return values;
}

