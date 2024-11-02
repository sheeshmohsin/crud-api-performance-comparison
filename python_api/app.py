# app.py
from flask import Flask, request, jsonify, g
import database

app = Flask(__name__)

@app.before_request
def before_request():
    database.init_db()

@app.teardown_appcontext
def close_connection(exception):
    db = g.pop('db', None)
    if db is not None:
        db.close()

# Endpoint to create a new student
@app.route('/create', methods=['POST'])
def create():
    name = request.args.get('name')
    age = request.args.get('age')
    if name and age:
        try:
            database.create_student(name, int(age))
            return jsonify({"status": "success"}), 201
        except Exception as e:
            return jsonify({"status": "error", "message": str(e)}), 400
    return jsonify({"status": "error", "message": "Missing name or age"}), 400

# Endpoint to read all students
@app.route('/read', methods=['GET'])
def read():
    students = database.read_students()
    return jsonify(students), 200

# Endpoint to update a student
@app.route('/update', methods=['PUT'])
def update():
    id = request.args.get('id')
    name = request.args.get('name')
    age = request.args.get('age')
    if id and name and age:
        try:
            database.update_student(int(id), name, int(age))
            return jsonify({"status": "success"}), 200
        except Exception as e:
            return jsonify({"status": "error", "message": str(e)}), 400
    return jsonify({"status": "error", "message": "Missing id, name, or age"}), 400

# Endpoint to delete a student
@app.route('/delete', methods=['DELETE'])
def delete():
    id = request.args.get('id')
    if id:
        try:
            database.delete_student(int(id))
            return jsonify({"status": "success"}), 200
        except Exception as e:
            return jsonify({"status": "error", "message": str(e)}), 400
    return jsonify({"status": "error", "message": "Missing id"}), 400

if __name__ == '__main__':
    app.run(debug=True)

