#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

int recursiveKnapsack(std::vector<int> sizes, std::vector<int> values, int n, int size);
int cachingKnapsack(std::vector<int> sizes, std::vector<int> values, int n, int size);
int dynamicKnapsack(std::vector<int> sizes, std::vector<int> values, int n, int size);

int main(){
	const int KNAPSIZE = 1000;
	const int MAXSIZE = 100;
	const int MAXVAL = 100;
	const int ITEMS = 10;
	std::uniform_int_distribution<> sizeDist(1, MAXSIZE);
	std::uniform_int_distribution<> valDist(1, MAXVAL);
	std::mt19937 rng(time(NULL));
	std::vector<int> sizes(ITEMS);
	std::vector<int> values(ITEMS);
	std::generate(sizes.begin(), sizes.end(), [&](){return sizeDist(rng);});
	std::generate(values.begin(), values.end(), [&](){return valDist(rng);});
	for(int i=0;i<sizes.size();++i){
		std::cout<<i<<" size "<<sizes[i]<<std::endl;
		std::cout<<i<<" value "<<values[i]<<std::endl;
	}
	// for(int i=0;i<values.size();++i){
	// 	std::cout<<values[i]<<std::endl;
	// }
	std::cout<<recursiveKnapsack(sizes, values, ITEMS, KNAPSIZE)<<std::endl;
}

int recursiveKnapsack(std::vector<int> sizes, std::vector<int> values, int n, int size){
	if(n < 0 || size <= 0){
		return 0;
	}
	auto notUsed = recursiveKnapsack(sizes, values, n-1, size);
	auto used = (size - sizes[n] >=0 ) ? (recursiveKnapsack(sizes, values, n-1, size - sizes[n]) + values[n]) : 0;
	return std::max(notUsed, used);
}
