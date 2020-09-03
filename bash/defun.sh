#!/bin/bash
 
check()
{
isdir=0
for arg in "$@"
do
if [ "$arg" == "-d" ]
then
    isdir=1
else
if [ "$isdir" == 1 ]
               then
                   [ -d "$arg" ] && echo "$arg is a directory" || echo "$arg is not a directory"
                   isdir=0
               else
                   isdir=0
                   [ -e "$arg" ] && echo "$arg exists" || echo "$arg does not exist"
           fi
        fi
    done
}
