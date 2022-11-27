#!/bin/bash

printf "#####################\n"
printf "### Running tests ###\n"
printf "#####################\n\n"
count=0 # number of test cases run so far

# Assume all `.in` and `.out` files are located in a separate `tests` directory

for folder in `ls -d tests/*/ | sort -V`; do
    name=$(basename "$folder")

    echo Running test $name.

    cat tests/$name/$name.in | xargs -a tests/$name/$name.args ./timetable | diff - tests/$name/$name.out || echo "Test $name: failed!"

    count=$((count+1))
done

printf "\nTests completed!\n"
