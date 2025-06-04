#!/bin/bash

PATH1="src/cat/s21_cat"
PATH2="src/grep/s21_grep"
# PATH2="/home/gitlab-runner/builds/xEf-8Z7_/0/students/DO6_CICD.ID_356283/wattniji_student.21_school.ru/DO6_CICD-1/src/grep/s21_grep"
REMOTE_IP="192.168.100.1"
REMOTE_PATH="/usr/local/bin"

scp "$PATH1" user1@"$REMOTE_IP":"$REMOTE_PATH"
scp "$PATH2" user1@"$REMOTE_IP":"$REMOTE_PATH"
