#ifndef _SelectionSort_
/* 	_SelectionSort_
	time O(N^2)
	memory O(N)
*/
#define _SelectionSort_
#include <vector>
#include <iostream>

template <class X> 
std::vector<X> SelectionSort( std::vector<X> &data){
		
	int Size = data.size();
	std::vector<X> answer(Size,0);
	X max = data.back();
	X min = data.back();
	int index = Size -1;;
	for(int i = 0;i < Size; ++i){
		if(data[i] > max){
			max = data[i];
		}
		if(data[i] < min){
			min = data[i];
			index = i;
		}
	}
	answer[0] = min;
	data[index] = max;
	min = data.back();
	for(int k = 1; k < Size ; ++k){
		min = max;
		for(int i = 0; i < Size; ++i){
			if(data[i] <= min){
			min = data[i];
			index = i;
			}
		}
		answer[k] = min;
		data[index] = max;
	}
	
	return answer;
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
	g = SelectionSort(g);
	std::cout << "\n";
	for(int i = 0; i < 6 ; ++i ){
		std::cout << g[i] << "\t";
	}
	
}
