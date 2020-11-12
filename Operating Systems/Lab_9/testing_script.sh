echo "step 1 test"
echo " "
for file in test1.txt test2.txt test3.txt test4.txt test5.txt;
	do 
	echo "step 1 $file"
	time ./step1 $file
	echo " "
done

echo "step 2 test"
echo " "
for file in test1.txt test2.txt test3.txt test4.txt test5.txt;
	do 
	for buff in 100 1000 10000 100000
		do
		echo "step 2 $file $buff"
		time ./step2 $file $buff
		echo " "
	done
done

echo "step 3 test"
echo " "
for file in test1.txt test2.txt test3.txt test4.txt test5.txt;
	do 
	for buff in 100 1000 10000 100000
		do
		echo "step 3 $file $buff"
		time ./step3 $file $buff
		echo " "
	done
done
rm *step3copy*


echo "step 4 test"
echo " "
for file in test1.txt test2.txt test3.txt test4.txt;
	do 
	for buff in 100 1000 10000 100000
		do
		for tc in 2 8 32 64
		do
			echo "step 4 $file $buff $tc"
			time ./step4 $file $buff $tc
			echo " "
		done
		rm *step4copy*
	done
done
