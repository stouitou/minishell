#!/bin/bash

# Path to the tests.logs file
LOG_FILE="./src/tester/all.logs"

# Path to the last_tested.logs file
LAST_TESTED_LOGS_FILE="./src/tester/last_tested.logs"

# Keep track of the number of lines in the file
num_lines=$(wc -l < "$LOG_FILE")

# Continuously check for new entries in the tests.logs file
while true; do
    # Get the current number of lines in the file
    current_num_lines=$(wc -l < "$LOG_FILE")

    # Check if new lines have been added
    if [ "$current_num_lines" -gt "$num_lines" ]; then
        echo "Running test..."

        # Copy the last entry from all.logs to last_tested.logs
        tail -n 1 "$LOG_FILE" > "$LAST_TESTED_LOGS_FILE"

        # Run the test script
        ./test_last_log.sh

		# Remove the last line from the log file
        sed -i '$d' "$LOG_FILE"

        echo "Test completed."

        # Update the number of lines to the current count
        num_lines="$current_num_lines"
    fi

    # Polling interval (in seconds)
    sleep 1
done
