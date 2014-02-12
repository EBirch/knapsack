#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <iomanip>

int recursiveKnapsack(std::vector<int> &sizes, std::vector<int> &values, int n, int size);
int cachingKnapsack(std::vector<int> &sizes, std::vector<int> &values, std::vector<std::vector<int>> &cache, int n, int size);
int dynamicKnapsack(std::vector<int> &sizes, std::vector<int> &values, int n, int size);
int dynamicLinearKnapsack(std::vector<int> &sizes, std::vector<int> &values, std::vector<bool> &used, int itemsLow, int itemsHigh, int sizeLot, int sizeHigh);
std::vector<bool> dynamicBacktrace(std::vector<std::vector<int>> &cache, std::vector<int> &sizes);
std::vector<bool> cachingBacktrace(std::vector<std::vector<int>> &cache, std::vector<int> &sizes);

int main(int argc, char **argv){
	// if(argc < 3){
	// 	std::cout<<"Too few arguments\n";
	// 	return 0;
	// }
	// int ITEMS = atoi(argv[2]);
	// int KNAPSIZE = (argv[1][1] == 'r') ? 1000 : ITEMS * 10;
	// int MAXSIZE = (argv[1][1] == 'r') ? 100 : ITEMS * 10;
	// int MAXVAL = (argv[1][1] == 'r') ? 100 : ITEMS * 10;
	// int MINSIZE = (argc < 4) ? 1 : ((argv[3][1] == 'w') ? 1 : (KNAPSIZE / 20));
	int KNAPSIZE = 10;
	int ITEMS = 5;
	int MAXSIZE = 5;
	int MAXVAL = 5;
	int MINSIZE = 1;

	std::uniform_int_distribution<> sizeDist(MINSIZE, MAXSIZE);
	std::uniform_int_distribution<> valDist(1, MAXVAL);
	std::mt19937 rng(time(NULL));
	std::vector<float> times;
	
	std::cout<<"Problem size: "<<ITEMS<<std::endl;
	std::cout<<"Knapsize: "<<KNAPSIZE<<std::endl;


	std::vector<int> sizes(ITEMS);
	// std::vector<int> sizes;
	std::vector<int> values(ITEMS);
	// std::vector<int> values;
	std::generate(sizes.begin(), sizes.end(), [&](){return sizeDist(rng);});
	std::generate(values.begin(), values.end(), [&](){return valDist(rng);});

	// sizes.push_back(5);
	// values.push_back(4);
	// sizes.push_back(1);
	// values.push_back(9);
	// sizes.push_back(6);
	// values.push_back(2);
	
	for(int i = 0; i < sizes.size(); ++i){
		std::cout<<"Item "<<i<<": size "<<sizes[i]<<" val "<<values[i]<<std::endl;
	}

	std::vector<bool> used(ITEMS);
	auto temp = dynamicLinearKnapsack(sizes, values, used, 0, ITEMS, 0, KNAPSIZE);
	for(int i=0;i<used.size();++i){
		std::cout<<used[i]<<" ";
	}

	// auto temp=dynamicKnapsack(sizes, values, ITEMS, KNAPSIZE);
	// std::vector<std::vector<int>> cache(ITEMS, std::vector<int>(KNAPSIZE, -1));
	// cachingKnapsack(sizes, values, cache, ITEMS - 1, KNAPSIZE);

	// for(int i = cache.size() - 1; i >= 0; --i){
	// 	for(auto &col : cache[i]){
	// 		std::cout<<std::setw(3)<<col<<" ";
	// 	}
	// 	std::cout<<std::endl;
	// }

	// auto res = cachingBacktrace(cache, sizes);

	// for(int i=0;i<res.size();++i){
	// 	std::cout<<res[i]<<" ";
	// }


	// for(int i = 0; i < 10; ++i){
	// 	std::vector<int> sizes(ITEMS);
	// 	std::vector<int> values(ITEMS);
	// 	std::vector<std::vector<int>> cache(ITEMS, std::vector<int>(KNAPSIZE, -1));
	// 	std::generate(sizes.begin(), sizes.end(), [&](){return sizeDist(rng);});
	// 	std::generate(values.begin(), values.end(), [&](){return valDist(rng);});
	// 	auto start = std::chrono::steady_clock::now();

	// 	switch(argv[1][1]){
	// 		case 'r': std::cout<<"Recursive knapsack value: "<<recursiveKnapsack(sizes, values, ITEMS - 1, KNAPSIZE)<<std::endl; //Takes ITEMS - 1 to compensate for indexing
	// 			break;
	// 		case 'c': std::cout<<"Caching knapack value: "<<cachingKnapsack(sizes, values, cache, ITEMS - 1, KNAPSIZE)<<std::endl; //Takes ITEMS - 1 to compensate for indexing
	// 			break;
	// 		case 'd': std::cout<<"Dynamic knapsack value: "<<dynamicKnapsack(sizes, values, ITEMS, KNAPSIZE)<<std::endl;
	// 			break;
	// 	}
	// 	times.push_back(std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::steady_clock::now() - start).count());
	// 	std::cout<<"Done run "<<i+1<<" in "<<times[i]<<" seconds\n\n";
	// }
	// std::cout<<"Mean time: "<<(std::accumulate(times.begin(), times.end(), 0.0) / times.size())<<" seconds"<<std::endl<<std::endl;
}

int recursiveKnapsack(std::vector<int> &sizes, std::vector<int> &values, int n, int size){
	if(n < 0 || size <= 0){
		return 0;
	}
	auto notUsed = recursiveKnapsack(sizes, values, n-1, size);
	auto used = (size - sizes[n] >= 0 ) ? (recursiveKnapsack(sizes, values, n - 1, size - sizes[n]) + values[n]) : 0;
	return std::max(notUsed, used);
}

int cachingKnapsack(std::vector<int> &sizes, std::vector<int> &values, std::vector<std::vector<int>> &cache, int n, int size){
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

int dynamicKnapsack(std::vector<int> &sizes, std::vector<int> &values, int n, int size){
	std::vector<std::vector<int>> cache(n + 1, std::vector<int>(size + 1, 0));
	for(int i = 1;i < cache.size(); ++i){
		for(int j = 1;j < cache[i].size(); ++j){
			auto used = (j - sizes[i-1] >= 0) ? (cache[i-1][j-sizes[i-1]] + values[i-1]) : 0;
			cache[i][j] = std::max(cache[i-1][j], used);
		}
	}
	auto temp = dynamicBacktrace(cache, sizes);
	for(int i=0;i<temp.size();++i){
		std::cout<<temp[i]<<" ";
	}
	std::cout<<'\n';

	return cache[n][size];
}

int dynamicLinearKnapsack(std::vector<int> &sizes, std::vector<int> &values, std::vector<bool> &used, int itemsLow, int itemsHigh, int sizeLow, int sizeHigh){
	std::vector<int> kPrevCol(size + 1, 0);
	std::vector<int> kCol(size + 1, 0);
	std::vector<int> kNextCol(size + 1, 0);
	std::vector<std::vector<int>> cache(n + 1, std::vector<int>(size + 1, 0));

	for(int i = 1; i < size + 1; ++i){

	}

	for(int i = 1;i < cache.size(); ++i){
		for(int j = 1;j < cache[i].size(); ++j){
			auto used = (j - sizes[i-1] >= 0) ? (cache[i-1][j-sizes[i-1]] + values[i-1]) : 0;
			cache[i][j] = std::max(cache[i-1][j], used);
		}
	}
	auto temp = dynamicBacktrace(cache, sizes);
	for(int i=0;i<temp.size();++i){
		std::cout<<temp[i]<<" ";
	}
	std::cout<<'\n';

	return cache[n][size];
}

std::vector<bool> dynamicBacktrace(std::vector<std::vector<int>> &cache, std::vector<int> &sizes){
	std::vector<bool> temp(cache.size());
	int i = cache.size() - 1;
	int j = cache[0].size() - 1;
	while(j > 0){
		if(cache[i][j] == cache[i][j - 1]){
			--j;
			continue;
		}
		temp[i] = (cache[i][j] != cache[i-1][j]);
		j = temp[i] ? j - sizes[i - 1] : j;
		--i;
	}
	temp.erase(temp.begin());
	return temp;
}

std::vector<bool> cachingBacktrace(std::vector<std::vector<int>> &cache, std::vector<int> &sizes){
	std::vector<bool> temp(cache.size());
	int i = cache.size() - 1;
	int j = cache[0].size() - 1;
	while(j > 0 && i >= 0){
		if(j > 0 && cache[i][j] == cache[i][j - 1]){
			--j;
			continue;
		}
		if(i > 0){
			temp[i] = (cache[i][j] != cache[i-1][j]);
			j = temp[i] ? j - sizes[i] : j;
		}
		else{
			temp[i] = cache[i][j] > 0 ? true : false;
		}
		--i;
	}
	return temp;
}
