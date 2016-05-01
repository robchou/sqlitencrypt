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


#ifndef _SQLITETABLE_H
#define _SQLITETABLE_H

#include <string>
#include <vector>
#include <memory>

#include "sqlite_record.h"

class SQLiteTable {
    public:
        SQLiteTable();

        ~SQLiteTable();

        const std::string& table_name() const;

        /**
         * @param table_name
         */
        void set_table_name(const std::string& table_name);

        /**
         * @param column_name
         * @param flag including data type and constraint as std::string
         */
        void AddColumn(const std::string& column_name, const std::string& flag);

        const std::string ColumnsAsSQLCreateString() const;

        const std::string RecordsAsSQLQueryString();

        void AddRecord(std::shared_ptr<SQLiteRecord> record);

        const std::shared_ptr<SQLiteRecord> GetNextRecord();

        void ClearRecords();

        size_t GetRecordCount() const;

    private:
        std::string table_name_;
        size_t records_pos_;
        std::vector<std::string> columns_;
        std::vector<std::shared_ptr<SQLiteRecord>> records_;
};

#endif  // _SQLITETABLE_H
