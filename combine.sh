#!/bin/bash

# Script to combine cp_utils.hpp and a given C++ main file into a single file for submission.

# Default main C++ file, can be overridden by the first argument
DEFAULT_MAIN_CPP_FILE="main.cpp"
MAIN_CPP_FILE=${1:-$DEFAULT_MAIN_CPP_FILE}

CP_UTILS_HEADER_FILE="cp_utils.hpp"
# This script assumes cp_utils.hpp already handles including debug_utils.hpp
INCLUDE_DIRECTIVE='#include "cp_utils.hpp"' # The exact include line to replace in MAIN_CPP_FILE

# Construct submission filename: submission_<main_cpp_basename_no_ext>.cpp
MAIN_CPP_BASENAME=$(basename -- "$MAIN_CPP_FILE")
if [ -z "$MAIN_CPP_BASENAME" ]; then
    echo "Error: Could not determine basename for '$MAIN_CPP_FILE'"
    exit 1
fi
MAIN_CPP_BASENAME_NO_EXT="${MAIN_CPP_BASENAME%.*}"
SUBMISSION_FILE="submission_${MAIN_CPP_BASENAME_NO_EXT}.cpp"

# Check if the necessary files exist
if [ ! -f "$MAIN_CPP_FILE" ]; then
    echo "Error: Main C++ file '$MAIN_CPP_FILE' not found."
    exit 1
fi

if [ ! -f "$CP_UTILS_HEADER_FILE" ]; then
    echo "Error: Core utilities header file '$CP_UTILS_HEADER_FILE' not found."
    exit 1
fi

# Read the content of the cp_utils header file
CP_UTILS_HEADER_CONTENT=$(awk '1' "$CP_UTILS_HEADER_FILE")

# Read the main C++ file content
MAIN_CPP_CONTENT=$(cat "$MAIN_CPP_FILE")

# Use a unique placeholder to avoid collision with file content
PLACEHOLDER="___CP_UTILS_HEADER_CONTENT_PLACEHOLDER_$(date +%s%N)___"

# Replace the include directive with the placeholder in the main C++ content
TEMP_CONTENT=$(echo "$MAIN_CPP_CONTENT" | awk -v directive="$INCLUDE_DIRECTIVE" -v ph="$PLACEHOLDER" '
    BEGIN { replaced=0 }
    $0 == directive {
        print ph;
        replaced=1;
        next;
    }
    { print }
    END {
        if (replaced == 0) {
            print "Warning: Include directive \"" directive "\" not found in '$MAIN_CPP_FILE'. Submission file might be incomplete." > "/dev/stderr"
        }
    }
')

# Now, replace the placeholder with the actual cp_utils header content using awk.
awk -v ph="$PLACEHOLDER" -v header_content="$CP_UTILS_HEADER_CONTENT" '
    $0 == ph {
        printf "%s\n", header_content # Print header and a newline after it
        next
    }
    { print }
' <<< "$TEMP_CONTENT" > "$SUBMISSION_FILE"

echo "Successfully combined '$MAIN_CPP_FILE' and '$CP_UTILS_HEADER_FILE' (and its includes like debug_utils.hpp) into '$SUBMISSION_FILE'"
echo ""
echo "Reminder: Compile '$SUBMISSION_FILE' for online judges WITHOUT -DPRACTICE or -DLOCAL flags."
echo "Example: g++ -std=c++20 -O2 -Wall -DONLINE_JUDGE '$SUBMISSION_FILE' -o solution" 