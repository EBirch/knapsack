for i in {6..20}; do
	echo Size $i
	echo -n $i ''>> recursiveData
	./knapsack -r `echo $i` | grep "Mean time" | echo `awk '{print $3}'` >> recursiveData
done
