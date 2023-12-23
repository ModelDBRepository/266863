#! /bin/bash

rm -fR wbcl-gpu wbpol-gpu wbpwl-gpu wbtbl-gpu test-gpu.csv
export PATH=`pwd`:$PATH
make gpu 2>&1 >make.log || { echo "COMPILATION ERROR"; exit 1; }
{
printf  "\n\n#=== Classic ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./wbcl-gpu > wbcl-gpu.log ;  } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
printf  "\n\n#===   PWL   ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./wbpwl-gpu > wbpwl-gpu.log ; } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
printf  "\n\n#===   POL   ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./wbpol-gpu > wbpol-gpu.log ; } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
printf  "\n\n#===   TBL   ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./wbtbl-gpu > wbtbl-gpu.log ; } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done

printf  "\n\n#===   MIX   ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./wbmix-gpu > wbmix-gpu.log ; } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
} | tee test-gpu.csv
