#!/bin/bash

# Comprehensive testing script for CP-Template
# Compiles and tests C++ solutions with various input/output scenarios

set -e  # Exit on any error

# Default values
CPP_FILE=""
INPUT_FILE=""
EXPECTED_OUTPUT=""
COMPILER="g++"
TIMEOUT=5
VERBOSE=false
CLEAN_AFTER=true
COMPILE_FLAGS="-std=c++20 -O2 -Wall -Wextra"

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -f|--file)
            CPP_FILE="$2"
            shift 2
            ;;
        -i|--input)
            INPUT_FILE="$2"
            shift 2
            ;;
        -o|--output)
            EXPECTED_OUTPUT="$2"
            shift 2
            ;;
        -c|--compiler)
            COMPILER="$2"
            shift 2
            ;;
        -t|--timeout)
            TIMEOUT="$2"
            shift 2
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        --no-clean)
            CLEAN_AFTER=false
            shift
            ;;
        --flags)
            COMPILE_FLAGS="$2"
            shift 2
            ;;
        -h|--help)
            echo "Usage: $0 [OPTIONS]"
            echo ""
            echo "Options:"
            echo "  -f, --file FILE       C++ file to test (default: auto-detect)"
            echo "  -i, --input FILE      Input file for testing"
            echo "  -o, --output FILE     Expected output file"
            echo "  -c, --compiler CMD    Compiler to use (default: g++)"
            echo "  -t, --timeout SEC     Execution timeout in seconds (default: 5)"
            echo "  -v, --verbose         Show detailed output"
            echo "  --no-clean           Don't clean up executable after testing"
            echo "  --flags FLAGS        Custom compilation flags"
            echo "  -h, --help           Show this help message"
            echo ""
            echo "Examples:"
            echo "  $0                                    # Test auto-detected file"
            echo "  $0 -f solution.cpp -i input.txt      # Test specific file with input"
            echo "  $0 -f main.cpp -i in.txt -o out.txt  # Test with expected output"
            exit 0
            ;;
        *)
            echo "Unknown option: $1" >&2
            echo "Use -h or --help for usage information." >&2
            exit 1
            ;;
    esac
done

# Determine script and project root directories
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Change to project root
cd "$PROJECT_ROOT"

log_verbose() {
    if [ "$VERBOSE" = true ]; then
        echo "$1"
    fi
}

log_info() {
    echo "ℹ️  $1"
}

log_success() {
    echo "✅ $1"
}

log_error() {
    echo "❌ $1" >&2
}

log_warning() {
    echo "⚠️  $1"
}

# Auto-detect C++ file if not specified
if [ -z "$CPP_FILE" ]; then
    # Look for main.cpp first, then any .cpp file
    if [ -f "src/main.cpp" ]; then
        CPP_FILE="src/main.cpp"
    elif [ -f "main.cpp" ]; then
        CPP_FILE="main.cpp"
    else
        # Find first .cpp file
        CPP_FILE=$(find . -maxdepth 2 -name "*.cpp" -type f | head -1)
        if [ -z "$CPP_FILE" ]; then
            log_error "No C++ file found. Please specify with -f option."
            exit 1
        fi
    fi
    log_info "Auto-detected C++ file: $CPP_FILE"
fi

# Verify C++ file exists
if [ ! -f "$CPP_FILE" ]; then
    log_error "C++ file '$CPP_FILE' not found."
    exit 1
fi

# Generate executable name
EXECUTABLE="${CPP_FILE%.*}"
if [[ "$EXECUTABLE" == *"/"* ]]; then
    EXECUTABLE="$(basename "$EXECUTABLE")"
fi

echo "🚀 CP-Template Testing Script"
echo "================================"
echo "File: $CPP_FILE"
echo "Compiler: $COMPILER"
echo "Flags: $COMPILE_FLAGS"
echo "Timeout: ${TIMEOUT}s"
echo ""

# Compilation phase
log_info "Compiling $CPP_FILE..."
log_verbose "Command: $COMPILER $COMPILE_FLAGS -o $EXECUTABLE $CPP_FILE"

if ! $COMPILER $COMPILE_FLAGS -o "$EXECUTABLE" "$CPP_FILE" 2>&1; then
    log_error "Compilation failed!"
    exit 1
fi

log_success "Compilation successful!"

# Cleanup function
cleanup() {
    if [ "$CLEAN_AFTER" = true ] && [ -f "$EXECUTABLE" ]; then
        log_verbose "Cleaning up executable: $EXECUTABLE"
        rm -f "$EXECUTABLE"
    fi
}

# Set up cleanup trap
trap cleanup EXIT

# Testing phase
echo ""
log_info "Starting tests..."

# Test 1: Basic execution (no input file)
if [ -z "$INPUT_FILE" ]; then
    echo ""
    echo "📝 Test 1: Interactive/Manual Input"
    echo "Enter your input (Ctrl+D to finish):"
    
    if timeout "$TIMEOUT" "./$EXECUTABLE"; then
        log_success "Program executed successfully!"
    else
        exit_code=$?
        if [ $exit_code -eq 124 ]; then
            log_error "Program timed out after ${TIMEOUT} seconds!"
        else
            log_error "Program failed with exit code: $exit_code"
        fi
        exit 1
    fi
else
    # Test with input file
    if [ ! -f "$INPUT_FILE" ]; then
        log_error "Input file '$INPUT_FILE' not found."
        exit 1
    fi
    
    echo ""
    echo "📝 Test: File Input"
    echo "Input file: $INPUT_FILE"
    
    log_verbose "Input content:"
    if [ "$VERBOSE" = true ]; then
        cat "$INPUT_FILE" | sed 's/^/  /'
    fi
    
    # Run program with input file
    ACTUAL_OUTPUT_FILE="actual_output.tmp"
    
    if timeout "$TIMEOUT" "./$EXECUTABLE" < "$INPUT_FILE" > "$ACTUAL_OUTPUT_FILE" 2>&1; then
        log_success "Program executed successfully!"
        
        echo ""
        echo "📤 Program Output:"
        cat "$ACTUAL_OUTPUT_FILE" | sed 's/^/  /'
        
        # Compare with expected output if provided
        if [ -n "$EXPECTED_OUTPUT" ]; then
            if [ ! -f "$EXPECTED_OUTPUT" ]; then
                log_warning "Expected output file '$EXPECTED_OUTPUT' not found. Skipping comparison."
            else
                echo ""
                echo "🔍 Comparing with expected output..."
                
                if diff -q "$ACTUAL_OUTPUT_FILE" "$EXPECTED_OUTPUT" > /dev/null; then
                    log_success "Output matches expected result!"
                else
                    log_error "Output differs from expected result!"
                    echo ""
                    echo "Expected output:"
                    cat "$EXPECTED_OUTPUT" | sed 's/^/  /'
                    echo ""
                    echo "Actual output:"
                    cat "$ACTUAL_OUTPUT_FILE" | sed 's/^/  /'
                    echo ""
                    echo "Differences:"
                    diff "$EXPECTED_OUTPUT" "$ACTUAL_OUTPUT_FILE" | sed 's/^/  /' || true
                    
                    # Cleanup temp file
                    rm -f "$ACTUAL_OUTPUT_FILE"
                    exit 1
                fi
            fi
        fi
        
        # Cleanup temp file
        rm -f "$ACTUAL_OUTPUT_FILE"
        
    else
        exit_code=$?
        if [ $exit_code -eq 124 ]; then
            log_error "Program timed out after ${TIMEOUT} seconds!"
        else
            log_error "Program failed with exit code: $exit_code"
            if [ -f "$ACTUAL_OUTPUT_FILE" ]; then
                echo "Error output:"
                cat "$ACTUAL_OUTPUT_FILE" | sed 's/^/  /'
            fi
        fi
        
        # Cleanup temp file
        rm -f "$ACTUAL_OUTPUT_FILE"
        exit 1
    fi
fi

echo ""
log_success "All tests completed successfully! 🎉"

# Performance info
if [ "$VERBOSE" = true ]; then
    echo ""
    echo "📊 Performance Info:"
    echo "  Executable size: $(du -h "$EXECUTABLE" 2>/dev/null | cut -f1 || echo "unknown")"
    echo "  Compilation time: Fast ⚡"
fi 