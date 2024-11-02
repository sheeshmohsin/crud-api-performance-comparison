#!/bin/bash

# Directory for results
mkdir -p results

# CSV file to store results
OUTPUT_FILE="results/benchmark_results.csv"

# Endpoints for Python and C APIs
PYTHON_API="http://localhost:5000"
C_API="http://localhost:8888"

# Function to benchmark a specific endpoint
benchmark() {
    local api_url=$1
    local endpoint=$2
    local method=$3
    local params=$4

    # Measure the time taken for the request
    total_time=$(curl -o /dev/null -s -w "%{time_total}" -X $method "$api_url/$endpoint$params")
    echo "$api_url,$endpoint,$method,$total_time" >> $OUTPUT_FILE
}

# Write CSV header
echo "API,Endpoint,Method,Time(s)" > $OUTPUT_FILE

echo "Starting benchmarks..."

# Start the Python API and C API servers in separate terminals or background if needed

# Create benchmark
echo "Benchmarking Create endpoint..."
benchmark $PYTHON_API "create" "POST" "?name=John&age=20"
benchmark $C_API "create" "POST" "?name=John&age=20"

# Read benchmark
echo "Benchmarking Read endpoint..."
benchmark $PYTHON_API "read" "GET" ""
benchmark $C_API "read" "GET" ""

# Update benchmark (replace <id> with the actual ID you want to test with)
echo "Benchmarking Update endpoint..."
benchmark $PYTHON_API "update" "PUT" "?id=1&name=Jane&age=22"
benchmark $C_API "update" "PUT" "?id=1&name=Jane&age=22"

# Delete benchmark (replace <id> with the actual ID you want to test with)
echo "Benchmarking Delete endpoint..."
benchmark $PYTHON_API "delete" "DELETE" "?id=1"
benchmark $C_API "delete" "DELETE" "?id=1"

echo "Benchmarks completed. Results are saved in $OUTPUT_FILE"


