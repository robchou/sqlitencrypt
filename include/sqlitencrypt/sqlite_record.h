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

#ifndef _SQLITERECORD_H
#define _SQLITERECORD_H

#include <string>
#include <map>
#include <cstdint>

class SQLiteRecord {
    // TODO(robin): process NULL value
    public:
        SQLiteRecord();

        ~SQLiteRecord();

        void SetColumnValue(const std::string& key, const std::string& value);

        /**
         * @param column_name
         */
        bool GetBool(const std::string& column_name);

        /**
         * @param column_name
         */
        int32_t GetInt32(const std::string& column_name);

        /**
         * @param column_name
         */
        int64_t GetInt64(const std::string& column_name);

        /**
         * @param column_name
         */
        double GetDouble(const std::string& column_name);

        /**
         * @param column_name
         */
        const std::string GetText(const std::string& column_name);

        const std::string RecordAsSQLQueryResultString() const;

        const std::string ColumnNamesAsSQLQueryResultString() const;

        size_t GetColumnsCount() const;

    private:
        std::map<std::string, std::string> fields_;
};

#endif  // _SQLITERECORD_H
