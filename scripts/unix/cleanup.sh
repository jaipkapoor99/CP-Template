#!/bin/bash

# Comprehensive cleanup script for CP-Template project
# Removes build artifacts, temporary files, generated test files, and other clutter

set -e  # Exit on any error

FORCE=false
VERBOSE=false

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -f|--force)
            FORCE=true
            shift
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [OPTIONS]"
            echo ""
            echo "Options:"
            echo "  -f, --force    Skip confirmation prompts"
            echo "  -v, --verbose  Show detailed output"
            echo "  -h, --help     Show this help message"
            echo ""
            echo "This script removes:"
            echo "  • Build artifacts (.exe, .o, .obj files)"
            echo "  • Temporary files (.tmp, .temp)"
            echo "  • Generated test files (input*.txt, output*.txt)"
            echo "  • Backup files (.bak, .backup, *~)"
            echo "  • IDE files (.vscode/settings.json if default)"
            echo "  • OS-specific files (.DS_Store, Thumbs.db)"
            exit 0
            ;;
        *)
            echo "Unknown option: $1" >&2
            echo "Use -h or --help for usage information." >&2
            exit 1
            ;;
    esac
done

# Determine script and project root directories
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

# Change to project root to ensure we're cleaning the right directory
cd "$PROJECT_ROOT"

log_verbose() {
    if [ "$VERBOSE" = true ]; then
        echo "$1"
    fi
}

log_action() {
    echo "🧹 $1"
}

remove_files() {
    local pattern="$1"
    local description="$2"
    local found_files
    
    # Use find to locate files matching the pattern
    mapfile -t found_files < <(find . -name "$pattern" -type f 2>/dev/null)
    
    if [ ${#found_files[@]} -gt 0 ]; then
        log_action "Removing $description..."
        for file in "${found_files[@]}"; do
            log_verbose "  Removing: $file"
            rm -f "$file"
        done
        echo "  ✓ Removed ${#found_files[@]} $description"
    else
        log_verbose "  No $description found"
    fi
}

remove_directories() {
    local pattern="$1"
    local description="$2"
    local found_dirs
    
    # Use find to locate directories matching the pattern
    mapfile -t found_dirs < <(find . -name "$pattern" -type d 2>/dev/null)
    
    if [ ${#found_dirs[@]} -gt 0 ]; then
        log_action "Removing $description..."
        for dir in "${found_dirs[@]}"; do
            log_verbose "  Removing directory: $dir"
            rm -rf "$dir"
        done
        echo "  ✓ Removed ${#found_dirs[@]} $description"
    else
        log_verbose "  No $description found"
    fi
}

# Show what will be cleaned
echo "🔍 CP-Template Cleanup Script"
echo "Working directory: $PROJECT_ROOT"
echo ""

if [ "$FORCE" = false ]; then
    echo "This will remove:"
    echo "  • Build artifacts (.exe, .o, .obj files)"
    echo "  • Temporary files (.tmp, .temp)"
    echo "  • Generated test files (input*.txt, output*.txt, test*.txt)"
    echo "  • Backup files (.bak, .backup, *~)"
    echo "  • IDE files (.vscode/settings.json if default)"
    echo "  • OS-specific files (.DS_Store, Thumbs.db)"
    echo "  • Node modules and package locks (if any)"
    echo ""
    read -p "Continue with cleanup? (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "Cleanup cancelled."
        exit 0
    fi
fi

echo ""
echo "🚀 Starting cleanup..."

# Build artifacts
remove_files "*.exe" "executable files"
remove_files "*.o" "object files"
remove_files "*.obj" "object files"
remove_files "*.out" "output files"
remove_files "*.a" "static library files"
remove_files "*.so" "shared library files"
remove_files "*.dll" "dynamic library files"

# Temporary files
remove_files "*.tmp" "temporary files"
remove_files "*.temp" "temporary files"
remove_files "*~" "backup files"
remove_files "*.bak" "backup files"
remove_files "*.backup" "backup files"
remove_files "*.swp" "vim swap files"
remove_files "*.swo" "vim swap files"

# Generated test files (be careful not to remove important test data)
remove_files "input*.txt" "generated input files"
remove_files "output*.txt" "generated output files"
remove_files "test*.txt" "generated test files"
remove_files "*.in" "input files"
remove_files "*.out" "output files"

# OS-specific files
remove_files ".DS_Store" "macOS metadata files"
remove_files "Thumbs.db" "Windows thumbnail files"
remove_files "desktop.ini" "Windows desktop files"

# IDE and editor files
remove_directories ".vscode" "VS Code directories (if present)"
remove_files "*.code-workspace" "VS Code workspace files"

# Node.js files (if any)
remove_directories "node_modules" "Node.js modules"
remove_files "package-lock.json" "npm lock files"
remove_files "yarn.lock" "Yarn lock files"

# Python cache files
remove_directories "__pycache__" "Python cache directories"
remove_files "*.pyc" "Python compiled files"
remove_files "*.pyo" "Python optimized files"

# Log files
remove_files "*.log" "log files"

# Core dumps
remove_files "core" "core dump files"
remove_files "core.*" "core dump files"

echo ""
echo "✅ Cleanup completed successfully!"
echo ""

# Show remaining structure
if [ "$VERBOSE" = true ]; then
    echo "📁 Remaining project structure:"
    tree -I '.git' . 2>/dev/null || find . -type d -not -path './.git*' | head -20
fi

echo "🎯 Project is now clean and ready for development!" 