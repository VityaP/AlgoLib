#ifndef _CountingSort_
/* 	_CountingSort_
	time O(N)
	memory O(N)
*/
#define _CountingSort_
#include <vector>
#include <iostream>

template<class X>


#endif


#include<iostream>
#include<ctime>
#include<cstdlib>
int main(){
	
	time_t start = time(NULL);
	int n = 10000000;
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
