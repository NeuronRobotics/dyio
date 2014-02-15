#!/bin/bash

total=0

for i in $(ls output/o/*.o)
do
	echo $i
	xc32-size --no-split $i
	echo ""
done

