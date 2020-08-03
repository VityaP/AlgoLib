#ifndef _QuickSort_
/* 	
	_QuickSort_
	time O(N^2)
	aprox time O(N*log(N))
	memory O(N)

*/
#define _QuickSort_
#include <vector>
#include <iostream>


template<class X>
int Partition(std::vector<X> &nums,int p,int r){
	
	X x = nums[r];
	int i = p - 1;
	
	for(int j = p; j <= r-1; ++j){
		if ( nums[j] < x){
			++i;
			X temp = nums[i];
			nums[i] = nums[j];
			nums[j] = temp;
		}
	}
	
	++i;
	X temp = nums[i];
	nums[i] = nums[r];
	nums[r] = temp;
	return i;
}

template<class X>
void QuickSortPart(std::vector<X> &nums,int p,int r){
	if (p < r){
		int q = Partition(nums,p,r);
		QuickSortPart(nums,p,q - 1);
		QuickSortPart(nums,q + 1,r);
	}
}

template<class X>
void QuickSort(std::vector<X> &nums){
	int Size = nums.size() - 1;
	QuickSortPart(nums,0,Size);
}

#endif


#include<iostream>
#include<ctime>
#include<cstdlib>
int main(){
	
	time_t start = time(NULL);
	int n = 100000000;
	std::vector<int> g(n,0);
	srand(time(NULL));
	for(int i = 0; i < n ; ++i ){
		g[i] = rand() % 1000;
	}
	
	QuickSort(g);

	bool flag = true;
	for(int i = 1; i < n ; ++i ){
		if ( g[i] < g[i-1] ){
			flag = false;
			std::cout << i <<"\t";
		}
	}
	
	time_t end = time(NULL);
	start = end - start;
	std::cout << start << "\t" ;
	
	if (flag){
		std::cout << "Correct\n";
	}
	else{
		std::cout << "Not correct\n" ;
	}
	
	return 0;
}
