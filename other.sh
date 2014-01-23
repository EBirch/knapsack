SIZES="64 128 256 512 1024 2048 4096 8192"
for i in $SIZES; do
	echo Size $i
	echo -n $i ''>> otherData
	./knapsack -c `echo $i` -w | grep "Mean time" | echo -n `awk '{print $3}'` ''>> otherData
	./knapsack -d `echo $i` -w | grep "Mean time" | echo -n `awk '{print $3}'` ''>> otherData
	./knapsack -c `echo $i` -n | grep "Mean time" | echo -n `awk '{print $3}'` ''>> otherData
	./knapsack -d `echo $i` -n | grep "Mean time" | echo `awk '{print $3}'` >> otherData
done
