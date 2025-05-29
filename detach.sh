#!/bin/bash

# Script to detach cp_utils.hpp and debug_utils.hpp from a combined main.cpp file.
# It expects main.cpp to have been processed by the companion combine.sh script.

DEFAULT_MAIN_CPP_FILE="main.cpp"
MAIN_CPP_FILE=${1:-$DEFAULT_MAIN_CPP_FILE}

CP_UTILS_HEADER_FILE="cp_utils.hpp"
DEBUG_UTILS_HEADER_FILE="debug_utils.hpp"

CP_UTILS_INCLUDE_DIRECTIVE='#include "cp_utils.hpp"' 
# Or be more specific with comment if it was part of the original line:
# CP_UTILS_INCLUDE_DIRECTIVE='#include "cp_utils.hpp" // Core utilities, macros, and type aliases'
DEBUG_UTILS_INCLUDE_DIRECTIVE='#include "debug_utils.hpp"'
# Or be more specific:
# DEBUG_UTILS_INCLUDE_DIRECTIVE='#include "debug_utils.hpp" // Include the debug header'

MARKER_CP_UTILS_BEGIN="// --- BEGIN CP UTILS ---"
MARKER_CP_UTILS_END="// --- END CP UTILS ---"
MARKER_DEBUG_UTILS_BEGIN="// --- BEGIN DEBUG UTILS ---"
MARKER_DEBUG_UTILS_END="// --- END DEBUG UTILS ---"

# Check if the main file exists
if [ ! -f "$MAIN_CPP_FILE" ]; then
    echo "Error: Combined C++ file '$MAIN_CPP_FILE' not found."
    exit 1
fi

# Temporary files for extracted content
TEMP_DEBUG_UTILS_CONTENT=$(mktemp)
TEMP_CP_UTILS_CONTENT=$(mktemp)
TEMP_MAIN_LEFTOVER_CONTENT=$(mktemp)

# --- Extraction using awk ---

# 1. Extract debug_utils.hpp content
awk -v marker_begin="$MARKER_DEBUG_UTILS_BEGIN" -v marker_end="$MARKER_DEBUG_UTILS_END" \
    '
    $0 == marker_begin {in_block=1; next}
    $0 == marker_end {in_block=0; next}
    in_block {print}
    ' "$MAIN_CPP_FILE" > "$TEMP_DEBUG_UTILS_CONTENT"

# 2. Extract cp_utils.hpp content (which includes the debug block initially)
awk -v marker_begin="$MARKER_CP_UTILS_BEGIN" -v marker_end="$MARKER_CP_UTILS_END" \
    '
    $0 == marker_begin {in_block=1; next}
    $0 == marker_end {in_block=0; next}
    in_block {print}
    ' "$MAIN_CPP_FILE" > "$TEMP_CP_UTILS_CONTENT"

# 3. Extract main.cpp content (everything outside the CP_UTILS block)
# and insert the #include "cp_utils.hpp" directive where the block was.
awk -v marker_begin="$MARKER_CP_UTILS_BEGIN" -v marker_end="$MARKER_CP_UTILS_END" \
    -v include_directive="$CP_UTILS_INCLUDE_DIRECTIVE" \
    '
    $0 == marker_begin {in_block_to_skip=1; print include_directive; next}
    $0 == marker_end {in_block_to_skip=0; next}
    !in_block_to_skip {print}
    ' "$MAIN_CPP_FILE" > "$TEMP_MAIN_LEFTOVER_CONTENT"

# --- Post-processing and final file writing ---

# 4. Post-process extracted cp_utils.hpp content:
#    Replace the embedded debug_utils block with #include "debug_utils.hpp"
PROCESSED_CP_UTILS_CONTENT=$(mktemp)
awk -v marker_begin="$MARKER_DEBUG_UTILS_BEGIN" -v marker_end="$MARKER_DEBUG_UTILS_END" \
    -v include_directive="$DEBUG_UTILS_INCLUDE_DIRECTIVE" \
    '
    $0 == marker_begin {in_block_to_replace=1; print include_directive; next}
    $0 == marker_end {in_block_to_replace=0; next}
    !in_block_to_replace {print}
    ' "$TEMP_CP_UTILS_CONTENT" > "$PROCESSED_CP_UTILS_CONTENT"

# --- Overwrite original files ---
# Check if extraction yielded content before overwriting to prevent accidental empty files
# (basic check: if temp file for debug_utils is empty, maybe markers were not found)

if [ ! -s "$TEMP_DEBUG_UTILS_CONTENT" ]; then
    echo "Warning: No content extracted for '$DEBUG_UTILS_HEADER_FILE'. Check markers in '$MAIN_CPP_FILE'."
    # Decide if to proceed or exit. For now, we will not write an empty debug_utils.hpp
else
    mv "$TEMP_DEBUG_UTILS_CONTENT" "$DEBUG_UTILS_HEADER_FILE"
    echo "Detached and wrote '$DEBUG_UTILS_HEADER_FILE'"
fi

if [ ! -s "$PROCESSED_CP_UTILS_CONTENT" ]; then
    echo "Warning: No content processed for '$CP_UTILS_HEADER_FILE'. Check markers in '$MAIN_CPP_FILE'."
else
    mv "$PROCESSED_CP_UTILS_CONTENT" "$CP_UTILS_HEADER_FILE"
    echo "Detached and wrote '$CP_UTILS_HEADER_FILE'"
fi

if [ ! -s "$TEMP_MAIN_LEFTOVER_CONTENT" ]; then
    echo "Warning: Resulting main content for '$MAIN_CPP_FILE' is empty. Check markers."
    # This is more critical. If main becomes empty, something is wrong.
    # However, if the original main only had the include, it could be empty.
    # For now, allow it but warn.
    mv "$TEMP_MAIN_LEFTOVER_CONTENT" "$MAIN_CPP_FILE"
    echo "Detached and overwrote '$MAIN_CPP_FILE' (it might be empty if it only contained includes)."
else
    mv "$TEMP_MAIN_LEFTOVER_CONTENT" "$MAIN_CPP_FILE"
    echo "Detached and overwrote '$MAIN_CPP_FILE'"
fi

# Cleanup temporary files that were not moved (e.g., if extraction failed for one)
rm -f "$TEMP_DEBUG_UTILS_CONTENT" # Will fail harmlessly if already moved
rm -f "$TEMP_CP_UTILS_CONTENT"    # This one is intermediate, should always be removed
rm -f "$TEMP_MAIN_LEFTOVER_CONTENT" # Will fail harmlessly if already moved
rm -f "$PROCESSED_CP_UTILS_CONTENT" # Will fail harmlessly if already moved

echo "Detachment process complete." 