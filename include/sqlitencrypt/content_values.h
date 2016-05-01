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

#ifndef _CONTENTVALUES_H
#define _CONTENTVALUES_H

#include <string>
#include <map>

/**
 * @brief This class is a container of values in a row
 */
class ContentValues {
    public:
        ContentValues();

        ~ContentValues();

        /**
         * @param key
         * @param value
         */
        void PutBool(const std::string& key, const bool& value);

        /**
         * @param key
         * @param value
         */
        void PutInt32(const std::string& key, const int32_t& value);

        /**
         * @param key
         * @param value
         */
        void PutInt64(const std::string& key, const int64_t& value);

        /**
         * @param key
         * @param value
         */
        void PutDouble(const std::string& key, const double& value);

        /**
         * @param key
         * @param value
         */
        void PutText(const std::string& key, const std::string& value);

        /**
         * @param key
         */
        void PutNULL(const std::string& key);

        void ClearValues();

        size_t GetValuesCount() const;

        const std::string ValuesAsSQLInsertString() const;

        const std::string ValuesAsSQLUpdateString() const;
    private:
        std::map< std::string, std::string> values_;
};

#endif  // _CONTENTVALUES_H
