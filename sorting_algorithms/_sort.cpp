#include "sort.h"
#include "../utils/func.h"

/*
 * I'm not copy any of code version on the internet
 * I just read the idea and implement it on my own 
 * contact me if you see bugs in my code, thanks <3
 * email: dotrann.1412@gmail.com
 */

void selection_sort(int* begin, int* end, long long& cmpCount) {
	for (int* i = begin; ++cmpCount && i < end - 1; ++i) {
		int* select = i;
		for(int* j = i + 1;++cmpCount &&  j < end; ++j)
			if(++cmpCount && *select > *j) select = j;
		_swap(*select, *i);
	}
}

void insertion_sort(int* begin, int* end, long long& cmpCount) {
	for (int* i = begin + 1; ++cmpCount && i < end; ++i) {
		int hold = *i, *j = i;
		for (;++cmpCount && j > begin && ++cmpCount && hold < *(j - 1); --j) 
			*j = *(j - 1);
		*j = hold;
	}
}

// basic idea - optimized with check the last time swapped
void bubble_sort(int* begin, int* end, long long& cmpCount) {
	for(int* i = end - 1; ++cmpCount && i > begin; --i) {
		int* lastswapped = begin - 1;
		for(int* j = begin;++cmpCount && j < i; ++j) {
			if(++cmpCount && *j > *(j + 1)) 
				_swap(*j, *(j + 1)), lastswapped = j + 1;
		}

		if(++cmpCount && lastswapped == begin - 1) break;
		i = lastswapped;
	}
}

// expand idea from bubble sort
void shaker_sort(int* begin, int* end, long long& cmpCount) {
	while(++cmpCount && begin < end) {
		int *lastSwapped = begin;
		for(int* i = begin;++cmpCount && i < end - 1; ++i)
			if(++cmpCount && *i > *(i + 1)) _swap(*i, *(i + 1)), lastSwapped = i + 1;
		
		if(++cmpCount && lastSwapped == begin) break;
		end = lastSwapped;

		lastSwapped = end;
		for(int* i = end - 1;++cmpCount && i > begin; --i)
			if(++cmpCount && *i < *(i - 1)) _swap(*i, *(i - 1)), lastSwapped = i;

		if(++cmpCount && lastSwapped == end) break;
		begin = lastSwapped;
	}
}

// reference: https:// en.wikipedia.org/wiki/Shellsort
// time: 12:05 PM NOV 17 2021
void shell_sort(int* begin, int* end, long long& cmpCount) {
	int n = end - begin;
	for(int gap = n / 2; ++cmpCount && gap; gap /= 2) {
		// use insertion with step = gap to sort all sublist of array using insertion sort
		// idx: [0..10], gap = 2: -> 2 sublists: 0 2 4 6 8 10 and 1 3 5 7 9
		for(int* i = begin + gap;++cmpCount && i < end; ++i) {
			int hold = *i, *j = i;
			for(;++cmpCount && j >= begin + gap && ++cmpCount &&  hold < *(j - gap); j -= gap)
				*j = *(j - gap);
			*j = hold;
		}
	}
}

// reference: Mr.Phuong
// but: this is heapify recursion version
void heapify(int* a, int n, int k, long long& cmpCount) {
	if(++cmpCount && 2 * k >= n) return;
	int i = 2 * k + 1;

	if(++cmpCount && i < n - 1 && ++cmpCount && a[i] < a[i + 1]) ++i;
	if(++cmpCount && i < n && ++cmpCount && a[k] < a[i]) _swap(a[i], a[k]);
	
	heapify(a, n, i, cmpCount);
}

void heap_sort(int* a, int* end, long long& cmpCount) {
	int n = end - a;
	// this step used to build max heap
	// we start from n / 2 because half of the last array is a natural heap
	for(int i = n / 2 - 1;++cmpCount && i >= 0; --i)
		heapify(a, n, i, cmpCount);
	
	for(int i = n - 1;++cmpCount && i > 0; --i) {
		_swap(a[i], a[0]);
		heapify(a, i, 0, cmpCount);
	}
}


// reference: Mr.MinhHuy
// the main idea is use divide and conquer to sort the left side 
// and right side then merge it 
// suppose that the array with exactly 1 element is always sorted
void merge(int* array, int* a, int n, int* b, int m, long long& cmpCount) {
	int i = 0, j = 0;
	while(++cmpCount && i < n && ++cmpCount && j < m)
		if(++cmpCount && a[i] < b[j]) array[i + j] = a[i], ++i;
		else array[i + j] = b[j], ++j;

	while(++cmpCount && i < n) array[i + j] = a[i], ++i;
	while(++cmpCount && j < m) array[i + j] = b[j], ++j;
}

void merge_sort(int* begin, int* end, long long& cmpCount) {
	int n = end - begin; // size of array
	if(++cmpCount && n <= 1) return;

	merge_sort(begin, begin + n / 2, cmpCount);
	merge_sort(begin + n / 2, end, cmpCount);

	int* tmp = new int[n];
	merge(tmp, begin, n / 2, begin + n / 2, n - n / 2, cmpCount);
	memcpy(begin, tmp, n * sizeof(int));
	delete[] tmp;
}


// this partition function choose a random pivot to reduce the probability of
// value of the chosen value is the max or min of all element in array
// and then partition all the element with value less than value of pivot to leftside
// return pointer point to the index of pivot -> pivot was in the right position in the array
int* partition(int* begin, int* end, long long& cmpCount) {
	_swap(*(end - 1), *(begin + rand() % (end - begin - 1) + 1));

	int *iter = begin - 1, *pivot = end - 1;
	for(int* i = begin;++cmpCount && i < end - 1; ++i)
		if(++cmpCount && *i < *pivot) ++iter, _swap(*iter, *i);

	++iter, _swap(*iter, *pivot);
	return iter;
}

// the idea of quick sort is use devide and conquer 
void quick_sort(int* begin, int* end, long long& cmpCount) {
	if(++cmpCount && end - begin <= 1) return;
	
	int* pivot = partition(begin, end, cmpCount);
	quick_sort(begin, pivot, cmpCount);
	quick_sort(pivot + 1, end, cmpCount);
	// pivot + 1 because the value of pivot is in the right position in the array
}

// idea: Mr.Phuong
// find max min of array to reduce memory usage of algorithms in some special case
void counting_sort(int* begin, int* end, long long& cmpCount) {
	int mn = *begin, mx = *begin;

	for (int* i = begin; ++cmpCount && i < end; ++i)
		mn = _min(mn, *i), mx = _max(mx, *i), ++cmpCount, ++cmpCount;// 2 comparison here
	
	// _count not count because count was declared as a function in many librarys
	int* _count = new int[mx - mn + 1]; 
	memset(_count, 0x00, (mx - mn + 1) * sizeof(int));

	for (int* i = begin;++cmpCount && i < end; ++i) 
		_count[*i - mn]++;

	for (int i = 1;++cmpCount && i <= mx - mn; ++i)
		_count[i] += _count[i - 1];

	for (int i = mx - mn;++cmpCount && i >= 0; --i) {
		while(++cmpCount &&  (_count[i]--) > ((++cmpCount && !i) ? 0: _count[i - 1])) 
			*(begin + _count[i]) = i + mn;
	}

	delete[] _count;
}


// this radix_sort version is sort the number in base 2
// ->dont need to define another function to get the k'th ditgit of number, ...
// just use to sort the positive integer array
void radix_sort(int* begin, int* end, long long& cmpCount, int k = 30) {
	if(++cmpCount && k < 0 || ++cmpCount && end - begin <= 1) return;

	// arrange all element with k'th bit = 0 to the left side
	// then use recursion to sort all the element in the left side, and the right side
	// base on (k - 1)'th bit until k return to zero or the array's size have 
	// exactly 0 or 1 element
	int* iter = begin - 1;
	for(int* i = begin;++cmpCount && i < end; ++i)
		if (++cmpCount && !(*i >> k & 1)) _swap(*++iter, *i); 

	radix_sort(begin, ++iter, cmpCount, k - 1);
	radix_sort(iter, end, cmpCount, k - 1);
}

void radix_sort(int* begin, int* end, long long& cmpCount) {
	int rmsb = 0; // rmsb: right most set bit
	for(int* i = begin;++cmpCount && i < end; ++i)
		for(int j = 30; ++cmpCount && j >= 0; --j)
			if(++cmpCount && *i >> j & 1) {
				// if k'th bit of number *i is 1 -> check and break
				rmsb = _max(rmsb, j);
				break;
			}

	radix_sort(begin, end, cmpCount, rmsb);
	// to return as a function pointer with format void(int*, int*) instead of void(int*, int*, int)
}


// reference: idea from Mr.Phuong - pointer only version
void flash_sort(int* begin, int* end, long long& cmpCount) {
	int mx = *begin, mn = *begin;

	// Mr.Phuong said 0.43 is the best value for this algorithm
	int layers_count = 0.43 * (end - begin);
	
	for(int* i = begin;++cmpCount && i < end; ++i)
		mx = _max(*i, mx), mn =  _min(mn, *i);
	
	int* layer = new int[layers_count];
	memset(layer, 0x00, layers_count * sizeof(int));

	// return level of the element with value = *element
	auto level = [&](int k) -> int {
		return (1.0 * (k - mn) / (mx - mn)) * (layers_count - 1);
	};
	
	// statistic how many element 
	for(int* i = begin;++cmpCount && i < end; ++i)
		layer[level(*i)]++;

	// find position of last element of each layer
	for(int i = 1;++cmpCount && i < layers_count; ++i) 
		layer[i] += layer[i - 1];
	
	int *idx = begin;
	while(++cmpCount && idx < end - 1) {
		// rerange elements overall layers
		while(++cmpCount  && idx < end - 1 
			&& ++cmpCount && idx - begin > layer[level(*idx)] - 1)
			++idx;
		
		if(++cmpCount && idx >= end - 1) break;

 		while(++cmpCount && idx - begin != layer[level(*idx)] - 1)
			_swap(*idx, begin[--layer[level(*idx)]]);

		// idx return in the correct position --> decreasing the last element of layer *idx;
		--layer[level(*idx)]; ++idx;
	}

	// use insertion sort to rerange elements on every layers
	insertion_sort(begin, end, cmpCount);
	delete[] layer;
}

_sort_func_pointer _parse(const std::string& s) {
	if(s == "selection-sort")
		return selection_sort;
	
	if(s == "insertion-sort")
		return insertion_sort;
	
	if(s == "shaker-sort")
		return shaker_sort;
	
	if(s == "bubble-sort")
		return bubble_sort;
	
	if(s == "shell-sort")
		return shell_sort;
	
	if(s == "heap-sort")
		return heap_sort;
	
	if(s == "merge-sort")
		return merge_sort;
	
	if(s == "quick-sort")
		return quick_sort;
	
	if(s == "counting-sort")
		return counting_sort;
	
	if(s == "radix-sort")
		return radix_sort;
	
	if(s == "flash-sort")
		return flash_sort;
	
	return nullptr;
}