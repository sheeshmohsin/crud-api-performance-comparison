# CRUD API Performance Comparison: C vs Python

## Overview

This repository provides a performance comparison between two CRUD APIs:
1. A **C-based API** built with **Libmicrohttpd** and **SQLite3**.
2. A **Python-based API** built with **Flask** and **SQLite3**.

The goal is to demonstrate the performance differences between a low-level language (C) and a higher-level language (Python) for typical CRUD operations. This repository allows you to observe how each language impacts response times, making it ideal for those focused on performance optimization.

## Repository Structure

```
crud-api-performance-comparison/
├── c_api/
│   ├── students_api.c             # Main C API file
│   ├── students_api.h             # C API header file
│   ├── students_db.c              # C database operations
│   ├── students_db.h              # C database operations header
│   ├── Makefile                   # Optional: For compiling C API
│   └── README.md                  # Documentation for C API setup and usage
├── python_api/
│   ├── app.py                     # Main Python Flask API file
│   ├── database.py                # Python database operations
│   ├── README.md                  # Documentation for Python API setup and usage
│   └── requirements.txt               # Python dependencies for easy setup
├── benchmark/
│   ├── benchmark_script.sh        # Script to benchmark both APIs with curl
│   └── results/                   # Directory to store benchmark results (CSV)
└── README.md                      # Main documentation
```

## Setup

1. **Clone the repository**:

    ```bash
    git clone <repository-url>
    cd crud-api-performance-comparison
    ```

### C API Setup

1. Install dependencies (for Ubuntu):

    ```bash
    sudo apt install libsqlite3-dev libmicrohttpd-dev
    ```

   For macOS, use Homebrew:

    ```bash
    brew install sqlite3 libmicrohttpd
    ```

2. Compile and run the C API:

    ```bash
    cd c_api
    make  # or manually: gcc students_api.c students_db.c -o students_api -lsqlite3 -lmicrohttpd
    ./students_api
    ```

   The C API server will run on `http://localhost:8888`.

### Python API Setup

1. Install dependencies:

    ```bash
    pip install -r requirements.txt
    ```

2. Run the Python API:

    ```bash
    cd python_api
    python app.py
    ```

   The Python API server will run on `http://localhost:5000`.

## Benchmarking

The `benchmark_script.sh` in the `benchmark/` folder automates the performance testing of both APIs using `curl`. The script will send requests to each API’s `create`, `read`, `update`, and `delete` endpoints, capturing the time taken for each operation and saving it in a CSV file for analysis.

### Running the Benchmark Script

1. Start both the C and Python API servers in separate terminals.
2. Run the benchmarking script:

    ```bash
    cd benchmark
    bash benchmark_script.sh
    ```

3. Results will be saved to `benchmark/results/benchmark_results.csv`.

### Example CSV Output

```
API,Endpoint,Method,Time(s)
http://localhost:5000,create,POST,0.017229
http://localhost:8888,create,POST,0.004574
http://localhost:5000,read,GET,0.002306
http://localhost:8888,read,GET,0.000555
http://localhost:5000,update,PUT,0.003243
http://localhost:8888,update,PUT,0.001363
http://localhost:5000,delete,DELETE,0.002395
http://localhost:8888,delete,DELETE,0.001283
```

## Results and Analysis

### Performance Summary

The benchmark results show that the **C-based API** significantly outperforms the **Python-based API** in terms of response times. Here is a comparison of average times for each operation:

| Operation | Python API Time (s) | C API Time (s) | Speedup Factor (Python/C) |
|-----------|----------------------|----------------|---------------------------|
| Create    | 0.017229             | 0.004574      | ~3.8x                     |
| Read      | 0.002306             | 0.000555      | ~4.2x                     |
| Update    | 0.003243             | 0.001363      | ~2.4x                     |
| Delete    | 0.002395             | 0.001283      | ~1.9x                     |

### Key Takeaways

1. **C is Faster**: Across all CRUD operations, the C API consistently performs faster than the Python API, with a speedup factor ranging from **2x to 4x**.
   
2. **Optimal for Resource-Constrained Environments**: This speed advantage makes the C API a better choice for environments where performance and resource efficiency are critical, such as embedded systems or high-throughput applications.

3. **Python’s Ease of Development**: Despite being slower, the Python API offers advantages in terms of readability, ease of development, and rapid prototyping, making it ideal for applications where development speed is more critical than performance.

### Conclusion

This comparison highlights the classic trade-off between **performance** and **development efficiency**:
- **C API**: Ideal for performance-critical applications.
- **Python API**: Great for quick development and applications where ease of use is prioritized over raw speed.

## License

This project is licensed under the MIT License.
