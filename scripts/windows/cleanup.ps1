# PowerShell script to clean up all generated/temporary files
# This script removes build artifacts, test files, and other temporary files
# while preserving the core template structure.

param(
    [switch]$Force,  # Skip confirmation prompts
    [switch]$Verbose # Show detailed output
)

# Ensure we're running from the project root
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$projectRoot = Split-Path -Parent $scriptDir
Set-Location $projectRoot

Write-Host "🧹 CP-Template Cleanup Script" -ForegroundColor Cyan
Write-Host "==============================" -ForegroundColor Cyan
Write-Host "Working directory: $(Get-Location)" -ForegroundColor Gray

# Define files and patterns to clean up
$FilesToDelete = @(
    # Build artifacts
    "*.exe",
    "*.o", 
    "*.obj",
    
    # Temporary files
    "*.txt",
    "tempCodeRunnerFile.cpp",
    
    # Generated test files
    "brute.cpp",
    "scripts/brute.cpp",
    "src/brute.cpp",
    
    # Backup files
    "*_backup.cpp",
    "*_backup.hpp",
    
    # Python cache
    "__pycache__",
    "*.pyc",
    "*.pyo"
)

$DirectoriesToDelete = @(
    # IDE/Editor directories
    ".vscode",
    
    # CPH directories
    ".cph",
    ".cph_settings", 
    ".cph_cache",
    
    # Test directories
    "script_test",
    
    # Python cache
    "__pycache__"
)

# Function to safely delete files/directories
function Remove-SafelyWithConfirmation {
    param(
        [string]$Path,
        [string]$Type = "file"
    )
    
    if (Test-Path $Path) {
        if ($Verbose) {
            Write-Host "  Found: $Path" -ForegroundColor Yellow
        }
        
        if ($Force -or (Read-Host "Delete $Type '$Path'? (y/N)") -eq 'y') {
            try {
                if ($Type -eq "directory") {
                    Remove-Item $Path -Recurse -Force
                } else {
                    Remove-Item $Path -Force
                }
                Write-Host "  ✅ Deleted: $Path" -ForegroundColor Green
                return $true
            }
            catch {
                Write-Host "  ❌ Failed to delete: $Path - $($_.Exception.Message)" -ForegroundColor Red
                return $false
            }
        } else {
            Write-Host "  ⏭️  Skipped: $Path" -ForegroundColor Gray
            return $false
        }
    }
    return $false
}

# Clean up files
Write-Host "`n🗂️  Cleaning up files..." -ForegroundColor Blue
$filesDeleted = 0

foreach ($pattern in $FilesToDelete) {
    $matchingFiles = Get-ChildItem -Path . -Recurse -Name $pattern -ErrorAction SilentlyContinue
    
    foreach ($file in $matchingFiles) {
        if (Remove-SafelyWithConfirmation -Path $file -Type "file") {
            $filesDeleted++
        }
    }
}

# Clean up directories
Write-Host "`n📁 Cleaning up directories..." -ForegroundColor Blue
$dirsDeleted = 0

foreach ($dirPattern in $DirectoriesToDelete) {
    $matchingDirs = Get-ChildItem -Path . -Recurse -Directory -Name $dirPattern -ErrorAction SilentlyContinue
    
    foreach ($dir in $matchingDirs) {
        if (Remove-SafelyWithConfirmation -Path $dir -Type "directory") {
            $dirsDeleted++
        }
    }
}

# Clean up root directory (except allowed files/folders)
Write-Host "`n🏠 Cleaning up root directory..." -ForegroundColor Blue
$allowedInRoot = @(
    ".gitignore",
    "README.md", 
    "src",
    "include",
    "scripts", 
    "tests",
    "docs",
    ".git"
)

$rootItems = Get-ChildItem -Path . -Force | Where-Object { 
    $_.Name -notin $allowedInRoot 
}

$rootCleaned = 0
foreach ($item in $rootItems) {
    $type = if ($item.PSIsContainer) { "directory" } else { "file" }
    if (Remove-SafelyWithConfirmation -Path $item.Name -Type $type) {
        $rootCleaned++
    }
}

# Summary
Write-Host "`n📊 Cleanup Summary:" -ForegroundColor Magenta
Write-Host "===================" -ForegroundColor Magenta
Write-Host "Files deleted: $filesDeleted" -ForegroundColor Green
Write-Host "Directories deleted: $dirsDeleted" -ForegroundColor Green  
Write-Host "Root items cleaned: $rootCleaned" -ForegroundColor Green
Write-Host "Total items cleaned: $($filesDeleted + $dirsDeleted + $rootCleaned)" -ForegroundColor Cyan

if (($filesDeleted + $dirsDeleted + $rootCleaned) -eq 0) {
    Write-Host "`n✨ Repository is already clean!" -ForegroundColor Green
} else {
    Write-Host "`n✅ Cleanup completed successfully!" -ForegroundColor Green
}

Write-Host "`n💡 Tip: Use -Force to skip confirmations, -Verbose for detailed output" -ForegroundColor Gray 