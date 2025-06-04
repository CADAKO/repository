#!/bin/bash

result=""
test_status=0
result=$(grep FAILED: ./cat/test.txt)
echo $result
if [ "$result" = "FAILED: 0" ]
  then
    echo "test cat SUCCESS"
  else
    echo "test cat FAIL"
    test_status=1
fi
result=$(grep FAIL: ./grep/test.txt)
echo $result
if [ "$result" = "FAIL: 0" ]
  then
    echo "test grep SUCCESS"
  else
    echo "test grep FAIL"
    test_status=1
fi
exit $test_status
