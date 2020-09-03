#!/bin/sh

insert=' '

if [ $# -ge 1 ]; then
    insert="$1"
fi

for f in [0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9].log ; do
    prefix=$(echo "$f" | cut -c 1-10)
    out=$(echo "$f" | cut -c 1-7).log

    n=$(wc -l < "$f")
    yes "$prefix" | head -$n | paste -d "$insert" - "$f" >> "$out"
done
