#!/bin/bash

# step1:
# sudo apt-get install lcov

# step2:
# chmod +x coverage.sh

# step3:
# execute .sh
# ./coverage.sh

# set build dir
BUILD_DIR="./build"

if [ ! -f "$BUILD_DIR/ormTest" ]; then
    echo "Error: Test executable 'ormTest' not found in '$BUILD_DIR'. Please run 'make' first."
    exit 1
fi

echo "Running tests..."
$BUILD_DIR/ormTest

if [ $? -ne 0 ]; then
    echo "Error: Test execution failed."
    exit 1
fi

echo "Generating coverage information..."
lcov --capture --directory $BUILD_DIR --output-file coverage.info

echo "Generating HTML report..."
genhtml coverage.info --output-directory out

if command -v xdg-open &> /dev/null
then
    xdg-open out/index.html
elif command -v open &> /dev/null  # macOS
then
    open out/index.html
else
    echo "Coverage report generated in 'out/index.html'. Please open it manually."
fi
