# Last Name:   Ghosh
# First Name:  Satyaki
# Student ID:  10077685
# Course:      CPSC 457
# Tutorial:    T01
# Assignment:  2
# Question:    Q5
# File Name: scan.sh


find . -type f -name "*$1" -printf '%p, %s\n' | sort -t"," -k 2 -n -r | head -$2 | awk '{ x += $NF ; print $0 } END { print "Total Size: " x }'


