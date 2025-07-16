#!/bin/bash

extract_titles() {
    local data_dir
    data_dir=$1
    rm "titles-${data_dir}.txt"
    for file in $(ls -1 ${data_dir}); do
        grep -E "title=\"Horoscop[ul]* ?[zil]*.* [[:digit:]]{1,2} [[:alpha:]]" ${data_dir}/${file} | grep -v "săpt" | sed s/.*title=\"// | sed "s/\".*//" | sed s/Află.*// | uniq >> "titles-${data_dir}.txt"
    done
}

extract_titles "data_index"
extract_titles "data_index2"
