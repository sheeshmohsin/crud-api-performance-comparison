// students_db.h
#ifndef STUDENTS_DB_H
#define STUDENTS_DB_H

int initialize_database();
void close_database();
int create_student(const char *name, int age);
char *read_students();
int update_student(int id, const char *name, int age);
int delete_student(int id);

#endif // STUDENTS_DB_H

