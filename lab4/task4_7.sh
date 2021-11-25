#! /bin/bash
(cd $1 && ls -li | awk '{print $10}')  > "tmp1.out"
(cd $2 && ls -li | awk '{print $10}')  > "tmp2.out"
while IFS= read -r line2 #read line in tmp2.out
do
	lmt2=$(date +%s  -r  "$2/$line2")
	while IFS= read -r line1
	do
		foundEq=false
		lmt1=$(date +%s -r "$1/$line1")
		if [ $lmt1 -lt  $lmt2 ] && [ "$line1" == "$line2" ]; then 
			cp  "$2/$line2" $1
			break
		fi
		if [ "$line1" == "$line2" ]; then 
			foundEq=true
			break
		fi
	
	done < "./tmp1.out"
	if [ "$foundEq" = false ]; then
		cp "$2/$line2" $1
		echo "copping"
	fi	
done < "./tmp2.out"
ls -li $1
while IFS= read -r  line1 #read line in tmp1.out
do  
    
     while IFS= read -r  line2
     do 
	    
	     foundE=false
	     if [ "$line1" == "$line2" ]; then 
		     foundE=true
		     break
	     fi
     
     done < "./tmp2.out"
     if [ "$foundE" = false ]; then
	   rm "$1/$line1"
     fi
done < "./tmp1.out"
rm tmp1.out
rm tmp2.out
