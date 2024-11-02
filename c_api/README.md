## High-Performance CRUD API in C using SQLite3 and Libmicrohttpd

This project showcases a high-performance, lightweight CRUD (Create, Read, Update, Delete) API built in **C** with **SQLite3** as the database and **Libmicrohttpd** as the HTTP server. It is designed to provide fast and efficient data handling and HTTP request processing, ideal for performance-centric applications or embedded systems.

### Features

- **Built with C** for optimal performance.
- Uses **SQLite3** as an embedded, lightweight database.
- Powered by **Libmicrohttpd** for minimal HTTP server overhead.
- Simple, modular structure with separate files for API and database logic.

---

### Prerequisites

Ensure you have the following dependencies installed:

- **GCC Compiler**
- **SQLite3 Library**: Install with `brew install sqlite3` on macOS or `sudo apt install libsqlite3-dev` on Linux.
- **Libmicrohttpd Library**: Install with `brew install libmicrohttpd` on macOS or `sudo apt install libmicrohttpd-dev` on Linux.

### Project Structure

```
students_crud_api/
├── students_api.c      # Main server and API handling code
├── students_api.h      # Header file for API declarations
├── students_db.c       # CRUD database functions
├── students_db.h       # Header file for database function declarations
└── README.md           # Project documentation
```

### Building and Running

To compile and run the API server, use the following commands:

```bash
gcc students_api.c students_db.c -o students_api -lsqlite3 -lmicrohttpd
./students_api
```

The server will start on `http://localhost:8888`. You can terminate the server by pressing **Enter**.

---

### API Endpoints

The API provides four primary endpoints to manage student data. Each endpoint returns a JSON response with a `status` message.

| HTTP Method | Endpoint        | Description           |
|-------------|-----------------|-----------------------|
| POST        | `/create`       | Create a new student  |
| GET         | `/read`         | Read all students     |
| PUT         | `/update`       | Update a student      |
| DELETE      | `/delete`       | Delete a student      |

---

### Testing with Curl

You can test the API endpoints using `curl` commands as shown below.

#### 1. Create a New Student

```bash
curl -X POST "http://localhost:8888/create?name=John&age=20"
```

#### 2. Read All Students

```bash
curl -X GET "http://localhost:8888/read"
```

#### 3. Update a Student

Replace `<id>` with the student’s ID you want to update.

```bash
curl -X PUT "http://localhost:8888/update?id=<id>&name=Jane&age=22"
```

#### 4. Delete a Student

Replace `<id>` with the student’s ID you want to delete.

```bash
curl -X DELETE "http://localhost:8888/delete?id=<id>"
```

---

### Why Use C?

This project leverages **C**, known for its speed, minimal memory overhead, and control over system resources, to create a fast and efficient CRUD API. Using C for server-side APIs is ideal for scenarios where performance is critical, such as embedded systems or high-throughput applications. The combination of **SQLite3** and **Libmicrohttpd** ensures that the application remains lightweight while offering robust database capabilities and HTTP handling.

--- 

### License

This project is licensed under the MIT License.
