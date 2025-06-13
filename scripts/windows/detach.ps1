# PowerShell script to detach cp_utils.hpp and debug_utils.hpp from a combined main.cpp file.
# It expects main.cpp to have been processed by the companion attach.ps1 script.

param(
    [string]$MainCppFile
)

# If no file specified, use the current working directory's main.cpp
if (-not $MainCppFile) {
    $MainCppFile = "main.cpp"
}

# Determine paths relative to the main file's location
$mainFileDir = Split-Path -Parent (Resolve-Path $MainCppFile -ErrorAction SilentlyContinue)
if (-not $mainFileDir) {
    $mainFileDir = Split-Path -Parent $MainCppFile
    if (-not $mainFileDir) {
        $mainFileDir = "."
    }
}

# Calculate relative paths to include directory from main file's location
$CP_UTILS_HEADER_FILE = Join-Path $mainFileDir "include/cp_utils.hpp"
$DEBUG_UTILS_HEADER_FILE = Join-Path $mainFileDir "include/debug_utils.hpp"

# If files don't exist with relative path, try from script directory
if (-not (Test-Path $CP_UTILS_HEADER_FILE)) {
    $CP_UTILS_HEADER_FILE = "../include/cp_utils.hpp"
    $DEBUG_UTILS_HEADER_FILE = "../include/debug_utils.hpp"
}

$CP_UTILS_INCLUDE_DIRECTIVE = '#include "include/cp_utils.hpp"'
$DEBUG_UTILS_INCLUDE_DIRECTIVE = '#include "debug_utils.hpp"'

$MARKER_CP_UTILS_BEGIN = "// --- BEGIN CP UTILS ---"
$MARKER_CP_UTILS_END = "// --- END CP UTILS ---"
$MARKER_DEBUG_UTILS_BEGIN = "// --- BEGIN DEBUG UTILS ---"
$MARKER_DEBUG_UTILS_END = "// --- END DEBUG UTILS ---"

# Check if the main file exists
if (-not (Test-Path $MainCppFile)) {
    Write-Error "Error: Combined C++ file '$MainCppFile' not found."
    exit 1
}

try {
    $main_content = Get-Content $MainCppFile

    # 1. Extract debug_utils.hpp content
    $debug_content = ""
    $in_debug_block = $false
    
    foreach ($line in $main_content) {
        if ($line -eq $MARKER_DEBUG_UTILS_BEGIN) {
            $in_debug_block = $true
            continue
        }
        if ($line -eq $MARKER_DEBUG_UTILS_END) {
            $in_debug_block = $false
            continue
        }
        if ($in_debug_block) {
            $debug_content += $line + "`n"
        }
    }

    # 2. Extract cp_utils.hpp content (which includes the debug block initially)
    $cp_utils_content = ""
    $in_cp_utils_block = $false
    
    foreach ($line in $main_content) {
        if ($line -eq $MARKER_CP_UTILS_BEGIN) {
            $in_cp_utils_block = $true
            continue
        }
        if ($line -eq $MARKER_CP_UTILS_END) {
            $in_cp_utils_block = $false
            continue
        }
        if ($in_cp_utils_block) {
            $cp_utils_content += $line + "`n"
        }
    }

    # 3. Extract main.cpp content (everything outside the CP_UTILS block)
    # and insert the #include "cp_utils.hpp" directive where the block was
    $main_leftover_content = ""
    $in_cp_utils_block_to_skip = $false
    
    foreach ($line in $main_content) {
        if ($line -eq $MARKER_CP_UTILS_BEGIN) {
            $in_cp_utils_block_to_skip = $true
            $main_leftover_content += $CP_UTILS_INCLUDE_DIRECTIVE + "`n"
            continue
        }
        if ($line -eq $MARKER_CP_UTILS_END) {
            $in_cp_utils_block_to_skip = $false
            continue
        }
        if (-not $in_cp_utils_block_to_skip) {
            $main_leftover_content += $line + "`n"
        }
    }

    # 4. Post-process extracted cp_utils.hpp content:
    # Replace the embedded debug_utils block with #include "debug_utils.hpp"
    $processed_cp_utils_content = ""
    $in_debug_block_to_replace = $false
    
    $cp_utils_lines = $cp_utils_content -split "`n"
    foreach ($line in $cp_utils_lines) {
        if ($line -eq $MARKER_DEBUG_UTILS_BEGIN) {
            $in_debug_block_to_replace = $true
            $processed_cp_utils_content += $DEBUG_UTILS_INCLUDE_DIRECTIVE + "`n"
            continue
        }
        if ($line -eq $MARKER_DEBUG_UTILS_END) {
            $in_debug_block_to_replace = $false
            continue
        }
        if (-not $in_debug_block_to_replace) {
            $processed_cp_utils_content += $line + "`n"
        }
    }

    # --- Overwrite original files ---
    # Check if extraction yielded content before overwriting

    if ($debug_content.Trim()) {
        $debug_content | Out-File -FilePath $DEBUG_UTILS_HEADER_FILE -Encoding UTF8 -NoNewline
        Write-Output "Detached and wrote '$DEBUG_UTILS_HEADER_FILE'"
    } else {
        Write-Warning "Warning: No content extracted for '$DEBUG_UTILS_HEADER_FILE'. Check markers in '$MainCppFile'."
    }

    if ($processed_cp_utils_content.Trim()) {
        $processed_cp_utils_content | Out-File -FilePath $CP_UTILS_HEADER_FILE -Encoding UTF8 -NoNewline
        Write-Output "Detached and wrote '$CP_UTILS_HEADER_FILE'"
    } else {
        Write-Warning "Warning: No content processed for '$CP_UTILS_HEADER_FILE'. Check markers in '$MainCppFile'."
    }

    if ($main_leftover_content.Trim() -or $main_leftover_content.Length -eq 0) {
        $main_leftover_content | Out-File -FilePath $MainCppFile -Encoding UTF8 -NoNewline
        if ($main_leftover_content.Trim()) {
            Write-Output "Detached and overwrote '$MainCppFile'"
        } else {
            Write-Warning "Detached and overwrote '$MainCppFile' (it might be empty if it only contained includes)."
        }
    } else {
        Write-Warning "Warning: Resulting main content for '$MainCppFile' is empty. Check markers."
    }

    Write-Output "Detachment process complete."

} catch {
    Write-Error "Error occurred during processing: $($_.Exception.Message)"
    exit 1
} 