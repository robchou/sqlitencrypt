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
#include <vector>
#include <unistd.h>
#include <fcntl.h>

#include "sqlite_db.h"
#include "log.h"

SQLiteDB::SQLiteDB() : sqlite3_handler_(nullptr) { }

SQLiteDB::~SQLiteDB() {
    if (sqlite3_handler_) {
        sqlite3_close(sqlite3_handler_);
    }
}

/**
 * @param db_path
 * @param db_name
 * @param password
 * @return int
 */
int SQLiteDB::Open(const string& db_path, const string& db_name, const string& password) {
    if (access(db_path.c_str(), F_OK)) {
        LOGE("Database path %s not exists", db_path.c_str());
        return SQLITE_CANTOPEN;
    }

    if (access(db_path.c_str(), R_OK | W_OK)) {
        LOGE("Database path %s cannot be read or written", db_path.c_str());
        return SQLITE_CANTOPEN;
    }

#ifdef __ANDROID__
    // Default sqlite3_temp_directory is unaccessable in android
    sqlite3_temp_directory = db_path.c_str();
#endif

    string db_file = db_path + db_name + ".db";
    int rc = sqlite3_open(db_file.c_str(), &sqlite3_handler_);

    if (rc) return rc;

    if (password.length()) {
        return sqlite3_key(sqlite3_handler_, password.c_str(), password.length());
    } else {
        return SQLITE_OK;
    }
}

/**
 * @param sqlite_table
 * @return int
 */
int SQLiteDB::Create(const SQLiteTable& sqlite_table) {
    string sql_statement = "CREATE TABLE IF NOT EXISTS " + sqlite_table.table_name()
        + "(" + sqlite_table.ColumnsAsSQLCreateString() + ")";
    return ExecSQL(sql_statement);
}

/**
 * @param table_name
 * @param columns
 * @return int
 */
int SQLiteDB::Create(const string& table_name, const string& columns) {
    string sql_statement = "CREATE TABLE IF NOT EXISTS " + table_name + "(" + columns + ")";

    return ExecSQL(sql_statement);
}

/**
 * @param table_name
 * @param column_name
 * @param where_condition
 * @param result_table
 */
int SQLiteDB::Query(const string& table_name, const string& column_name, const string& where_condition,
        SQLiteTable* result_table) {
    if (result_table) {
        string sql_statement = "SELECT " + column_name + " FROM " + table_name + " " + where_condition;
        return ExecSQL(sql_statement, result_table);
    } else {
        LOGE("Error: SQLiteTable* result_table is NULL");
        return SQLITE_ERROR;
    }
}

/**
 * @param table_name
 * @param column_names
 * @param where_condition
 * @param result_table
 */
int SQLiteDB::Query(const string& table_name, const vector<string>& column_names, const string& where_condition,
        SQLiteTable* result_table) {
    if (result_table) {
        string sql_statement;
        string column_names_as_sql;

        vector<string>::const_iterator it;
        for (it = column_names.cbegin(); it != column_names.cend(); ++it) {
            column_names_as_sql += *it + ", ";
        }

        column_names_as_sql = column_names_as_sql.substr(0, column_names_as_sql.length() - 2);

        sql_statement += "SELECT " + column_names_as_sql + " FROM " + table_name + " " + where_condition;


        return ExecSQL(sql_statement, result_table);
    } else {
        LOGE("Error: SQLiteTable* result_table is NULL");
        return SQLITE_ERROR;
    }
}

/**
 * @param table_name
 * @return int
 */
int SQLiteDB::Insert(const string& table_name, const ContentValues& values) {
    string sql_statement = "INSERT INTO " + table_name + " " + values.ValuesAsSQLInsertString();

    return ExecSQL(sql_statement);
}

/**
 * @param table_name
 * @param values
 * @param where_condition
 * @return int
 */
int SQLiteDB::Update(const string& table_name, const ContentValues& values, const string& where_condition) {
    string sql_statement = "UPDATE " + table_name + " SET " + values.ValuesAsSQLUpdateString() + " " + where_condition;

    return ExecSQL(sql_statement);
}

/**
 * @param table_name
 * @param where_condition
 * @return int
 */
int SQLiteDB::Delete(const string& table_name, const string& where_condition) {
    string sql_statement = "DELETE FROM " + table_name + " "  + where_condition;

    return ExecSQL(sql_statement);
}

/**
 * @param statement
 * @return int
 */
int SQLiteDB::ExecSQL(const string& statement, SQLiteTable* result_table) {
    char* errmsg;
    int rc;

    if (result_table) {
        rc = sqlite3_exec(sqlite3_handler_, statement.c_str(), SelectCallback, result_table, &errmsg);
    } else {
        rc = sqlite3_exec(sqlite3_handler_, statement.c_str(), nullptr, nullptr, &errmsg);
    }

    if (rc) {
        LOGE("%s, return %s", errmsg, SQLiteCodeAsString(rc).c_str());
    }

    return rc;
}

/**
 * @return int
 */
int SQLiteDB::Begin() {
    return ExecSQL("BEGIN");
}

/**
 * @return int
 */
int SQLiteDB::Commit() {
    return ExecSQL("COMMIT");
}

/**
 * @return int
 */
int SQLiteDB::RollBack() {
    return ExecSQL("ROLLBACK");
}

/**
 * @param error_code
 * @return const string
 */

const string SQLiteDB::SQLiteCodeAsString(int error_code) {
    switch (error_code) {
        case SQLITE_OK              : return "SQLITE_OK";
        case SQLITE_ERROR           : return "SQLITE_ERROR";
        case SQLITE_INTERNAL        : return "SQLITE_INTERNAL";
        case SQLITE_PERM            : return "SQLITE_PERM";
        case SQLITE_ABORT           : return "SQLITE_ABORT";
        case SQLITE_BUSY            : return "SQLITE_BUSY";
        case SQLITE_LOCKED          : return "SQLITE_LOCKED";
        case SQLITE_NOMEM           : return "SQLITE_NOMEM";
        case SQLITE_READONLY        : return "SQLITE_READONLY";
        case SQLITE_INTERRUPT       : return "SQLITE_INTERRUPT";
        case SQLITE_IOERR           : return "SQLITE_IOERR";
        case SQLITE_CORRUPT         : return "SQLITE_CORRUPT";
        case SQLITE_NOTFOUND        : return "SQLITE_NOTFOUND";
        case SQLITE_FULL            : return "SQLITE_FULL";
        case SQLITE_CANTOPEN        : return "SQLITE_CANTOPEN";
        case SQLITE_PROTOCOL        : return "SQLITE_PROTOCOL";
        case SQLITE_EMPTY           : return "SQLITE_EMPTY";
        case SQLITE_SCHEMA          : return "SQLITE_SCHEMA";
        case SQLITE_TOOBIG          : return "SQLITE_TOOBIG";
        case SQLITE_CONSTRAINT      : return "SQLITE_CONSTRAINT";
        case SQLITE_MISMATCH        : return "SQLITE_MISMATCH";
        case SQLITE_MISUSE          : return "SQLITE_MISUSE";
        case SQLITE_NOLFS           : return "SQLITE_NOLFS";
        case SQLITE_AUTH            : return "SQLITE_AUTH";
        case SQLITE_FORMAT          : return "SQLITE_FORMAT";
        case SQLITE_RANGE           : return "SQLITE_RANGE";
        case SQLITE_NOTADB          : return "SQLITE_NOTADB";
        case SQLITE_NOTICE          : return "SQLITE_NOTICE";
        case SQLITE_WARNING         : return "SQLITE_WARNING";
        case SQLITE_ROW             : return "SQLITE_ROW";
        case SQLITE_DONE            : return "SQLITE_DONE";
        default                     : return "UNKNOWN_ERROR";
    }
}


int SQLiteDB::SelectCallback(void *data, int num_fields, char **fields, char **column_names) {
    SQLiteTable* res = reinterpret_cast<SQLiteTable*>(data);

    shared_ptr<SQLiteRecord> record(new SQLiteRecord());

    for (int i = 0; i < num_fields; i++) {
        if (fields[i]) {
            record->SetColumnValue(column_names[i], fields[i]);
        } else {
            record->SetColumnValue(column_names[i], "NULL");
        }
    }

    res->AddRecord(record);

    return 0;
}

