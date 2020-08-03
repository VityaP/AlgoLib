#ifndef _MergeSort_
/* 	_MergeSort_
	time O(N*log(N))
	memory O(N)
*/
#define _MergeSort_
#include <vector>
#include <iostream>

template <class X>
void Merge( std::vector<X> &data,int p,int q,int r){
	
	int left_part = p;
	int right_part = q + 1;
	std::vector<X> answer(r - p + 1);
	int k = 0;
	while( left_part <= q && right_part <= r){
		if( data[left_part] < data[right_part] ){
			answer[k] = data[left_part];
			++k;
			++left_part;
		}
		else{
			answer[k] = data[right_part];
			++k;
			++right_part;
		}
	}
	
	while( right_part <= r){
		answer[k] = data[right_part];
		++k;
		++right_part;
	}

	while( left_part <= q){
		answer[k] = data[left_part];
		++k;
		++left_part;
	}
	
	k = 0;
	for(int i = p; i <= r; ++i){
		data[i] = answer[k];
		++k;
	}
	
	return;
	
}

template <class X> 
void MergeSort( std::vector<X> &data,int p,int q){
	if( p < q){
		int mid = (p + q)/2;
		MergeSort(data,p,mid);
		MergeSort(data,mid + 1,q);
		Merge(data,p,mid,q);
	}
}

#endif


#include<iostream>
#include<ctime>
#include<cstdlib>
int main(){
	
	int n = 8;
	std::vector<int> g(n,0);
	srand(time(NULL));
	for(int i = 0; i < n ; ++i ){
		std::cout << g[i] << "\t";
	}
	std::cout << "\n";
	for(int i = 0; i < n ; ++i ){
		g[i] = rand() % 1000;
	}
	for(int i = 0; i < n ; ++i ){
		std::cout << g[i] << "\t";
	}
	std::cout << "\n";
	MergeSort(g,0,n);
	std::cout << "\n";
	for(int i = 0; i < n ; ++i ){
		std::cout << g[i] << "\t";
	}
	
}
