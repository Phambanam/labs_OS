#! /bin/bash

grep -Rl $1 . > out.txt

while IFS= read -r line
do
	echo "$line $(cat -b $line | grep $1)" > $2
done < out.txt
cat $2

rm $2
rm out.txt
