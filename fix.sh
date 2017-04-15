#!/bin/bash

for var in "$@"
do
	(cat ~/Git/ParserGenerator/LicenseHeader.txt & cat $var) > test.txt.tmp
	mv test.txt.tmp $var
done
