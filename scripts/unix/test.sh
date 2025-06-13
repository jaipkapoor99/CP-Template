#!/bin/bash

# Bash script for stress testing C++ competitive programming solutions
# Enhanced version with brute force comparison capabilities

set -e  # Exit on any error

# --- Default Configuration ---
NUM_TESTS=100
COMPILER="g++"
STD_VERSION="c++20"
OPTIMIZATION_LEVEL="-O2"
WARNING_FLAGS="-Wall"
PRACTICE_DEFINE="-DPRACTICE"  # Enables asserts and internal brute-force checks
LOCAL_DEFINE="-DLOCAL"        # Enables TRACE and DEBUG macros (optional)
SOURCE_FILE="../src/main.cpp"
EXECUTABLE_NAME="my_solution"
BRUTE_EXECUTABLE_NAME="brute_solution"
INPUT_FILE="input.txt"
OUTPUT_FILE="output.txt"
BRUTE_OUTPUT_FILE="brute_output.txt"

# Test case generator configuration
GENERATOR_TYPE="inline"  # "inline" or "python"
PYTHON_GENERATOR_SCRIPT="generate_input.py"

# Set to true to keep input/output files on failure for debugging
KEEP_FILES_ON_FAILURE=true

# Brute force comparison mode
USE_BRUTE_FORCE_COMPARISON=true  # Set to false to use internal ASSERT-based checking only

# Verbose mode
VERBOSE=false

# --- Parse Command Line Arguments ---
while [[ $# -gt 0 ]]; do
    case $1 in
        -n|--num-tests)
            NUM_TESTS="$2"
            shift 2
            ;;
        --no-brute)
            USE_BRUTE_FORCE_COMPARISON=false
            shift
            ;;
        --keep-files)
            KEEP_FILES_ON_FAILURE=true
            shift
            ;;
        --python-gen)
            GENERATOR_TYPE="python"
            shift
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [OPTIONS]"
            echo ""
            echo "Stress testing script for C++ competitive programming solutions"
            echo ""
            echo "Options:"
            echo "  -n, --num-tests N     Number of stress tests to run (default: 100)"
            echo "  --no-brute           Disable brute force comparison"
            echo "  --keep-files         Keep test files on failure for debugging"
            echo "  --python-gen         Use Python script for test case generation"
            echo "  -v, --verbose        Enable verbose output"
            echo "  -h, --help           Show this help message"
            echo ""
            echo "Examples:"
            echo "  $0                           # Run 100 tests with default settings"
            echo "  $0 -n 50                     # Run 50 stress tests"
            echo "  $0 --no-brute -n 200         # Run 200 tests without brute force"
            echo "  $0 --python-gen --keep-files # Use Python generator and keep files"
            echo ""
            echo "The script will:"
            echo "  1. Compile the main solution (../src/main.cpp)"
            echo "  2. Compile brute force solution (brute.cpp) if it exists"
            echo "  3. Generate random test cases"
            echo "  4. Compare outputs between main and brute force solutions"
            echo "  5. Report any mismatches or errors"
            exit 0
            ;;
        *)
            echo "Unknown option: $1" >&2
            echo "Use -h or --help for usage information." >&2
            exit 1
            ;;
    esac
done

# --- Helper Functions ---
log_info() {
    echo "$1"
}

log_error() {
    echo "ERROR: $1" >&2
}

log_warning() {
    echo "WARNING: $1"
}

log_verbose() {
    if [ "$VERBOSE" = true ]; then
        echo "$1"
    fi
}

# --- Determine script directory and change to tests directory ---
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$(dirname "$SCRIPT_DIR")")"

# Change to tests directory (create if it doesn't exist)
TESTS_DIR="$PROJECT_ROOT/tests"
if [ ! -d "$TESTS_DIR" ]; then
    mkdir -p "$TESTS_DIR"
fi
cd "$TESTS_DIR"

# --- Compilation ---
log_info "Compiling $SOURCE_FILE..."

compile_args=(
    "-std=$STD_VERSION"
    "$OPTIMIZATION_LEVEL"
    "$WARNING_FLAGS"
    "$PRACTICE_DEFINE"
    "$LOCAL_DEFINE"
    "$SOURCE_FILE"
    "-o"
    "$EXECUTABLE_NAME"
)

if ! "$COMPILER" "${compile_args[@]}" 2>&1; then
    log_error "Compilation failed!"
    exit 1
fi
log_info "Compilation successful."

# --- Compile Brute Force Solution (if using brute force comparison) ---
if [ "$USE_BRUTE_FORCE_COMPARISON" = true ]; then
    BRUTE_SOURCE_FILE="brute.cpp"
    if [ ! -f "$BRUTE_SOURCE_FILE" ]; then
        log_warning "Brute force comparison enabled but '$BRUTE_SOURCE_FILE' not found."
        log_info "Creating template brute force file '$BRUTE_SOURCE_FILE'..."
        
        cat > "$BRUTE_SOURCE_FILE" << 'EOF'
#include "../include/cp_utils.hpp"

// TODO: Implement your brute force solution here
// This should solve the same problem as main.cpp but with a simpler, slower approach
void solve_brute(int test_case_num) 
{
    int n;
    read(n);
    
    // Example brute force: sum 1 to n using a loop instead of formula
    ll result = 0;
    for (int i = 1; i <= n; i++) {
        result += i;
    }
    
    print(result);
}

int main()
{
    FASTINOUT;
    int t;
    read(t);
    
    f(i, 0, t)
        solve_brute(i + 1);
        
    return 0;
}
EOF
        log_info "Template brute force file created. Please implement your brute force logic."
    fi
    
    log_info "Compiling brute force solution..."
    brute_compile_args=(
        "-std=$STD_VERSION"
        "$OPTIMIZATION_LEVEL"
        "$WARNING_FLAGS"
        "$PRACTICE_DEFINE"
        "$LOCAL_DEFINE"
        "$BRUTE_SOURCE_FILE"
        "-o"
        "$BRUTE_EXECUTABLE_NAME"
    )
    
    if ! "$COMPILER" "${brute_compile_args[@]}" 2>&1; then
        log_error "Brute force compilation failed!"
        exit 1
    fi
    log_info "Brute force compilation successful."
fi

# --- Cleanup function ---
cleanup_files() {
    if [ "$KEEP_FILES_ON_FAILURE" = true ] && [ "$1" != "success" ]; then
        log_info "Files kept for debugging: $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE"
    else
        rm -f "$EXECUTABLE_NAME" "$BRUTE_EXECUTABLE_NAME" "$INPUT_FILE" "$OUTPUT_FILE" "$BRUTE_OUTPUT_FILE" 2>/dev/null || true
    fi
}

# Set up cleanup trap
trap 'cleanup_files "failure"' EXIT

# --- Stress Testing ---
log_info "Running $NUM_TESTS stress tests..."
PASSED_COUNT=0

for ((i = 1; i <= NUM_TESTS; i++)); do
    printf "Test %d/%d: " "$i" "$NUM_TESTS"

    # Generate test case
    if [ "$GENERATOR_TYPE" = "python" ]; then
        if [ ! -f "$PYTHON_GENERATOR_SCRIPT" ]; then
            log_info "Python generator script '$PYTHON_GENERATOR_SCRIPT' not found!"
            log_info "Creating placeholder $PYTHON_GENERATOR_SCRIPT..."
            
            cat > "$PYTHON_GENERATOR_SCRIPT" << 'EOF'
import random

# Example: Generate a random number N
# Modify this to generate input for your specific problem
n = random.randint(1, 1000)
print(n)

# Example for a problem needing an array:
# size = random.randint(1, 10)
# print(size)
# arr = [random.randint(1, 100) for _ in range(size)]
# print(*arr)
EOF
        fi
        
        if ! python3 "$PYTHON_GENERATOR_SCRIPT" > "$INPUT_FILE" 2>/dev/null; then
            log_error "Input generation failed!"
            cleanup_files "failure"
            exit 1
        fi
    else
        # Inline generator - generates a random number N between 1 and 1000
        # TODO: Customize this inline generator for your problem
        test_cases=$((RANDOM % 3 + 1))  # Random number of test cases (1-3)
        {
            echo "$test_cases"
            for ((tc = 1; tc <= test_cases; tc++)); do
                n=$((RANDOM % 1000 + 1))
                echo "$n"
            done
        } > "$INPUT_FILE"
    fi

    # Run the main solution
    if ! timeout 10 "./$EXECUTABLE_NAME" < "$INPUT_FILE" > "$OUTPUT_FILE" 2>/dev/null; then
        log_error "Main solution runtime error!"
        log_info "Input:"
        cat "$INPUT_FILE"
        cleanup_files "failure"
        exit 1
    fi

    # Run brute force comparison if enabled
    if [ "$USE_BRUTE_FORCE_COMPARISON" = true ]; then
        if ! timeout 10 "./$BRUTE_EXECUTABLE_NAME" < "$INPUT_FILE" > "$BRUTE_OUTPUT_FILE" 2>/dev/null; then
            log_error "Brute force solution runtime error!"
            log_info "Input:"
            cat "$INPUT_FILE"
            cleanup_files "failure"
            exit 1
        fi

        # Compare outputs
        main_output=$(cat "$OUTPUT_FILE" | tr -d '\r' | sed 's/[[:space:]]*$//')
        brute_output=$(cat "$BRUTE_OUTPUT_FILE" | tr -d '\r' | sed 's/[[:space:]]*$//')
        
        if [ "$main_output" != "$brute_output" ]; then
            echo "FAILED"
            log_error "Output mismatch!"
            log_info "Input:"
            cat "$INPUT_FILE"
            log_info "Main solution output:"
            echo "$main_output"
            log_info "Brute force output:"
            echo "$brute_output"
            cleanup_files "failure"
            exit 1
        fi
    fi

    echo "Passed."
    ((PASSED_COUNT++))
done

echo ""
log_info "All $PASSED_COUNT/$NUM_TESTS tests passed successfully!"

# --- Cleanup ---
cleanup_files "success"
trap - EXIT  # Remove the trap since we're cleaning up manually

exit 0 