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
$SOURCE_FILE = "main.cpp"
$EXECUTABLE_NAME = "my_solution"
$INPUT_FILE = "input.txt"
$OUTPUT_FILE = "output.txt"
$BRUTE_OUTPUT_FILE = "brute_output.txt" # If using a separate brute force solution

# Test case generator configuration
$GENERATOR_TYPE = "inline" # "inline" or "python"
$PYTHON_GENERATOR_SCRIPT = "generate_input.py"

# Set to $true to keep input/output files on failure for debugging
$KEEP_FILES_ON_FAILURE = $true

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
                Remove-Item -Path "$EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE -ErrorAction SilentlyContinue
            }
            exit 1
        }
    } else {
        # Inline generator - generates a random number N between 1 and 1000
        # TODO: Customize this inline generator for your problem
        $N = Get-Random -Minimum 1 -Maximum 1001
        $N | Out-File -FilePath $INPUT_FILE -Encoding UTF8
    }

    # Run the solution
    try {
        $solutionProcess = Start-Process -FilePath ".\$EXECUTABLE_NAME.exe" -Wait -PassThru -NoNewWindow -RedirectStandardInput $INPUT_FILE -RedirectStandardOutput $OUTPUT_FILE -RedirectStandardError "NUL"
        
        # Check for runtime errors
        if ($solutionProcess.ExitCode -ne 0) {
            Write-Error "Runtime error!"
            Write-Output "Input:"
            Get-Content $INPUT_FILE
            if (-not $KEEP_FILES_ON_FAILURE) {
                Remove-Item -Path "$EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE -ErrorAction SilentlyContinue
            }
            exit 1
        }
    } catch {
        Write-Error "Failed to run solution: $($_.Exception.Message)"
        if (-not $KEEP_FILES_ON_FAILURE) {
            Remove-Item -Path "$EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE -ErrorAction SilentlyContinue
        }
        exit 1
    }

    # The C++ template has an internal brute-force check with ASSERT.
    # If the solution reaches this point without exiting, the internal check passed.
    # If you were using a separate brute-force executable, you would compare outputs here:
    # 
    # $bruteProcess = Start-Process -FilePath ".\my_brute_solution.exe" -Wait -PassThru -NoNewWindow -RedirectStandardInput $INPUT_FILE -RedirectStandardOutput $BRUTE_OUTPUT_FILE
    # if ($bruteProcess.ExitCode -ne 0) {
    #     Write-Error "Brute force solution runtime error!"
    #     Write-Output "Input:"
    #     Get-Content $INPUT_FILE
    #     if (-not $KEEP_FILES_ON_FAILURE) {
    #         Remove-Item -Path "$EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE -ErrorAction SilentlyContinue
    #     }
    #     exit 1
    # }
    #
    # $outputDiff = Compare-Object (Get-Content $OUTPUT_FILE) (Get-Content $BRUTE_OUTPUT_FILE)
    # if ($outputDiff) {
    #     Write-Error "Output mismatch!"
    #     Write-Output "Input:"
    #     Get-Content $INPUT_FILE
    #     Write-Output "Your output:"
    #     Get-Content $OUTPUT_FILE
    #     Write-Output "Brute output:"
    #     Get-Content $BRUTE_OUTPUT_FILE
    #     if (-not $KEEP_FILES_ON_FAILURE) {
    #         Remove-Item -Path "$EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE, $BRUTE_OUTPUT_FILE -ErrorAction SilentlyContinue
    #     }
    #     exit 1
    # }

    Write-Output "Passed."
    $PASSED_COUNT++
}

Write-Output ""
Write-Output "All $PASSED_COUNT/$NumTests tests passed successfully!"

# --- Cleanup ---
if ($KEEP_FILES_ON_FAILURE -and ($PASSED_COUNT -ne $NumTests)) {
    Write-Output "Files kept for debugging: $INPUT_FILE, $OUTPUT_FILE"
} else {
    Remove-Item -Path "$EXECUTABLE_NAME.exe", $INPUT_FILE, $OUTPUT_FILE -ErrorAction SilentlyContinue
    # Optionally remove the python generator if it was auto-created and you don't want to keep it
    # if ((Test-Path $PYTHON_GENERATOR_SCRIPT) -and (Get-Content $PYTHON_GENERATOR_SCRIPT -Raw).Contains("Example: Generate a random number N")) {
    #     Remove-Item -Path $PYTHON_GENERATOR_SCRIPT -ErrorAction SilentlyContinue
    # }
}

exit 0 