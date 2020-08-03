#ifndef _InsertionSort_
/* 	_InsertionSort_
	time O(N^2)
	memory O(N)
*/
#define _InsertionSort_
#include <vector>
#include <iostream>

template <class X> 
std::vector<X> InsertionSort( std::vector<X> &data){
		
	for(int i = 0;i < data.size(); ++i){
		X key = data[i];
		int t = i - 1;
		while ( t >= 0 && data[t] < key ){
			data[t + 1] = data[t];
			--t;
		}
		data[t + 1] = key;
	}
	
	return data;
}

#endif


#include<iostream>
#include<ctime>
#include<cstdlib>
int main(){
		
	std::vector<int> g(6,0);
	srand(time(NULL));
	for(int i = 0; i < 6 ; ++i ){
		std::cout << g[i] << "\t";
	}
	for(int i = 0; i < 6 ; ++i ){
		g[i] = rand() % 1000;
	}
	InsertionSort(g);
	std::cout << "\n";
	for(int i = 0; i < 6 ; ++i ){
		std::cout << g[i] << "\t";
	}
	
}
