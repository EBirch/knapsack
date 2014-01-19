#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

int recursiveKnapsack(std::vector<int> sizes, std::vector<int> values, int n, int size);
int cachingKnapsack(std::vector<int> sizes, std::vector<int> values, std::vector<std::vector<int>> &cache, int n, int size);
int dynamicKnapsack(std::vector<int> sizes, std::vector<int> values, int n, int size);

const int KNAPSIZE = 1000;
const int MAXSIZE = 100;
const int MAXVAL = 100;
const int ITEMS = 20;

int main(){
	std::uniform_int_distribution<> sizeDist(1, MAXSIZE);
	std::uniform_int_distribution<> valDist(1, MAXVAL);
	std::mt19937 rng(time(NULL));

	std::vector<int> sizes(ITEMS);
	std::vector<int> values(ITEMS);

	std::generate(sizes.begin(), sizes.end(), [&](){return sizeDist(rng);});
	std::generate(values.begin(), values.end(), [&](){return valDist(rng);});
	std::vector<std::vector<int>> cache(ITEMS, std::vector<int>(KNAPSIZE, -1));

	std::cout<<recursiveKnapsack(sizes, values, ITEMS - 1, KNAPSIZE)<<std::endl;
	std::cout<<cachingKnapsack(sizes, values, cache, ITEMS - 1, KNAPSIZE)<<std::endl;
	std::cout<<dynamicKnapsack(sizes, values, ITEMS, KNAPSIZE)<<std::endl;
}

int recursiveKnapsack(std::vector<int> sizes, std::vector<int> values, int n, int size){
	if(n < 0 || size <= 0){
		return 0;
	}
	auto notUsed = recursiveKnapsack(sizes, values, n-1, size);
	auto used = (size - sizes[n] >= 0 ) ? (recursiveKnapsack(sizes, values, n - 1, size - sizes[n]) + values[n]) : 0;
	return std::max(notUsed, used);
}

int cachingKnapsack(std::vector<int> sizes, std::vector<int> values, std::vector<std::vector<int>> &cache, int n, int size){
	if(n < 0 || size <= 0){
		return 0;
	}
	if(cache[n][size - 1] < 0){
		auto notUsed = cachingKnapsack(sizes, values, cache, n - 1, size);
		auto used = (size - sizes[n] >= 0 ) ? (cachingKnapsack(sizes, values, cache, n - 1, size - sizes[n]) + values[n]) : 0;
		cache[n][size - 1] = std::max(notUsed, used);
	}
	return cache[n][size - 1];
}

int dynamicKnapsack(std::vector<int> sizes, std::vector<int> values, int n, int size){
	std::vector<std::vector<int>> cache(n + 1, std::vector<int>(size + 1, 0));
	for(int i = 1;i < cache.size(); ++i){
		for(int j = 1;j < cache[i].size(); ++j){
			auto used = (j - sizes[i-1] >= 0) ? (cache[i-1][j-sizes[i-1]] + values[i-1]) : 0;
			cache[i][j] = std::max(cache[i-1][j], used);
		}
	}
	return cache[n][size];
}
