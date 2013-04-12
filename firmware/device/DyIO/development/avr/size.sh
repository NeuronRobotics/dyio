#!/bin/bash


for i in $(ls output/o/*.o)
do
	echo $i
	avr-size --format=avr --mcu=atmega644p $i|grep Data
	echo ""
done
