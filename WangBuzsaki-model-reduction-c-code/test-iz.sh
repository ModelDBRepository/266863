#! /bin/bash

rm -fR izcl-gpu izcl
export PATH=`pwd`:$PATH
make iz 2>&1 >make.log || { echo "COMPILATION ERROR"; exit 1; }
printf  "\n\n#=== Iz CPU ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./izcl > izcl.log ;  } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
printf  "\n\n#=== Iz GPU   ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./izcl-gpu > izcl-gpu.log ; } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
