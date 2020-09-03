#!/bin/sh
if test $# -ne 2
then
    echo usage:src and tgt >&2
    exit 1
fi
if [ -d tgt ]
then
    echo alr exist tgt >&2
    exit 2
fi
mkdir $2
cd $2
dest=`pwd`
cd ..
#rm -rf $2*
cd $1
for dir in */; do
    if [ -d "$dir" ]; then
        #end=$(basename $"$(pwd)")
        cd "$dir"
        for dir2 in */; do
            if [ -d "$dir2" ]; then
                mkdir -p "$dest"/"$dir2"/"$dir"
                cp -r $1/"$dir""$dir2"* $dest/"$dir2""$dir"
            fi
        done
        cd ..
    fi
done
