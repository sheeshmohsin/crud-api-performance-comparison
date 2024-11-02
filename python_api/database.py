# database.py
import sqlite3
from flask import g

DATABASE = 'students.db'

def get_db():
    if 'db' not in g:
        g.db = sqlite3.connect(DATABASE)
        g.db.row_factory = sqlite3.Row  # Enable dictionary-like access to rows
    return g.db

def init_db():
    db = get_db()
    db.execute('''CREATE TABLE IF NOT EXISTS students (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT NOT NULL,
                    age INTEGER NOT NULL)''')
    db.commit()

def create_student(name, age):
    db = get_db()
    db.execute('INSERT INTO students (name, age) VALUES (?, ?)', (name, age))
    db.commit()

def read_students():
    db = get_db()
    cursor = db.execute('SELECT * FROM students')
    students = cursor.fetchall()
    return [{"id": row["id"], "name": row["name"], "age": row["age"]} for row in students]

def update_student(id, name, age):
    db = get_db()
    db.execute('UPDATE students SET name = ?, age = ? WHERE id = ?', (name, age, id))
    db.commit()

def delete_student(id):
    db = get_db()
    db.execute('DELETE FROM students WHERE id = ?', (id,))
    db.commit()

