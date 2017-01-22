#!/bin/bash

FTDI_PATH="/root/BlueRelay/"
counter=0
#while [ true ];
#do
	serial=$(adb devices | grep 0044 | cut -d 'd' -f1)
	#echo $serial
	if [ ! -z "$serial" -a "$serial" != " " ]; then
        	echo "Ok. failed ${counter}"
#		sleep 20
	else
		counter=$((counter+1))
		echo "Fail"
		${FTDI_PATH}ftdi 1 1
		${FTDI_PATH}ftdi 2 1
		sleep 1
		${FTDI_PATH}ftdi 1 0
		sleep 10
		${FTDI_PATH}ftdi 2 0
	#	sleep 60
	fi
sleep 1
#done
