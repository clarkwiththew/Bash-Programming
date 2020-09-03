echo "$PATH"
PATH=:$PATH:
PATH=${PATH//:$1:/:}
PATH=${PATH#:}; PATH=${PATH%:}
echo "$PATH"