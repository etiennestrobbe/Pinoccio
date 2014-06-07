#!/bin/bash
extension_bin='.bin'
repertoire="./tests/"
for n in ./tests/*
do
fullfilename=$(basename $n)
filename=${fullfilename%.*}
extension=${fullfilename##*.}
if [ $extension = "asm" ]
then
	name=$repertoire$filename$extension_bin
	./asm $n $name
fi
done
