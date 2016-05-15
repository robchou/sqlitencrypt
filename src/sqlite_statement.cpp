#include <string>
#include <cstdint>
#include <sqlite3.h>

#include "sqlitencrypt/sqlite_statement.h"

SQLiteStatement::SQLiteStatement(sqlite3* sqlite3_handler, const string& stmt) {
    //TODO(robin)
}
SQLiteStatement::~SQLiteStatement() {
    //TODO(robin)
}
int SQLiteStatement::bind(const int index, const bool& value) {
    //TODO(robin)
    return SQLITE_OK;
}
int SQLiteStatement::bind(const int index, const int32_t& value) {
    //TODO(robin)
    return SQLITE_OK;
}
int SQLiteStatement::bind(const int index, const int64_t& value) {
    //TODO(robin)
    return SQLITE_OK;
}
int SQLiteStatement::bind(const int index, const double& value) {
    //TODO(robin)
    return SQLITE_OK;
}
int SQLiteStatement::bind(const int index, const string& value) {
    //TODO(robin)
    return SQLITE_OK;
}
int SQLiteStatement::bind(const int index, const char* value) {
    //TODO(robin)
    return SQLITE_OK;
}
int SQLiteStatement::bind(const int index, const void* value, const int size) {
    //TODO(robin)
    return SQLITE_OK;
}
int SQLiteStatement::bind(const int index) {
    //TODO(robin)
    return SQLITE_OK;
}
