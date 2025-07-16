#!/bin/bash

INDEX_DIR="data_index"
INDEX_DIR2="data_index2"
export DATA_DIR="data"
export DATA_DIR2="data2"

mkdir -p "${INDEX_DIR}" "${DATA_DIR}" "${INDEX_DIR2}" "${DATA_DIR2}"


get_pages_horoscop1() {
    for page in {1..20}; do
        echo "on page ${page}"
        # -L follow redirects
        curl -o "${INDEX_DIR}/index-${page}.html" --silent -L "https://catine.ro/rubrica/horoscop-zilnic/page/${page}"
        #
        # we can check with | wc -l if we extracted all links
        grep "href.*Horoscopul zilei" "${INDEX_DIR}/index-${page}.html" | \
            sed s/.*href=\"// | \
            sed s/.html.*/.html/ | \
            xargs -I{} bash -c 'curl --silent -o "${DATA_DIR}/horoscop-$(echo {} | grep -E -o "[[:digit:]]{1,2}-[[:alpha:]]+-[[:digit:]]{4}").html" {}'
    done
}


get_pages_horoscop2() {
    # 1..124
    for page in {1..124}; do
        echo "on page ${page}"
        curl -o "${INDEX_DIR2}/index-${page}.html" --silent -L "https://observatornews.ro/horoscop?p=${page}"
        #
        grep -E "href.*Horoscop [[:digit:]]{1,2}" "${INDEX_DIR2}/index-${page}.html" | \
            sed s/.*href=\"// | \
            sed s/.html.*/.html/ | \
            xargs -I{} bash -c 'curl --silent -o "${DATA_DIR2}/horoscop-$(echo {} | grep -E -o "[[:digit:]]{1,2}-[[:alpha:]]+-[[:digit:]]{4}").html" {}'
    done
}


main() {
    get_pages_horoscop1
    get_pages_horoscop2
}


main
