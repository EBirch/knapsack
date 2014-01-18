#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

int main(){
	const int KNAPSIZE = 1000;
	const int MAXSIZE = 100;
	const int MAXVAL = 100;
	const int ITEMS = 6;
	std::uniform_int_distribution<> sizeDist(1, MAXSIZE);
	std::uniform_int_distribution<> valDist(1, MAXVAL);
	std::mt19937 rng(time(NULL));
	std::vector<int> sizes(ITEMS);
	std::vector<int> values(ITEMS);
	std::generate(sizes.begin(), sizes.end(), [&](){return sizeDist(rng);});
	std::generate(values.begin(), values.end(), [&](){return valDist(rng);});
}
