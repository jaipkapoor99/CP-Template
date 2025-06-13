#!/bin/bash

# Bash script to attach cp_utils.hpp (and debug_utils.hpp) into main.cpp, overwriting main.cpp.
# This version is intended for use with tools like CPH that expect a single main file.

set -e  # Exit on any error

MAIN_CPP_FILE="$1"

# If no file specified, find the first .cpp file other than main.cpp
if [ -z "$MAIN_CPP_FILE" ]; then
    # Find all .cpp files excluding main.cpp
    mapfile -t cpp_files < <(find . -maxdepth 1 -name "*.cpp" ! -name "main.cpp" -printf "%f\n" 2>/dev/null | sort)
    
    if [ ${#cpp_files[@]} -gt 0 ]; then
        MAIN_CPP_FILE="${cpp_files[0]}"
        echo -e "\033[36mNo file specified. Auto-targeting: $MAIN_CPP_FILE\033[0m"
    else
        MAIN_CPP_FILE="main.cpp"
        echo -e "\033[33mNo other .cpp files found. Targeting: $MAIN_CPP_FILE\033[0m"
    fi
fi

# Determine paths relative to the main file's location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
MAIN_FILE_DIR="$(dirname "$(realpath "$MAIN_CPP_FILE" 2>/dev/null || echo "$MAIN_CPP_FILE")")"

# Determine header file paths based on main file location
if [ "$(realpath "$MAIN_FILE_DIR" 2>/dev/null || echo "$MAIN_FILE_DIR")" = "$(realpath "$PROJECT_ROOT" 2>/dev/null || echo "$PROJECT_ROOT")" ]; then
    # File is in root - use direct paths
    CP_UTILS_HEADER_FILE="$PROJECT_ROOT/include/cp_utils.hpp"
    DEBUG_UTILS_HEADER_FILE="$PROJECT_ROOT/include/debug_utils.hpp"
    CP_UTILS_INCLUDE_DIRECTIVE='#include "include/cp_utils.hpp"'
else
    # File is in subdirectory - use relative paths
    CP_UTILS_HEADER_FILE="$MAIN_FILE_DIR/../include/cp_utils.hpp"
    DEBUG_UTILS_HEADER_FILE="$MAIN_FILE_DIR/../include/debug_utils.hpp"
    CP_UTILS_INCLUDE_DIRECTIVE='#include "../include/cp_utils.hpp"'
fi

DEBUG_UTILS_INCLUDE_DIRECTIVE='#include "debug_utils.hpp"'

MARKER_CP_UTILS_BEGIN="// --- BEGIN CP UTILS ---"
MARKER_CP_UTILS_END="// --- END CP UTILS ---"
MARKER_DEBUG_UTILS_BEGIN="// --- BEGIN DEBUG UTILS ---"
MARKER_DEBUG_UTILS_END="// --- END DEBUG UTILS ---"

# Check if the necessary files exist
if [ ! -f "$MAIN_CPP_FILE" ]; then
    echo "Error: Main C++ file '$MAIN_CPP_FILE' not found." >&2
    exit 1
fi

if [ ! -f "$CP_UTILS_HEADER_FILE" ]; then
    echo "Error: Core utilities header file '$CP_UTILS_HEADER_FILE' not found." >&2
    exit 1
fi

if [ ! -f "$DEBUG_UTILS_HEADER_FILE" ]; then
    echo "Error: Debug utilities header file '$DEBUG_UTILS_HEADER_FILE' not found." >&2
    exit 1
fi

# 1. Read debug_utils.hpp content for embedding
DEBUG_UTILS_CONTENT="$(cat "$DEBUG_UTILS_HEADER_FILE")"

# 2. Process cp_utils.hpp: embed debug_utils.hpp content where its include directive was
CP_UTILS_WITH_DEBUG_EMBEDDED=""

while IFS= read -r line; do
    # Replace debug include line with actual debug content
    if [ "$line" = "$DEBUG_UTILS_INCLUDE_DIRECTIVE" ]; then
        CP_UTILS_WITH_DEBUG_EMBEDDED+="$MARKER_DEBUG_UTILS_BEGIN"$'\n'
        CP_UTILS_WITH_DEBUG_EMBEDDED+="$DEBUG_UTILS_CONTENT"$'\n'
        CP_UTILS_WITH_DEBUG_EMBEDDED+="$MARKER_DEBUG_UTILS_END"$'\n'
    else
        CP_UTILS_WITH_DEBUG_EMBEDDED+="$line"$'\n'
    fi
done < "$CP_UTILS_HEADER_FILE"

# Error check after processing cp_utils.hpp
if [ -z "$CP_UTILS_WITH_DEBUG_EMBEDDED" ] && [ -s "$CP_UTILS_HEADER_FILE" ]; then
    echo "Error: Processing '$CP_UTILS_HEADER_FILE' for debug embedding resulted in empty content." >&2
    exit 1
fi

# 3. Process main.cpp: embed the augmented cp_utils.hpp content where its include directive was
result_content=""

while IFS= read -r line; do
    if [ "$line" = "$CP_UTILS_INCLUDE_DIRECTIVE" ]; then
        result_content+="$MARKER_CP_UTILS_BEGIN"$'\n'
        result_content+="$CP_UTILS_WITH_DEBUG_EMBEDDED"$'\n'
        result_content+="$MARKER_CP_UTILS_END"$'\n'
    else
        result_content+="$line"$'\n'
    fi
done < "$MAIN_CPP_FILE"

# Final checks
if [ -z "$result_content" ] && [ -s "$MAIN_CPP_FILE" ]; then
    echo "Error: Attaching process resulted in an empty file, but '$MAIN_CPP_FILE' was not empty." >&2
    if ! grep -Fxq "$CP_UTILS_INCLUDE_DIRECTIVE" "$MAIN_CPP_FILE"; then
        echo "Note: The directive '$CP_UTILS_INCLUDE_DIRECTIVE' was not found in '$MAIN_CPP_FILE'. '$MAIN_CPP_FILE' was not changed." >&2
    fi
    exit 1
fi

# Write result directly to the main file
printf "%s" "$result_content" > "$MAIN_CPP_FILE"

echo "Successfully attached sources into '$MAIN_CPP_FILE' (modified in-place)." 