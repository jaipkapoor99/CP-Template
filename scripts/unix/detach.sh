#!/bin/bash

# Bash script to detach cp_utils.hpp and debug_utils.hpp from a combined main.cpp file.
# It expects main.cpp to have been processed by the companion attach.sh script.

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

# Check if the main file exists
if [ ! -f "$MAIN_CPP_FILE" ]; then
    echo "Error: Combined C++ file '$MAIN_CPP_FILE' not found." >&2
    exit 1
fi

# 1. Extract debug_utils.hpp content
debug_content=""
in_debug_block=false

while IFS= read -r line; do
    if [ "$line" = "$MARKER_DEBUG_UTILS_BEGIN" ]; then
        in_debug_block=true
        continue
    fi
    if [ "$line" = "$MARKER_DEBUG_UTILS_END" ]; then
        in_debug_block=false
        continue
    fi
    if [ "$in_debug_block" = true ]; then
        debug_content+="$line"$'\n'
    fi
done < "$MAIN_CPP_FILE"

# 2. Extract cp_utils.hpp content (which includes the debug block initially)
cp_utils_content=""
in_cp_utils_block=false

while IFS= read -r line; do
    if [ "$line" = "$MARKER_CP_UTILS_BEGIN" ]; then
        in_cp_utils_block=true
        continue
    fi
    if [ "$line" = "$MARKER_CP_UTILS_END" ]; then
        in_cp_utils_block=false
        continue
    fi
    if [ "$in_cp_utils_block" = true ]; then
        cp_utils_content+="$line"$'\n'
    fi
done < "$MAIN_CPP_FILE"

# 3. Extract main.cpp content (everything outside the CP_UTILS block)
# and insert the #include "cp_utils.hpp" directive where the block was
main_leftover_content=""
in_cp_utils_block_to_skip=false

while IFS= read -r line; do
    if [ "$line" = "$MARKER_CP_UTILS_BEGIN" ]; then
        in_cp_utils_block_to_skip=true
        main_leftover_content+="$CP_UTILS_INCLUDE_DIRECTIVE"$'\n'
        continue
    fi
    if [ "$line" = "$MARKER_CP_UTILS_END" ]; then
        in_cp_utils_block_to_skip=false
        continue
    fi
    if [ "$in_cp_utils_block_to_skip" = false ]; then
        main_leftover_content+="$line"$'\n'
    fi
done < "$MAIN_CPP_FILE"

# 4. Post-process extracted cp_utils.hpp content:
# Replace the embedded debug_utils block with #include "debug_utils.hpp"
processed_cp_utils_content=""
in_debug_block_to_replace=false

while IFS= read -r line; do
    if [ "$line" = "$MARKER_DEBUG_UTILS_BEGIN" ]; then
        in_debug_block_to_replace=true
        processed_cp_utils_content+="$DEBUG_UTILS_INCLUDE_DIRECTIVE"$'\n'
        continue
    fi
    if [ "$line" = "$MARKER_DEBUG_UTILS_END" ]; then
        in_debug_block_to_replace=false
        continue
    fi
    if [ "$in_debug_block_to_replace" = false ]; then
        processed_cp_utils_content+="$line"$'\n'
    fi
done <<< "$cp_utils_content"

# --- Overwrite original files ---
# Check if extraction yielded content before overwriting

if [ -n "${debug_content// }" ]; then
    printf "%s" "$debug_content" > "$DEBUG_UTILS_HEADER_FILE"
    echo "Detached and wrote '$DEBUG_UTILS_HEADER_FILE'"
else
    echo "Warning: No content extracted for '$DEBUG_UTILS_HEADER_FILE'. Check markers in '$MAIN_CPP_FILE'." >&2
fi

if [ -n "${processed_cp_utils_content// }" ]; then
    printf "%s" "$processed_cp_utils_content" > "$CP_UTILS_HEADER_FILE"
    echo "Detached and wrote '$CP_UTILS_HEADER_FILE'"
else
    echo "Warning: No content processed for '$CP_UTILS_HEADER_FILE'. Check markers in '$MAIN_CPP_FILE'." >&2
fi

if [ -n "${main_leftover_content// }" ] || [ ${#main_leftover_content} -eq 0 ]; then
    printf "%s" "$main_leftover_content" > "$MAIN_CPP_FILE"
    if [ -n "${main_leftover_content// }" ]; then
        echo "Detached and overwrote '$MAIN_CPP_FILE'"
    else
        echo "Detached and overwrote '$MAIN_CPP_FILE' (it might be empty if it only contained includes)." >&2
    fi
else
    echo "Warning: Resulting main content for '$MAIN_CPP_FILE' is empty. Check markers." >&2
fi

echo "Detachment process complete." 