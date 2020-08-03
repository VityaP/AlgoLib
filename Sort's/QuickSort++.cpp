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
#include <cstdlib>
#include <ctime>

template<class X>
inline int Partition(std::vector<X> &nums,const int &p,const int &r){
	
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
inline int RandomizedPartition(std::vector<X> &nums,const int &p,const int &r){
	
	int mod = (r - p);
	int index;
	int index1 = p + rand() % mod;
	int index2 = p + rand() % mod;
	if (nums[index1] < nums[index2]){
		index = index1;
	}
	else{
		index = index2;
	}
	X temp = nums[index];
	nums[index] = nums[r];
	nums[r] = temp;
	return Partition(nums,p,r);
	
}

template <class X> 
void InsertionSort( std::vector<X> &data,int start,int end){
		
	for(int i = start;i <= end; ++i){
		X key = data[i];
		int t = i - 1;
		while ( t >= start && data[t] > key ){
			data[t + 1] = data[t];
			--t;
		}
		data[t + 1] = key;
	}
	
	return;
}

const int N = 512;
//this will make algorithm 
//more efficient(quicker) by 10-15%
template<class X>
void QuickSortPart(std::vector<X> &nums,const int &p,const int &r){
	if (p < r){
		if ( r - p > N){
			int q = RandomizedPartition(nums,p,r);
			QuickSortPart(nums,p,q - 1);
			QuickSortPart(nums,q + 1,r);
		}
		else{
			InsertionSort(nums,p,r);
		}
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
	
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	
	time_t start = time(NULL);
	int n = 1000000;
	std::vector<int> g(n,0);
	srand(time(NULL));
	for(int i = 0; i < n ; ++i ){
		g[i] = rand() % 40000000;
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
