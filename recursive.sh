for i in {6..20}; do
	./knapsack -r `echo $i` | tee | grep "Mean time" | awk '{print $3}' | tee -a recursive
done
