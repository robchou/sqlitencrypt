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

#include "sqlite_table.h"
#include "log.h"


SQLiteTable::SQLiteTable(): table_name_(""), records_pos_(0) { }

SQLiteTable::~SQLiteTable() { }


/**
 * @return const string
 */
const string& SQLiteTable::table_name() const {
    return table_name_;
}

/**
 * @param table_name
 * @return void
 */
void SQLiteTable::set_table_name(const string& table_name) {
    table_name_ = table_name;
}

/**
 * @param column_name
 * @param flag
 * @return void
 */
void SQLiteTable::AddColumn(const string& column_name, const string& flag) {
    columns_.push_back(column_name + " " + flag + ", ");
}

/**
 * @return const string
 */
const string SQLiteTable::ColumnsAsSQLCreateString() const {
    if (columns_.size() == 0) {
        LOGE("No column names");
        return "";
    }

    string columns;
    vector<string>::const_iterator it;

    for (it = columns_.cbegin(); it != columns_.cend(); ++it) {
        columns += *it;
    }
    columns = columns.substr(0, columns.length() - 2);

    return columns;
}

/**
 * @return const string
 */
const string SQLiteTable::RecordsAsSQLQueryString() {
    if (records_.size() == 0) {
        return "No record found";
    }

    string query_result;
    string records;
    shared_ptr<SQLiteRecord> record;
    while ((record = GetNextRecord())) {
        records += record->RecordAsSQLQueryResultString() + "\n";
    }

    // Headers
    query_result = "\n" + records_[0]->ColumnNamesAsSQLQueryResultString() + "\n";
    // Values in a record
    query_result += records;

    return query_result;
}

/**
 * @return const shared_ptr<SQLiteRecord>
 */
const shared_ptr<SQLiteRecord> SQLiteTable::GetNextRecord() {
    if (records_pos_ < records_.size()) {
        return records_[records_pos_++];
    }

    return nullptr;
}

void SQLiteTable::AddRecord(shared_ptr<SQLiteRecord> record) {
    records_.push_back(record);
}


/**
 * @return void
 */
void SQLiteTable::ClearRecords() {
    records_.clear();
    records_pos_ = 0;
}

/**
 * @return size_t
 */
size_t SQLiteTable::GetRecordCount() const {
    return records_.size();
}

