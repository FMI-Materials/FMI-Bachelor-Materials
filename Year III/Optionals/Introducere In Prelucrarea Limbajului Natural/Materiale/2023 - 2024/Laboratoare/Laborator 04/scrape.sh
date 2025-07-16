#!/bin/bash

for page in {1..8}; do
    curl -o index/index-${page}.html https://anpc.ro/category/comunicate-de-presa/bpage/${page}/
done
