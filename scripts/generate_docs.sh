#!/usr/bin/env bash

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
DOCS_DIR="$PROJECT_ROOT/docs"

echo "=== SGF-C Documentation Generator ==="
echo ""

# Check for doxygen
if ! command -v doxygen &> /dev/null; then
    echo "Error: doxygen is not installed."
    echo ""
    echo "Install doxygen:"
    echo "  macOS:    brew install doxygen"
    echo "  Ubuntu:   sudo apt-get install doxygen"
    echo "  Fedora:   sudo dnf install doxygen"
    echo "  Arch:     sudo pacman -S doxygen"
    echo ""
    exit 1
fi

echo "Generating documentation..."
echo ""

# Create docs directory if it doesn't exist
mkdir -p "$DOCS_DIR"

# Generate docs
cd "$PROJECT_ROOT"
doxygen Doxyfile

echo ""
echo "=== Done ==="
echo ""
echo "Documentation generated in: $DOCS_DIR/html/"
echo ""
echo "Open the following file in a browser to view:"
echo "  file://$DOCS_DIR/html/index.html"
echo ""
