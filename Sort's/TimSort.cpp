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

const int N = 16;
//this will make algorithm 
//more efficient(quicker) by 10-15%
template <class X> 
void MergeSort( std::vector<X> &data,int p,int q){
	if( p < q){	
		if ( q - p > N){
			int mid = (p + q)/2;
			MergeSort(data,p,mid);
			MergeSort(data,mid + 1,q);
			Merge(data,p,mid,q);
		}
		else{
			InsertionSort(data,p,q);
		}
	}
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
	MergeSort(g,0,n);
	bool flag = false;
	for(int i = 1; i < n ; ++i ){
		if ( g[i] < g[i-1] ){
			flag = true;
			break;
		}
	}
	time_t end = time(NULL);
	start = end - start;
	std::cout << start << "\t" ;
	if (flag){
		std::cout << "Not correct\n" ;
	}
	else{
		std::cout << "Correct\n";
	}
	
	return 0;
}
