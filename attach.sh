#!/bin/bash

# Script to attach cp_utils.hpp (and debug_utils.hpp) into main.cpp, overwriting main.cpp.
# This version is intended for use with tools like CPH that expect a single main file.

# Default main C++ file, can be overridden by the first argument
DEFAULT_MAIN_CPP_FILE="main.cpp"
MAIN_CPP_FILE=${1:-$DEFAULT_MAIN_CPP_FILE}

CP_UTILS_HEADER_FILE="cp_utils.hpp"
DEBUG_UTILS_HEADER_FILE="debug_utils.hpp"

CP_UTILS_INCLUDE_DIRECTIVE='#include "cp_utils.hpp"'
# Exact match for the include line in main.cpp, comment included for specificity if needed:
# CP_UTILS_INCLUDE_DIRECTIVE='#include "cp_utils.hpp" // Core utilities, macros, and type aliases'

DEBUG_UTILS_INCLUDE_DIRECTIVE='#include "debug_utils.hpp"'
# Exact match for the include line in cp_utils.hpp, comment included for specificity if needed:
# DEBUG_UTILS_INCLUDE_DIRECTIVE='#include "debug_utils.hpp" // Include the debug header'

MARKER_CP_UTILS_BEGIN="// --- BEGIN CP UTILS ---"
MARKER_CP_UTILS_END="// --- END CP UTILS ---"
MARKER_DEBUG_UTILS_BEGIN="// --- BEGIN DEBUG UTILS ---"
MARKER_DEBUG_UTILS_END="// --- END DEBUG UTILS ---"

# Function to escape special characters for sed replacement
escape_sed_replacement() {
  # Escape &, \, and the delimiter /
  echo "$1" | sed -e 's/[&\\/]/\\\\&/g'
}

# Check if the necessary files exist
if [ ! -f "$MAIN_CPP_FILE" ]; then
    echo "Error: Main C++ file '$MAIN_CPP_FILE' not found."
    exit 1
fi

if [ ! -f "$CP_UTILS_HEADER_FILE" ]; then
    echo "Error: Core utilities header file '$CP_UTILS_HEADER_FILE' not found."
    exit 1
fi

if [ ! -f "$DEBUG_UTILS_HEADER_FILE" ]; then
    echo "Error: Debug utilities header file '$DEBUG_UTILS_HEADER_FILE' not found."
    exit 1
fi

# Create a temporary file
TEMP_ATTACHED_FILE=$(mktemp)
if [ -z "$TEMP_ATTACHED_FILE" ]; then
    echo "Error: Could not create temporary file."
    exit 1
fi

# 1. Read debug_utils.hpp content for embedding
# This content will be passed to awk as a variable.
DEBUG_UTILS_CONTENT_FOR_AWK=$(cat "$DEBUG_UTILS_HEADER_FILE")

# 2. Process cp_utils.hpp: embed debug_utils.hpp content where its include directive was.
# The output of this awk command is the full content of cp_utils.hpp, with the #include replaced.
CP_UTILS_WITH_DEBUG_EMBEDDED=$(awk \
    -v directive="$DEBUG_UTILS_INCLUDE_DIRECTIVE" \
    -v m_begin="$MARKER_DEBUG_UTILS_BEGIN" \
    -v content_to_embed="$DEBUG_UTILS_CONTENT_FOR_AWK" \
    -v m_end="$MARKER_DEBUG_UTILS_END" \
    '
    # This script processes cp_utils.hpp line by line.
    # When it finds the line matching 'directive', it replaces it with the marked content.
    # Otherwise, it prints the original line.
    BEGIN {found_directive=0}
    $0 ~ directive {
        print m_begin;
        print content_to_embed;
        print m_end;
        found_directive=1;
        next; # Move to next line of cp_utils.hpp after replacement
    }
    {print} # Print the current line from cp_utils.hpp if no match
    END {
        if (found_directive == 0 && NR > 0) {
            # This means the file was read but the directive was not found.
            # The original content of cp_utils.hpp would have been printed line by line.
            # For safety, one might choose to exit or use original cp_utils.hpp if directive is critical.
            # echo "Warning: Directive '$DEBUG_UTILS_INCLUDE_DIRECTIVE' not found in '$CP_UTILS_HEADER_FILE'. Debug content not embedded as expected." > /dev/stderr
        }
    }
' "$CP_UTILS_HEADER_FILE")

# Error check after processing cp_utils.hpp
if [ -z "$CP_UTILS_WITH_DEBUG_EMBEDDED" ] && [ -s "$CP_UTILS_HEADER_FILE" ]; then
    # If cp_utils.hpp was not empty but the result is, something went wrong with awk.
    echo "Error: Processing '$CP_UTILS_HEADER_FILE' for debug embedding resulted in empty content."
    rm -f "$TEMP_ATTACHED_FILE"
    exit 1
fi

# 3. Process main.cpp: embed the augmented cp_utils.hpp content where its include directive was.
awk \
    -v directive="$CP_UTILS_INCLUDE_DIRECTIVE" \
    -v m_begin="$MARKER_CP_UTILS_BEGIN" \
    -v content_to_embed="$CP_UTILS_WITH_DEBUG_EMBEDDED" \
    -v m_end="$MARKER_CP_UTILS_END" \
    '
    BEGIN {found_directive=0}
    $0 ~ directive {
        print m_begin;
        print content_to_embed;
        print m_end;
        found_directive=1;
        next;
    }
    {print}
    END {
        if (found_directive == 0 && NR > 0) {
            # echo "Warning: Directive '$CP_UTILS_INCLUDE_DIRECTIVE' not found in '$MAIN_CPP_FILE'. File may not be correctly combined." > /dev/stderr
        }
    }
' "$MAIN_CPP_FILE" > "$TEMP_ATTACHED_FILE"


# Final checks and move
if [ $? -ne 0 ]; then 
    echo "Error: awk processing failed for '$MAIN_CPP_FILE'."
    rm -f "$TEMP_ATTACHED_FILE"; exit 1; 
fi

# Check if the output file is empty, which might happen if main.cpp was empty or directive not found.
# If main.cpp was empty, TEMP_ATTACHED_FILE will be empty. This is valid.
# If main.cpp was not empty, but TEMP_ATTACHED_FILE is, it implies directive was not found and no lines printed.
# The awk script prints lines even if directive is not found, so this check is more about awk failure.
if [ ! -s "$TEMP_ATTACHED_FILE" ] && [ -s "$MAIN_CPP_FILE" ]; then 
    echo "Error: Attaching process resulted in an empty file, but '$MAIN_CPP_FILE' was not empty."
    if ! grep -qF "$CP_UTILS_INCLUDE_DIRECTIVE" "$MAIN_CPP_FILE"; then
        echo "Note: The directive '$CP_UTILS_INCLUDE_DIRECTIVE' was not found in '$MAIN_CPP_FILE'. '$MAIN_CPP_FILE' was not changed."
    fi
    rm -f "$TEMP_ATTACHED_FILE"; exit 1; 
fi

mv "$TEMP_ATTACHED_FILE" "$MAIN_CPP_FILE"

echo "Successfully attached sources into '$MAIN_CPP_FILE' (overwritten)."

# Cleanup: mktemp should handle removal on script exit or signal, but explicit is fine too.
# However, mv replaces the need for explicit removal of TEMP_ATTACHED_FILE if successful. 