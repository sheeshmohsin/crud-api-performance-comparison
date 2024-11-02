// students_db.c
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students_db.h"

sqlite3 *db;

int initialize_database() {
    if (sqlite3_open("students.db", &db) == SQLITE_OK) {
        const char *sql = "CREATE TABLE IF NOT EXISTS students (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);";
        return sqlite3_exec(db, sql, NULL, NULL, NULL) == SQLITE_OK;
    }
    return 0;
}

void close_database() {
    sqlite3_close(db);
}

int create_student(const char *name, int age) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO students (name, age) VALUES ('%s', %d);", name, age);
    return sqlite3_exec(db, sql, NULL, NULL, NULL) == SQLITE_OK;
}

char *read_students() {
    char *result = malloc(1024);
    strcpy(result, "[");

    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM students;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            char buffer[256];
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char *name = sqlite3_column_text(stmt, 1);
            int age = sqlite3_column_int(stmt, 2);
            snprintf(buffer, sizeof(buffer), "{\"id\":%d,\"name\":\"%s\",\"age\":%d},", id, name, age);
            strcat(result, buffer);
        }
        sqlite3_finalize(stmt);
    }
    result[strlen(result) - 1] = ']'; // Replace last comma with closing bracket
    return result;
}

int update_student(int id, const char *name, int age) {
    char sql[256];
    snprintf(sql, sizeof(sql), "UPDATE students SET name='%s', age=%d WHERE id=%d;", name, age, id);
    return sqlite3_exec(db, sql, NULL, NULL, NULL) == SQLITE_OK;
}

int delete_student(int id) {
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM students WHERE id=%d;", id);
    return sqlite3_exec(db, sql, NULL, NULL, NULL) == SQLITE_OK;
}

