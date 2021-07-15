#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <algorithm>

#include "profile.h"
using namespace std;

template<typename type>
class Heap{
private:
    int _size;
    int _capacity;
    bool _less;
    type* ptr;
protected:
    int parent(int i){
        return (i - 1)/2;
    }

    void checkSize(){
        if( _size == _capacity ){
            type* tmp = new type[2 * _capacity];
            for(int i = 0; i < _size; ++i){
                tmp[i] = ptr[i];
            }
            delete [] ptr;
            _capacity = 2 * _capacity;
            ptr = tmp;
        }
    }

    void siftUp(int idx){
        if( _less == true ){
            while( (idx > 0) && (ptr[idx] < ptr[parent(idx)]) ){
                swap(ptr[idx], ptr[parent(idx)]);
                idx = parent(idx);
            }
        }
        else{
            while( (idx > 0) && (ptr[idx] > ptr[parent(idx)]) ){
                swap(ptr[idx], ptr[parent(idx)]);
                idx = parent(idx);
            }
        }
    }

    void siftDown(int idx){
        int j;
        if( _less == true ){
            while( true ){
                j = idx;
                if( (2 * idx + 1 < _size) && (ptr[2 * idx + 1] < ptr[j]) ){
                    j = 2 * idx + 1;
                }
                if( (2 * idx + 2 < _size) && (ptr[2 * idx + 2] < ptr[j]) ){
                    j = 2 * idx + 2;
                }
                if( j == idx ){
                    break;
                }
                swap(ptr[idx], ptr[j]);
                idx = j;
            }
        }
        else{
            while( true ){
                j = idx;
                if( (2 * idx + 1 < _size) && (ptr[2 * idx + 1] > ptr[j]) ){
                    j = 2 * idx + 1;
                }
                if( (2 * idx + 2 < _size) && (ptr[2 * idx + 2] > ptr[j]) ){
                    j = 2 * idx + 2;
                }
                if( j == idx ){
                    break;
                }
                swap(ptr[idx], ptr[j]);
                idx = j;
            }
        }
    }
public:
    Heap(){
        _size = 0;
        _capacity = 0;
        _less = true;
        ptr = NULL;
    }
    Heap(int n, bool cmpLess = true){
        _size = 0;
        _capacity = n;
        _less = cmpLess;
        ptr = new type[n];
    }

    Heap(const type* array, int n, bool cmpLess = true){
        _size = n;
        _capacity = n;
        _less = cmpLess;
        ptr = new type[n];
        for(int i = 0; i < n; ++i){
            ptr[i] = array[i];
        }
        // for(int i = n - 1; i >= 0; --i){
        //     siftDown(i);
        // }
        //
        // small optimization
        // ptr[(n/2) + 1] ... ptr[n - 1] are leafs
        // so we can skip them
        for(int i = n/2; i >= 0; --i){
            siftDown(i);
        }
    }

    int size() const{
        return _size;
    }

    bool empty() const{
        if(_size == 0){
            return true;
        }
        return false;
    }

    type getTop() const{
        if( _size == 0 ){
            throw runtime_error("Already Empty\n");
        }
        return ptr[0];
    }

    void insert(type val){
        checkSize();
        ptr[_size++] = val;
        siftUp(_size - 1);
    }

    void removeTop(){
        if( _size == 0 ){
            throw runtime_error("Already Empty\n");
        }
        swap(ptr[0], ptr[--_size]);
        siftDown(0);
    }

    ~Heap(){
        if( _capacity != 0 ){
            delete [] ptr;
        }
        _capacity = 0;
        _size = 0;
    }
};


class sortClass{

protected:

    template<typename type>
    void Merge(type* a, int p, int q, int s){
        //  [l..r]
        int l = p;
        int r = q + 1;
        type* tmp = new type[s - p + 1];
        int idx = 0;
        while( (l <= q) && (r <= s) ){
            if( a[l] < a[r] ){
                tmp[idx] = a[l];
                ++l;
            }
            else{
                tmp[idx] = a[r];
                ++r;
            }
            ++idx;
        }
        for(int i = ((l > q) ? r : l); idx <= (s - p); ++i){
            tmp[idx++] = a[i];
        }
        for(int i = 0; i <= (s - p); ++i){
            a[p + i] = tmp[i];
        }
        delete [] tmp;
        return;
    }

    template<typename type>
    void MergeSort(type* a, int l, int r){
        //  [l..r]
        if( l >= r ){
            return;
        }
        int mid = (l + r)/2;
        MergeSort(a, l, mid);
        MergeSort(a, mid + 1, r);
        Merge(a, l, mid, r);
    }

    template<typename type>
    void TimSort(type* a, int l, int r){
        //  [l..r]
        if( r - l <= 32 ){
            InsertionSort(a + l, r - l + 1);
            return;
        }
        int mid = (l + r)/2;
        TimSort(a, l, mid);
        TimSort(a, mid + 1, r);
        Merge(a, l, mid, r);
    }

    template<typename type>
    pair<int, int> Partition(type* a, int l, int r, int pivot){
        int m1 = l;
        int m2 = l;
        for(int i = l; i < r; ++i){
            if( a[i] < pivot ){
                swap(a[i], a[m1]);
                ++m1;
                swap(a[i], a[m2]);
                ++m2;
            }
            else if( a[i] == pivot ){
                swap(a[i], a[m2]);
                ++m2;
            }
        }
        return make_pair(m1, m2);
    }

    template<typename type>
    int RandomizedPartition(type* a, int l, int r){
        // [l .. r)
        swap(a[r - 1], a[l + (rand() % (r - l))]);
        type pivot = a[r - 1];

        int m = l - 1;
        for(int i = l; i < r; ++i){
            if( a[i] < pivot ){
                swap(a[++m], a[i]);
            }
        }
        swap(a[++m], a[r - 1]);
        return m;
    }

    template<typename type>
    void QuickSort(type* a, int l, int r){
        // [l, r - 1]
        if( l + 1 >= r){
            return;
        }
        int value = a[l];
        auto mid = Partition(a, l, r, value);
        QuickSort(a, l, mid.first);
        QuickSort(a, mid.second, r);
    }

public:

    template<typename type>
    type* Select(type* a, int l, int r, int idx){
        // [l .. r)
        // cerr << "info " << l << " " << r << " " << idx << "\n";
        if( l + 1 == r ){
            return &a[l];
        }
        int q = RandomizedPartition(a, l, r);
        int k = q - l;
        if( idx == k ){
            return &a[q];
        }
        if( idx < k ){
            return Select(a, l, q, idx);
        }
        else{
            return Select(a, q + 1, r, idx - (k + 1) );
        }
    }

    template<typename type>
    void CountingSort(type* a, int n){

        type k = 1 + *max_element(a, a + n);
        int* tmp = new int[k];
        for(int i = 0; i < k; ++i){
            tmp[i] = 0;
        }
        for(int i = 0; i < n; ++i){
            ++tmp[a[i]];
        }
        for(int i = 1; i < k; ++i){
            tmp[i] += tmp[i - 1];
        }
        
        type* B = new type[n];
        for(int i = n - 1; i >= 0; --i){
            B[--tmp[a[i]]] = a[i];
        }
        for(int i = 0; i < n; ++i){
            a[i] = B[i];
        }
        delete [] tmp;
        delete [] B;
    }

    template<typename type>
    void BucketSort(type* a, int n){

        vector<vector<type>> nums(n);
        for(int i = 0; i < n; ++i){
            nums[i].reserve(1024);
        }
        type max = *max_element(a, a + n);
        type min = *min_element(a, a + n);
        for(int i = 0; i < n; ++i){
            long long idx = (long long) n * (a[i] - min) / max;  // idx = n * [0 .. 1)
            nums[idx].push_back(a[i]);
        }
        for(int i = 0; i < n; ++i){
            sort(nums[i].begin(), nums[i].end());
        }
        int k = 0;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < nums[i].size(); ++j){
                a[k++] = nums[i][j];
            }
        }
    }

    template<typename type>
    void MergeSort(type* a, int n){
        MergeSort(a, 0, n - 1);
    }

    template<typename type>
    void TimSort(type* a, int n){
        TimSort(a, 0, n - 1);
    }

    template<typename type>
    void HeapSort(type* a, int n){

        Heap<type> tmp(a, n);   // O(N)

        // Heap<type> tmp(n);   // O(N * log(N)
        // for(int i = 0; i < n; ++i){
        //     tmp.insert(a[i]);
        // }

        for(int i = 0; i < n; ++i){ // O(N * log(N)
            a[i] = tmp.getTop();
            tmp.removeTop();
        }
    }

    template<typename type>
    void QuickSort(type* a, int n){
        QuickSort(a, 0, n);
    }

    template<typename type>
    void InsertionSort(type* a, int n) {
        type key;
        for (int i = 1; i < n; i++) {
            key = a[i];
            int j = i - 1;
            while( (j >= 0) && (a[j] > key) ){
                a[j + 1] = a[j];
                --j;
            }
            a[j + 1] = key;
        }
        return;
    }

    template<typename type>
    void SelectionSort(type* a, int n){

        int minIdx;
        type minValue;
        for(int i = 0; i < n; ++i){
            minValue = a[i];
            minIdx = i;
            for(int j = i + 1; j < n; ++j){
                if( a[j] < minValue ){
                    minValue = a[j];
                    minIdx = j;
                }
            }
            swap(a[i], a[minIdx]);
        }
    }

    template<typename type>
    string checkDifference(type *A, type *standart, int n){
        bool ok = true;
        for(int i = 0; i < n; ++i){
            if( A[i] != standart[i] ){
                ok = false;
                break;
            }
        }
        if( ok == true ){
            return "OK\n";
        }
        else{
            return "ERROR\n";
        }
    }
};



int main(){

    ios::sync_with_stdio(false);
    cin.tie(0);

    sortClass obj;

    int n;
    cin >> n;

    int* A = new int[n];
    int* B = new int[n];
    int* standart = new int[n];

    srand(time(NULL));
    for(int i = 0; i < n; ++i){
        A[i] = 1 + (rand() % n);
        // A[i] = (rand() % 10000000) - 500000;
        B[i] = A[i];
        standart[i] = A[i];
    }

    {
        LOG_DURATION("StandartSort")
        sort(standart, standart + n);
    }

    {
        LOG_DURATION("Select")
        int idx = rand() % n;
        if( *obj.Select(A, 0, n, idx) != standart[idx] ){
            cout << idx << " " << A[idx] << " " << standart[idx] << "\n";
            abort();
        }
    }
    


    {
        LOG_DURATION("InsertionSort")
        obj.InsertionSort(A, n);
    }
    cout << obj.checkDifference(A, standart, n);

    copy(B, B + n, A);
    {
        LOG_DURATION("SelectionSort")
        obj.SelectionSort(A, n);
    }
    cout << obj.checkDifference(A, standart, n);

    copy(B, B + n, A);
    {
        LOG_DURATION("MergeSort")
        obj.MergeSort(A, n);
    }
    cout << obj.checkDifference(A, standart, n);

    copy(B, B + n, A);
    {
        LOG_DURATION("TimSort")
        obj.TimSort(A, n);
    }
    cout << obj.checkDifference(A, standart, n);

    copy(B, B + n, A);
    {
        LOG_DURATION("HeapSort")
        obj.HeapSort(A, n);
    }
    cout << obj.checkDifference(A, standart, n);

    copy(B, B + n, A);
    {
        LOG_DURATION("QuickSort")
        obj.QuickSort(A, n);
    }
    cout << obj.checkDifference(A, standart, n);

    copy(B, B + n, A);
    {
        LOG_DURATION("CountingSort")
        obj.CountingSort(A, n);
    }
    cout << obj.checkDifference(A, standart, n);

    copy(B, B + n, A);
    {
        LOG_DURATION("BucketSort");
        obj.BucketSort(A, n);
    }
    cout << obj.checkDifference(A, standart, n);

    delete [] A;
    delete [] B;
    delete [] standart;

    return 0;
}