# PowerShell script to attach cp_utils.hpp (and debug_utils.hpp) into main.cpp, overwriting main.cpp.
# This version is intended for use with tools like CPH that expect a single main file.

param(
    [string]$MainCppFile = "main.cpp"
)

$CP_UTILS_HEADER_FILE = "cp_utils.hpp"
$DEBUG_UTILS_HEADER_FILE = "debug_utils.hpp"

$CP_UTILS_INCLUDE_DIRECTIVE = '#include "cp_utils.hpp"'
$DEBUG_UTILS_INCLUDE_DIRECTIVE = '#include "debug_utils.hpp"'

$MARKER_CP_UTILS_BEGIN = "// --- BEGIN CP UTILS ---"
$MARKER_CP_UTILS_END = "// --- END CP UTILS ---"
$MARKER_DEBUG_UTILS_BEGIN = "// --- BEGIN DEBUG UTILS ---"
$MARKER_DEBUG_UTILS_END = "// --- END DEBUG UTILS ---"

# Check if the necessary files exist
if (-not (Test-Path $MainCppFile)) {
    Write-Error "Error: Main C++ file '$MainCppFile' not found."
    exit 1
}

if (-not (Test-Path $CP_UTILS_HEADER_FILE)) {
    Write-Error "Error: Core utilities header file '$CP_UTILS_HEADER_FILE' not found."
    exit 1
}

if (-not (Test-Path $DEBUG_UTILS_HEADER_FILE)) {
    Write-Error "Error: Debug utilities header file '$DEBUG_UTILS_HEADER_FILE' not found."
    exit 1
}

# Create a temporary file
$TEMP_ATTACHED_FILE = [System.IO.Path]::GetTempFileName()

try {
    # 1. Read debug_utils.hpp content for embedding
    $DEBUG_UTILS_CONTENT = Get-Content $DEBUG_UTILS_HEADER_FILE -Raw

    # 2. Process cp_utils.hpp: embed debug_utils.hpp content where its include directive was
    $CP_UTILS_WITH_DEBUG_EMBEDDED = ""
    $found_directive = $false
    
    $cp_utils_lines = Get-Content $CP_UTILS_HEADER_FILE
    foreach ($line in $cp_utils_lines) {
        if ($line -eq $DEBUG_UTILS_INCLUDE_DIRECTIVE) {
            $CP_UTILS_WITH_DEBUG_EMBEDDED += $MARKER_DEBUG_UTILS_BEGIN + "`n"
            $CP_UTILS_WITH_DEBUG_EMBEDDED += $DEBUG_UTILS_CONTENT + "`n"
            $CP_UTILS_WITH_DEBUG_EMBEDDED += $MARKER_DEBUG_UTILS_END + "`n"
            $found_directive = $true
        } else {
            $CP_UTILS_WITH_DEBUG_EMBEDDED += $line + "`n"
        }
    }

    # Error check after processing cp_utils.hpp
    if (-not $CP_UTILS_WITH_DEBUG_EMBEDDED -and (Get-Item $CP_UTILS_HEADER_FILE).Length -gt 0) {
        Write-Error "Error: Processing '$CP_UTILS_HEADER_FILE' for debug embedding resulted in empty content."
        exit 1
    }

    # 3. Process main.cpp: embed the augmented cp_utils.hpp content where its include directive was
    $result_content = ""
    $found_main_directive = $false
    
    $main_lines = Get-Content $MainCppFile
    foreach ($line in $main_lines) {
        if ($line -eq $CP_UTILS_INCLUDE_DIRECTIVE) {
            $result_content += $MARKER_CP_UTILS_BEGIN + "`n"
            $result_content += $CP_UTILS_WITH_DEBUG_EMBEDDED + "`n"
            $result_content += $MARKER_CP_UTILS_END + "`n"
            $found_main_directive = $true
        } else {
            $result_content += $line + "`n"
        }
    }

    # Final checks
    if (-not $result_content -and (Get-Item $MainCppFile).Length -gt 0) {
        Write-Error "Error: Attaching process resulted in an empty file, but '$MainCppFile' was not empty."
        if (-not ($main_lines -contains $CP_UTILS_INCLUDE_DIRECTIVE)) {
            Write-Warning "Note: The directive '$CP_UTILS_INCLUDE_DIRECTIVE' was not found in '$MainCppFile'. '$MainCppFile' was not changed."
        }
        exit 1
    }

    # Write result to temporary file, then move to replace original
    $result_content | Out-File -FilePath $TEMP_ATTACHED_FILE -Encoding UTF8 -NoNewline

    # Replace original file
    Move-Item $TEMP_ATTACHED_FILE $MainCppFile -Force

    Write-Output "Successfully attached sources into '$MainCppFile' (overwritten)."

} catch {
    Write-Error "Error occurred during processing: $($_.Exception.Message)"
    if (Test-Path $TEMP_ATTACHED_FILE) {
        Remove-Item $TEMP_ATTACHED_FILE
    }
    exit 1
} 