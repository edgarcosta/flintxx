#!/bin/bash

# Bootstrap script for flintxx
# Generates configure script from configure.ac

echo "Bootstrapping flintxx build system..."

# Run autoreconf to generate build system files
if ! command -v autoreconf &> /dev/null; then
    echo "Error: autoreconf is required but not installed"
    exit 1
fi

echo "Running autoreconf..."
autoreconf -ivf

echo "Bootstrap complete. You can now run ./configure"
