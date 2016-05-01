#include <cstdlib>
#include "sqlitencrypt/sqlite_db.h"
#include "sqlitencrypt/content_values.h"
#include "sqlitencrypt/log.h"

using std::string;

int main(int argc, char *argv[])
{
    SQLiteDB db;
    SQLiteTable table;
    ContentValues values;

    string db_path = "./";
    string db_name = "test";
    string table_name = "COMPANY";
    const string ID = "ID";
    const string NAME = "NAME";
    const string AGE = "AGE";
    const string ADDRESS = "ADDRESS";
    const string SALARY = "SALARY";

    // Open database
    //int rc = db.Open(db_path, db_name, "passwd");
    int rc = db.Open(db_path, db_name);

    if (rc) {
        LOGE("Error: open database %s return %s", db_name.c_str(), SQLiteDB::SQLiteCodeAsString(rc).c_str());
        exit(1);
    }

    table.set_table_name(table_name);
    table.AddColumn(ID,"INT PRIMARY KEY NOT NULL");
    table.AddColumn(NAME,"TEXT NOT NULL" );
    table.AddColumn(AGE, "INT NOT NULL");
    table.AddColumn(ADDRESS, "CHAR(50)");
    table.AddColumn(SALARY, "REAL");

    // Create table
    rc = db.Create(table);

    if (rc) {
        LOGE("Error: create table %s, return %s", table_name.c_str(), SQLiteDB::SQLiteCodeAsString(rc).c_str());
        exit(2);
    }

    // Insert records
    values.PutInt64(ID, 1);
    values.PutText(NAME, "Paul");
    values.PutInt32(AGE, 32);
    values.PutText(ADDRESS, "California");
    values.PutDouble(SALARY, 20000.00);
    db.Insert(table_name, values);

    values.PutInt64(ID, 2);
    values.PutText(NAME, "Allen");
    values.PutInt32(AGE, 25);
    values.PutText(ADDRESS, "Texas");
    values.PutDouble(SALARY, 15000.00);
    db.Insert(table_name, values);

    values.PutInt64(ID, 3);
    values.PutText(NAME, "Teddy");
    values.PutInt32(AGE, 23);
    values.PutText(ADDRESS, "Norway");
    values.PutDouble(SALARY, 20000.00);
    db.Insert(table_name, values);

    values.PutInt64(ID, 4);
    values.PutText(NAME, "Mark");
    values.PutInt32(AGE, 25);
    values.PutText(ADDRESS, "Rich-Mond");
    values.PutDouble(SALARY, 65000.00);
    db.Insert(table_name, values);

    values.PutInt64(ID, 5);
    values.PutText(NAME, "David");
    values.PutInt32(AGE, 27);
    values.PutText(ADDRESS, "Texas");
    values.PutDouble(SALARY, 85000.00);
    db.Insert(table_name, values);

    values.PutInt64(ID, 6);
    values.PutText(NAME, "Kim");
    values.PutInt32(AGE, 22);
    values.PutText(ADDRESS, "South-Hall");
    values.PutDouble(SALARY, 45000.00);
    db.Insert(table_name, values);

    values.PutInt64(ID, 7);
    values.PutText(NAME, "James");
    values.PutInt32(AGE, 24);
    values.PutText(ADDRESS, "Houston");
    values.PutDouble(SALARY, 10000.00);
    db.Insert(table_name, values);

    // Update record
    values.PutText(ADDRESS, "Test-Update");
    db.Update(table_name, values, "WHERE ID = 7");

    // Query record
    SQLiteTable res;
    db.Query(table_name, {ID, NAME, SALARY}, "WHERE AGE < 28 ORDER BY ID DESC", &res);
    LOGE("\n===== Query Result =====\n");
    LOGE("%s", res.RecordsAsSQLQueryString().c_str());

    res.ClearRecords();
    db.Query(table_name, NAME, "WHERE AGE < 28 ORDER BY ID DESC", &res);
    LOGE("\n===== Query Result =====\n");
    LOGE("%s", res.RecordsAsSQLQueryString().c_str());
    return 0;
}
