#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"All test_1_grep.txt test_2_grep.txt"
"-e All test_1_grep.txt"
"-i ALL test_1_grep.txt"
"-v All test_1_grep.txt"
"-c All test_1_grep.txt"
"-l All test_1_grep.txt test_2_grep.txt"
"-n All test_1_grep.txt"

"-h All test_1_grep.txt test_2_grep.txt"
"-s All find_me.txt"

"-cv All test_1_grep.txt"
"-iv All test_1_grep.txt"
"-lv All test_1_grep.txt test_2_grep.txt"
"-hl All test_1_grep.txt test_2_grep.txt"
"-nv All test_1_grep.txt test_2_grep.txt"
"-iv All test_1_grep.txt test_2_grep.txt"
"-cv All test_1_grep.txt test_2_grep.txt"
"-sv All test_1_grep.txt test_2_grep.txt"
"-hv All test_1_grep.txt test_2_grep.txt"
"-ci All test_1_grep.txt test_2_grep.txt"
"-si All test_1_grep.txt test_2_grep.txt"
"-hi All test_1_grep.txt test_2_grep.txt"
"-ni All test_1_grep.txt test_2_grep.txt"
"-cv -e All test_1_grep.txt"
"-iv -e All test_1_grep.txt"
"-lv -e All test_1_grep.txt test_2_grep.txt"
"-hl -e All test_1_grep.txt test_2_grep.txt"
"-nv -e All test_1_grep.txt test_2_grep.txt"
"-iv -e All test_1_grep.txt test_2_grep.txt"
"-cv -e All test_1_grep.txt test_2_grep.txt"
"-sv -e All test_1_grep.txt test_2_grep.txt"
"-hv -e All test_1_grep.txt test_2_grep.txt"
"-ci -e All test_1_grep.txt test_2_grep.txt"
"-si -e All test_1_grep.txt test_2_grep.txt"
"-hi -e All test_1_grep.txt test_2_grep.txt"
"-ni -e All test_1_grep.txt test_2_grep.txt"
"-cvh -e All test_1_grep.txt"
"-ivc -e All test_1_grep.txt"
"-lvc -e All test_1_grep.txt test_2_grep.txt"
"-hlc -e All test_1_grep.txt test_2_grep.txt"
"-nvc -e All test_1_grep.txt test_2_grep.txt"
"-ivn -e All test_1_grep.txt test_2_grep.txt"
"-cvlh -e All test_1_grep.txt test_2_grep.txt"
"-svlh -e All test_1_grep.txt test_2_grep.txt"
"-hvln -e All test_1_grep.txt test_2_grep.txt"
"-cilv -e All test_1_grep.txt test_2_grep.txt"
"-silvn -e All test_1_grep.txt test_2_grep.txt"
"-hilv -e All test_1_grep.txt test_2_grep.txt"
"-nilv -e All test_1_grep.txt test_2_grep.txt"
"-cv -e Al test_1_grep.txt nofile.txt"
"-iv -e ^All test_1_grep.txt nofile.txt"
"-lv -e for -e All test_1_grep.txt test_2_grep.txt nofile.txt"
"-hl -e All test_1_grep.txt test_2_grep.txt nofile.txt"
"-nv -e All test_1_grep.txt test_2_grep.txt nofile.txt"
"-iv -e all test_1_grep.txt test_2_grep.txt nofile.txt"
"-cv -e All test_1_grep.txt test_2_grep.txt nofile.txt"
"-sv -e All test_1_grep.txt test_2_grep.txt nofile.txt"
"-hv -e All test_1_grep.txt test_2_grep.txt nofile.txt"
"-ci -e All test_1_grep.txt test_2_grep.txt nofile.txt"
"-si -e All -e for test_1_grep.txt test_2_grep.txt nofile.txt"
"-hi -e All test_1_grep.txt test_2_grep.txt nofile.txt"
"-ni -e All test_1_grep.txt test_2_grep.txt nofile.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo "$FAIL/$SUCCESS/$COUNTER success grep $t"
    else
      (( FAIL++ ))
      echo "$FAIL/$SUCCESS/$COUNTER fail grep $t"
    fi
    rm test_s21_grep.log test_sys_grep.log
}

for i in "${tests[@]}"
do
    var="-"
    testing $i
done


echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
printf "\n"
