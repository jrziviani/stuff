#!/bin/bash

compile() {
    echo "compiling external program"
    g++ -O3 -std=c++17 -Wall -Werror -Wextra external.cpp -o external
}

generate_test_case() {
    [[ -f numbers.txt ]] && rm numbers.txt

    # generate a 100MB file with random numbers
    echo "gerating random numbers to test [this will take some time]"
    while true; do
        for val in {1..100000}; do
            echo $RANDOM >> numbers.txt
        done
        sz=$(wc -c < numbers.txt)
         (( $sz > 104857600 )) && break
    done

    echo "create a sorted version to compare later"
    # create a template to compare later
    sort -n numbers.txt > template.txt
}

run() {
    echo "executing the program"
    # execute the program
    local result=$(/usr/bin/time -v ./external numbers.txt 2>&1 1>/dev/null)
    local peak_mem=$(echo "$result" | grep "Maximum" | cut -d':' -f2 | sed -E s@\(\[0-9\]+\)@"scale=2;\\1/1024"@g | bc)
    local time=$(echo "$result" | grep Elapsed | cut -d' ' -f8)

    # show some results
    echo "Peak of memory usage: $peak_mem"MB
    echo "Elapsed time: $time"
}

compare() {
    # check the results
    echo "Check the result is correctly sorted"
    sort -nc chunk.result
    [[ $? == 0 ]] && echo "[OK]"
    echo "Check the result is the same of a template"
    diff -u template.txt chunk.result
    [[ $? == 0 ]] && echo "[OK]"
}

finish() {
    rm chunk*
    rm template.txt
    rm numbers.txt
    rm external
}

main() {
    compile
    generate_test_case
    run
    compare
    finish
}

main
