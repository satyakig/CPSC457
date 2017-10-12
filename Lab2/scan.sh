find . -type f -name "*$1" -printf '%p, %s\n' | sort -t"," -k 2 -n -r | head -$2 | awk '{ x += $NF ; print $0 } END { print "Total Size: " x }'


