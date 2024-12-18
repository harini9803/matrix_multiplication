#!/bin/bash

# CSV file to store the results
OUTPUT_FILE="Results/time_report.csv"

# Header for the CSV file
echo "UnitTest,TimeTaken(ms),Status" > $OUTPUT_FILE

# Compile the driver program
gcc driver.c -o driver -O2
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

# Loop through each unit test directory
for UNIT_DIR in Unit_test/unit_*; do
    if [ -d "$UNIT_DIR" ]; then
        echo "Running test: $UNIT_DIR"
        
        # Get the start time
        START_TIME=$(date +%s%3N)
        
        # Run the driver program with the current test directory
        ./driver "$UNIT_DIR"
        STATUS=$?

        # Get the end time
        END_TIME=$(date +%s%3N)
        
        # Calculate the time taken
        TIME_TAKEN=$((END_TIME - START_TIME))
        
        # Determine test result status
        if [ $STATUS -eq 0 ]; then
            TEST_STATUS="Success"
        else
            TEST_STATUS="Failure"
        fi

        # Append results to the CSV file
        UNIT_NAME=$(basename "$UNIT_DIR")
        echo "$UNIT_NAME,$TIME_TAKEN,$TEST_STATUS" >> $OUTPUT_FILE
    fi
done

echo "All tests completed. Results saved in $OUTPUT_FILE."
