#! /bin/bash

rm -fR wbcl wbpol wbpwl wbtbl test-cpu.csv
make 2>&1 >make.log || { echo "COMPILATION ERROR"; exit 1; }
{
lscpu
printf  "\n\n#=== Classic ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./wbcl ;  } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
printf  "\n\n#===   PWL   ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./wbpwl ; } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
printf  "\n\n#===   POL   ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./wbpol ; } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
printf  "\n\n#===   TBL   ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./wbtbl ; } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
printf  "\n\n#===   MIX   ===\n"
for i in 0 1 2 3 4 5 6 7 8 9; do
	{ time -p ./wbmix ; } 2>&1 | grep "user" | sed "s|user[[:blank:]]*||g"
done
}  | tee -a test-cpu.csv
