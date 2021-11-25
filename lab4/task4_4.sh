cd $1
for file in *;
do
       stat --format='file name %n, size %s, atributes %A' $file >> fileFirst.txt       
done

cd ../$2

for file in *;
do
       stat --format='file name %n, size %s, atributes %A' $file >> fileSecond.txt
done

cd ../
ls -l $1
echo "___________________"
ls -l $2

echo "diffrent between $1 and $2: "
diff $1/fileFirst.txt $2/fileSecond.txt

rm $1/fileFirst.txt
rm $2/fileSecond.txt

