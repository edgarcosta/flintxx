#!/bin/bash

# Bootstrap script for flintxx
# Generates configure script from configure.ac

echo "Bootstrapping flintxx build system..."

# Check for required tools
if ! command -v autoconf &> /dev/null; then
    echo "Error: autoconf is required but not installed"
    exit 1
fi

if ! command -v autoheader &> /dev/null; then
    echo "Error: autoheader is required but not installed"
    exit 1
fi

# Create config directory if it doesn't exist
mkdir -p config

# Generate configure script
echo "Running autoheader..."
autoheader

echo "Running autoconf..."
autoconf

# Make sure configure is executable
chmod +x configure

echo "Bootstrap complete. You can now run ./configure"
