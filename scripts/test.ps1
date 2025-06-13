# PowerShell script for stress testing C++ competitive programming solutions

param(
    [int]$NumTests = 100
)

# --- Configuration ---
$COMPILER = "g++"
$STD_VERSION = "c++20"
$OPTIMIZATION_LEVEL = "-O2"
$WARNING_FLAGS = "-Wall"
$PRACTICE_DEFINE = "-DPRACTICE" # Enables asserts and internal brute-force checks
$LOCAL_DEFINE = "-DLOCAL"       # Enables TRACE and DEBUG macros (optional)
$SOURCE_FILE = "../src/main.cpp"
$EXECUTABLE_NAME = "my_solution"
$BRUTE_EXECUTABLE_NAME = "brute_solution"
$INPUT_FILE = "input.txt"
$OUTPUT_FILE = "output.txt"
$BRUTE_OUTPUT_FILE = "brute_output.txt"

# Test case generator configuration
$GENERATOR_TYPE = "inline" # "inline" or "python"
$PYTHON_GENERATOR_SCRIPT = "generate_input.py"

# Set to $true to keep input/output files on failure for debugging
$KEEP_FILES_ON_FAILURE = $true

# Brute force comparison mode
$USE_BRUTE_FORCE_COMPARISON = $true # Set to $false to use internal ASSERT-based checking only

# --- Compilation ---
Write-Output "Compiling $SOURCE_FILE..."

$compileArgs = @(
    "-std=$STD_VERSION",
    $OPTIMIZATION_LEVEL,
    $WARNING_FLAGS,
    $PRACTICE_DEFINE,
    $LOCAL_DEFINE,
    $SOURCE_FILE,
    "-o",
    "$EXECUTABLE_NAME.exe"
)

$compileProcess = Start-Process -FilePath $COMPILER -ArgumentList $compileArgs -Wait -PassThru -NoNewWindow

# Check if compilation was successful
if ($compileProcess.ExitCode -ne 0) {
    Write-Error "Compilation failed!"
    exit 1
}
Write-Output "Compilation successful."

# --- Compile Brute Force Solution (if using brute force comparison) ---
if ($USE_BRUTE_FORCE_COMPARISON) {
    # Check if brute force source exists
    $BRUTE_SOURCE_FILE = "brute.cpp"
    if (-not (Test-Path $BRUTE_SOURCE_FILE)) {
        Write-Warning "Brute force comparison enabled but '$BRUTE_SOURCE_FILE' not found."
        Write-Output "Creating template brute force file '$BRUTE_SOURCE_FILE'..."
        
        $bruteTemplate = @'
#include "../include/cp_utils.hpp"

// TODO: Implement your brute force solution here
// This should solve the same problem as main.cpp but with a simpler, slower approach
void solve_brute(int test_case_num) 
{
    int n;
    read(n);
    
    // Example brute force: sum 1 to n using a loop instead of formula
    ll result = 0;
    for (int i = 1; i <= n; i++) {
        result += i;
    }
    
    print(result);
}

int main()
{
    FASTINOUT;
    int t;
    read(t);
    
    f(i, 0, t)
        solve_brute(i + 1);
        
    return 0;
}
'@
        $bruteTemplate | Out-File -FilePath $BRUTE_SOURCE_FILE -Encoding UTF8
        Write-Output "Template brute force file created. Please implement your brute force logic."
    }
    
    Write-Output "Compiling brute force solution..."
    $brutCompileArgs = @(
        "-std=$STD_VERSION",
        $OPTIMIZATION_LEVEL,
        $WARNING_FLAGS,
        $PRACTICE_DEFINE,
        $LOCAL_DEFINE,
        $BRUTE_SOURCE_FILE,
        "-o",
        "$BRUTE_EXECUTABLE_NAME.exe"
    )
    
    $bruteCompileProcess = Start-Process -FilePath $COMPILER -ArgumentList $brutCompileArgs -Wait -PassThru -NoNewWindow
    
    if ($bruteCompileProcess.ExitCode -ne 0) {
        Write-Error "Brute force compilation failed!"
        exit 1
    }
    Write-Output "Brute force compilation successful."
}

# --- Stress Testing ---
Write-Output "Running $NumTests stress tests..."
$PASSED_COUNT = 0

for ($i = 1; $i -le $NumTests; $i++) {
    Write-Host "Test ${i}/${NumTests}: " -NoNewline

    # Generate test case
    if ($GENERATOR_TYPE -eq "python") {
        if (-not (Test-Path $PYTHON_GENERATOR_SCRIPT)) {
            Write-Output "Python generator script '$PYTHON_GENERATOR_SCRIPT' not found!"
            Write-Output "Creating placeholder $PYTHON_GENERATOR_SCRIPT..."
            
            $pythonTemplate = @'
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
'@
            $pythonTemplate | Out-File -FilePath $PYTHON_GENERATOR_SCRIPT -Encoding UTF8
        }
        
        $pythonProcess = Start-Process -FilePath "python" -ArgumentList $PYTHON_GENERATOR_SCRIPT -Wait -PassThru -NoNewWindow -RedirectStandardOutput $INPUT_FILE
        if ($pythonProcess.ExitCode -ne 0) {
            Write-Error "Input generation failed!"
            if (-not $KEEP_FILES_ON_FAILURE) {
                Remove-Item -Path "$EXECUTABLE_NAME.exe", "$BRUTE_EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE -ErrorAction SilentlyContinue
            }
            exit 1
        }
    } else {
        # Inline generator - generates a random number N between 1 and 1000
        # TODO: Customize this inline generator for your problem
        $testCases = Get-Random -Minimum 1 -Maximum 4  # Random number of test cases (1-3)
        $inputContent = "$testCases`n"
        for ($tc = 1; $tc -le $testCases; $tc++) {
            $N = Get-Random -Minimum 1 -Maximum 1001
            $inputContent += "$N`n"
        }
        $inputContent | Out-File -FilePath $INPUT_FILE -Encoding UTF8 -NoNewline
    }

    # Run the main solution
    try {
        $solutionProcess = Start-Process -FilePath ".\$EXECUTABLE_NAME.exe" -Wait -PassThru -NoNewWindow -RedirectStandardInput $INPUT_FILE -RedirectStandardOutput $OUTPUT_FILE -RedirectStandardError "NUL"
        
        # Check for runtime errors
        if ($solutionProcess.ExitCode -ne 0) {
            Write-Error "Main solution runtime error!"
            Write-Output "Input:"
            Get-Content $INPUT_FILE
            if (-not $KEEP_FILES_ON_FAILURE) {
                Remove-Item -Path "$EXECUTABLE_NAME.exe", "$BRUTE_EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE -ErrorAction SilentlyContinue
            }
            exit 1
        }
    } catch {
        Write-Error "Failed to run main solution: $($_.Exception.Message)"
        if (-not $KEEP_FILES_ON_FAILURE) {
            Remove-Item -Path "$EXECUTABLE_NAME.exe", "$BRUTE_EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE -ErrorAction SilentlyContinue
        }
        exit 1
    }

    # Run brute force comparison if enabled
    if ($USE_BRUTE_FORCE_COMPARISON) {
        try {
            $bruteProcess = Start-Process -FilePath ".\$BRUTE_EXECUTABLE_NAME.exe" -Wait -PassThru -NoNewWindow -RedirectStandardInput $INPUT_FILE -RedirectStandardOutput $BRUTE_OUTPUT_FILE -RedirectStandardError "NUL"
            
            if ($bruteProcess.ExitCode -ne 0) {
                Write-Error "Brute force solution runtime error!"
                Write-Output "Input:"
                Get-Content $INPUT_FILE
                if (-not $KEEP_FILES_ON_FAILURE) {
                    Remove-Item -Path "$EXECUTABLE_NAME.exe", "$BRUTE_EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE -ErrorAction SilentlyContinue
                }
                exit 1
            }
        } catch {
            Write-Error "Failed to run brute force solution: $($_.Exception.Message)"
            if (-not $KEEP_FILES_ON_FAILURE) {
                Remove-Item -Path "$EXECUTABLE_NAME.exe", "$BRUTE_EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE -ErrorAction SilentlyContinue
            }
            exit 1
        }

        # Compare outputs
        $mainOutput = Get-Content $OUTPUT_FILE -Raw
        $bruteOutput = Get-Content $BRUTE_OUTPUT_FILE -Raw
        
        # Normalize whitespace for comparison
        $mainOutput = $mainOutput.Trim() -replace '\r\n', "`n" -replace '\r', "`n"
        $bruteOutput = $bruteOutput.Trim() -replace '\r\n', "`n" -replace '\r', "`n"
        
        if ($mainOutput -ne $bruteOutput) {
            Write-Error "Output mismatch!"
            Write-Output "Input:"
            Get-Content $INPUT_FILE
            Write-Output "Main solution output:"
            Write-Output $mainOutput
            Write-Output "Brute force output:"
            Write-Output $bruteOutput
            if (-not $KEEP_FILES_ON_FAILURE) {
                Remove-Item -Path "$EXECUTABLE_NAME.exe", "$BRUTE_EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE -ErrorAction SilentlyContinue
            }
            exit 1
        }
    }

    Write-Output "Passed."
    $PASSED_COUNT++
}

Write-Output ""
Write-Output "All $PASSED_COUNT/$NumTests tests passed successfully!"

# --- Cleanup ---
if ($KEEP_FILES_ON_FAILURE -and ($PASSED_COUNT -ne $NumTests)) {
    Write-Output "Files kept for debugging: $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE"
} else {
    Remove-Item -Path "$EXECUTABLE_NAME.exe", "$BRUTE_EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE -ErrorAction SilentlyContinue
    # Optionally remove the python generator if it was auto-created and you don't want to keep it
    # if ((Test-Path $PYTHON_GENERATOR_SCRIPT) -and (Get-Content $PYTHON_GENERATOR_SCRIPT -Raw).Contains("Example: Generate a random number N")) {
    #     Remove-Item -Path $PYTHON_GENERATOR_SCRIPT -ErrorAction SilentlyContinue
    # }
}

exit 0 