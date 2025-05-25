#!/bin/bash

# --- Configuration ---
COMPILER="g++"
STD_VERSION="c++20"
OPTIMIZATION_LEVEL="-O2"
WARNING_FLAGS="-Wall"
PRACTICE_DEFINE="-DPRACTICE" # Enables asserts and internal brute-force checks
LOCAL_DEFINE="-DLOCAL"     # Enables TRACE and DEBUG macros (optional)
SOURCE_FILE="template.cpp"
EXECUTABLE_NAME="my_solution"
INPUT_FILE="input.txt"
OUTPUT_FILE="output.txt"
BRUTE_OUTPUT_FILE="brute_output.txt" # If using a separate brute force solution

# Number of test cases to run (can be overridden by script argument)
DEFAULT_NUM_TESTS=100
NUM_TESTS=${1:-$DEFAULT_NUM_TESTS} # Use first argument or default

# Test case generator (customize as needed)
# Option 1: Simple inline generator (current example: random N)
# Option 2: Python script (more flexible for complex cases)
GENERATOR_TYPE="inline" # "inline" or "python"
PYTHON_GENERATOR_SCRIPT="generate_input.py"

# Set to "true" to keep input/output files on failure for debugging
KEEP_FILES_ON_FAILURE=true

# --- Compilation ---
echo "Compiling $SOURCE_FILE..."
$COMPILER -std=$STD_VERSION $OPTIMIZATION_LEVEL $WARNING_FLAGS $PRACTICE_DEFINE $LOCAL_DEFINE $SOURCE_FILE debug_utils.hpp -o $EXECUTABLE_NAME

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi
echo "Compilation successful."

# --- Stress Testing ---
echo "Running $NUM_TESTS stress tests..."
PASSED_COUNT=0

for ((i=1; i<=NUM_TESTS; i++))
do
    echo -n "Test $i/$NUM_TESTS: "

    # Generate test case
    if [ "$GENERATOR_TYPE" == "python" ]; then
        if [ ! -f "$PYTHON_GENERATOR_SCRIPT" ]; then
            echo "Python generator script '$PYTHON_GENERATOR_SCRIPT' not found!"
            # Create a placeholder generator if it doesn't exist
            echo "Creating placeholder $PYTHON_GENERATOR_SCRIPT..."
            cat <<EOL > $PYTHON_GENERATOR_SCRIPT
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
EOL
        fi
        python $PYTHON_GENERATOR_SCRIPT > $INPUT_FILE
    else # Inline generator
        # This example generates a random number N between 1 and 1000
        # TODO: Customize this inline generator for your problem
        N=$(shuf -i 1-1000 -n 1)
        echo "$N" > $INPUT_FILE
    fi

    # Check if input generation was successful
    if [ $? -ne 0 ]; then
        echo "Input generation failed!"
        if [ "$KEEP_FILES_ON_FAILURE" != "true" ]; then
            rm -f $EXECUTABLE_NAME $INPUT_FILE $OUTPUT_FILE $BRUTE_OUTPUT_FILE
        fi
        exit 1
    fi

    # Run the solution
    ./$EXECUTABLE_NAME < $INPUT_FILE > $OUTPUT_FILE

    # Check for runtime errors
    if [ $? -ne 0 ]; then
        echo "Runtime error!"
        echo "Input:"
        cat $INPUT_FILE
        if [ "$KEEP_FILES_ON_FAILURE" != "true" ]; then
            rm -f $EXECUTABLE_NAME $INPUT_FILE $OUTPUT_FILE $BRUTE_OUTPUT_FILE
        fi
        exit 1
    fi

    # The C++ template has an internal brute-force check with ASSERT.
    # If the solution reaches this point without exiting, the internal check passed.
    # If you were using a separate brute-force executable, you would compare outputs here:
    # ./my_brute_solution < $INPUT_FILE > $BRUTE_OUTPUT_FILE
    # if [ $? -ne 0 ]; then
    #     echo "Brute force solution runtime error!"
    #     echo "Input:"
    #     cat $INPUT_FILE
    #     if [ "$KEEP_FILES_ON_FAILURE" != "true" ]; then
    #         rm -f $EXECUTABLE_NAME $INPUT_FILE $OUTPUT_FILE $BRUTE_OUTPUT_FILE
    #     fi
    #     exit 1
    # fi
    #
    # if ! diff -q $OUTPUT_FILE $BRUTE_OUTPUT_FILE; then
    #     echo "Output mismatch!"
    #     echo "Input:"
    #     cat $INPUT_FILE
    #     echo "Your output:"
    #     cat $OUTPUT_FILE
    #     echo "Brute output:"
    #     cat $BRUTE_OUTPUT_FILE
    #     if [ "$KEEP_FILES_ON_FAILURE" != "true" ]; then
    #         rm -f $EXECUTABLE_NAME $INPUT_FILE $OUTPUT_FILE $BRUTE_OUTPUT_FILE
    #     fi
    #     exit 1
    # fi

    echo "Passed."
    PASSED_COUNT=$((PASSED_COUNT + 1))
done

echo ""
echo "All $PASSED_COUNT/$NUM_TESTS tests passed successfully!"

# --- Cleanup ---
if [ "$KEEP_FILES_ON_FAILURE" == "true" ] && [ "$PASSED_COUNT" -ne "$NUM_TESTS" ]; then
    echo "Files kept for debugging: $INPUT_FILE, $OUTPUT_FILE"
else
    rm -f $EXECUTABLE_NAME $INPUT_FILE $OUTPUT_FILE $BRUTE_OUTPUT_FILE
    # Optionally remove the python generator if it was auto-created and you don't want to keep it
    # if [ -f "$PYTHON_GENERATOR_SCRIPT" ] && grep -q "Example: Generate a random number N" "$PYTHON_GENERATOR_SCRIPT"; then
    #     rm -f $PYTHON_GENERATOR_SCRIPT
    # fi
fi

exit 0
