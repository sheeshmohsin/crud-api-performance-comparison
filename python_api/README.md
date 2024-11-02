# Python CRUD API with Flask and SQLite

This project provides a simple CRUD (Create, Read, Update, Delete) API built with **Flask** and **SQLite** in Python. It serves as a comparison point for performance analysis with a similar API built in C.

## Features

- Simple CRUD operations for managing student data.
- Uses **Flask** as the web framework.
- Stores data in a lightweight, embedded **SQLite** database.
- JSON responses for easy integration and testing.

## Requirements

- Python 3.6+
- **Flask** and **SQLite3** libraries

### Installation

1. **Clone the repository** and navigate to the `python_api` directory.

    ```bash
    git clone <repository-url>
    cd crud-api-performance-comparison/python_api
    ```

2. **Install dependencies**:

    ```bash
    pip install -r requirements.txt
    ```

## Running the API

To start the Flask server, run:

```bash
python app.py
```

The server will run on `http://localhost:5000`.

## API Endpoints

The API provides the following endpoints to manage student data:

| HTTP Method | Endpoint           | Description                        |
|-------------|--------------------|------------------------------------|
| POST        | `/create`          | Creates a new student record       |
| GET         | `/read`            | Reads all student records          |
| PUT         | `/update`          | Updates a student record by ID     |
| DELETE      | `/delete`          | Deletes a student record by ID     |

Each endpoint returns a JSON response with the operation’s status and, in some cases, additional data.

### Usage and Examples

Here’s how to interact with each API endpoint using `curl`.

#### 1. Create a New Student

```bash
curl -X POST "http://localhost:5000/create?name=John&age=20"
```

- **Response**: `{ "status": "success" }` if the student was created successfully.

#### 2. Read All Students

```bash
curl -X GET "http://localhost:5000/read"
```

- **Response**: Returns a JSON array of all students.
  
  ```json
  [
      {
          "id": 1,
          "name": "John",
          "age": 20
      },
      {
          "id": 2,
          "name": "Jane",
          "age": 22
      }
  ]
  ```

#### 3. Update a Student

Replace `<id>` with the student’s actual ID.

```bash
curl -X PUT "http://localhost:5000/update?id=<id>&name=Jane&age=22"
```

- **Response**: `{ "status": "success" }` if the student record was updated.

#### 4. Delete a Student

Replace `<id>` with the student’s actual ID.

```bash
curl -X DELETE "http://localhost:5000/delete?id=<id>"
```

- **Response**: `{ "status": "success" }` if the student was deleted.

## Database Initialization

On startup, the API will automatically create the `students` table in `students.db` if it does not exist.

## Performance Comparison

This application is designed to be compared with a similar API written in **C** to understand the performance differences between the two. For detailed performance results, refer to the benchmark section in the main repository.

---

### License

This project is licensed under the MIT License.
