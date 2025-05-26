#!/bin/bash

# Script to combine cp_utils.hpp (with debug_utils.hpp inlined) and a given C++ main file
# into a single file for submission.

# Default main C++ file, can be overridden by the first argument
DEFAULT_MAIN_CPP_FILE="main.cpp"
MAIN_CPP_FILE=${1:-$DEFAULT_MAIN_CPP_FILE}

CP_UTILS_HEADER_FILE="cp_utils.hpp"
DEBUG_UTILS_HEADER_FILE="debug_utils.hpp" # Added for clarity

CP_UTILS_INCLUDE_DIRECTIVE='#include "cp_utils.hpp" // Core utilities, macros, and type aliases'
# Updated to match the exact line in cp_utils.hpp, including the comment
DEBUG_UTILS_INCLUDE_DIRECTIVE='#include "debug_utils.hpp" // Include the debug header'

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

if [ ! -f "$DEBUG_UTILS_HEADER_FILE" ]; then # Added check
    echo "Error: Debug utilities header file '$DEBUG_UTILS_HEADER_FILE' not found."
    exit 1
fi

# Read the content of debug_utils.hpp
DEBUG_UTILS_CONTENT=$(awk '1' "$DEBUG_UTILS_HEADER_FILE")

# Read the content of cp_utils.hpp
CP_UTILS_RAW_CONTENT=$(awk '1' "$CP_UTILS_HEADER_FILE")

# --- Inline debug_utils.hpp into cp_utils.hpp content ---
DEBUG_PLACEHOLDER="___DEBUG_UTILS_CONTENT_PLACEHOLDER_$(date +%s%N)___"

TEMP_CP_UTILS_CONTENT=$(awk -v directive="$DEBUG_UTILS_INCLUDE_DIRECTIVE" -v ph="$DEBUG_PLACEHOLDER" \
    -v header_file_name="$CP_UTILS_HEADER_FILE" '
    BEGIN { replaced_debug=0 }
    $0 == directive {
        print ph;
        replaced_debug=1;
        next;
    }
    { print }
    END {
        if (replaced_debug == 0 && NR > 0) {
            print "Warning: Include directive \"" directive "\" not found in " header_file_name ". Debug utils might not be inlined as expected." > "/dev/stderr"
        }
    }
' <<< "$CP_UTILS_RAW_CONTENT")

AUGMENTED_CP_UTILS_CONTENT=$(awk -v ph="$DEBUG_PLACEHOLDER" -v debug_content="$DEBUG_UTILS_CONTENT" '
    $0 == ph {
        if (length(debug_content) > 0) {
            printf "%s\n", debug_content
        } else {
            print "// debug_utils.hpp content was empty or not read, placeholder removed."
        }
        next
    }
    { print }
' <<< "$TEMP_CP_UTILS_CONTENT")
# --- End of inlining debug_utils.hpp into cp_utils.hpp ---

# Escape backslashes in the augmented content before passing to awk -v
# This prevents backslash-n in C++ macros from becoming literal newlines.
ESCAPED_AUGMENTED_CP_UTILS_CONTENT=$(echo "$AUGMENTED_CP_UTILS_CONTENT" | sed 's/\\/\\\\/g')

CP_UTILS_PLACEHOLDER="___CP_UTILS_HEADER_CONTENT_PLACEHOLDER_$(date +%s%N)___"

TEMP_MAIN_CONTENT=$(awk -v directive="$CP_UTILS_INCLUDE_DIRECTIVE" -v ph="$CP_UTILS_PLACEHOLDER" \
    -v main_file_name="$MAIN_CPP_FILE" '
    BEGIN { replaced_cp_utils=0 }
    $0 == directive {
        print ph;
        replaced_cp_utils=1;
        next;
    }
    { print }
    END {
        if (replaced_cp_utils == 0) {
            print "Warning: Include directive \"" directive "\" not found in " main_file_name ". Submission file might be incomplete." > "/dev/stderr"
        }
    }
' "$MAIN_CPP_FILE")


# Now, replace the CP_UTILS_PLACEHOLDER with the ESCAPED_AUGMENTED_CP_UTILS_CONTENT
awk -v ph="$CP_UTILS_PLACEHOLDER" -v header_content="$ESCAPED_AUGMENTED_CP_UTILS_CONTENT" '
    $0 == ph {
        printf "%s\n", header_content 
        next
    }
    { print }
' <<< "$TEMP_MAIN_CONTENT" > "$SUBMISSION_FILE"

echo "Successfully combined '$MAIN_CPP_FILE', '$CP_UTILS_HEADER_FILE', and '$DEBUG_UTILS_HEADER_FILE' into '$SUBMISSION_FILE'"
echo ""
echo "Reminder: Compile '$SUBMISSION_FILE' for online judges WITHOUT -DPRACTICE or -DLOCAL flags."
echo "Example: g++ -std=c++20 -O2 -Wall -DONLINE_JUDGE '$SUBMISSION_FILE' -o solution"