#!/bin/bash

MLX42_DIR="./MLX42"
OS=$(uname -s)
BUILD_DIR=""

# Detect the operating system and set the build directory
if [ "$OS" = "Linux" ]; then
  BUILD_DIR="build_linux"
elif [ "$OS" = "Darwin" ]; then
  BUILD_DIR="build_macos"
else
  echo "❌ Unsupported operating system: $OS"
  exit 1
fi

# Create the build directory if it doesn't exist
mkdir -p "$MLX42_DIR/$BUILD_DIR"

# Run CMake only if the build directory is empty or needs to be configured
if [ ! -f "$MLX42_DIR/$BUILD_DIR/Makefile" ]; then
  echo "⚙️  Configuring MLX42 for $OS..."
  cmake -B "$MLX42_DIR/$BUILD_DIR" -S "$MLX42_DIR" || exit 1
fi

# Compile MLX42
echo "🔨 Building MLX42 for $OS..."
cmake --build "$MLX42_DIR/$BUILD_DIR" || exit 1

echo "✅ MLX42 build completed for $OS!"
