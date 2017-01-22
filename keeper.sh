#!/bin/bash

counter=0
while [ true ];
do
	serial=$(adb devices | grep 0044 | cut -d 'd' -f1)
	#echo $serial
	if [ ! -z "$serial" -a "$serial" != " " ]; then
        	echo "Ok. failed ${counter}"
		sleep 20
	else
		counter=$((counter+1))
		echo "Fail"
		./ftdi 1 1
		./ftdi 2 1
		sleep 1
		./ftdi 1 0
		sleep 10
		./ftdi 2 0
		sleep 60
	fi
sleep 1
done
