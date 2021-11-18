#include "sort.h"
#include "../util/func.h"

void selection_sort(int* begin, int* end) {
	for (int* i = begin; i < end - 1; ++i) {
		int* select = i;
		for(int* j = i + 1; j < end; ++j)
			if(*select > *j) select = j;
		_swap(*select, *i);
	}
}

void insertion_sort(int* begin, int* end) {
	for (int* i = begin + 1; i < end; ++i) {
		for (int* j = i; j > begin && *j < *(j - 1);
			_swap(*j, *(j - 1)), --j);
	}
}

void bubble_sort(int* begin, int* end) {
	for (int* i = begin; i < end - 1; ++i) {
		bool _swapped = false;
		for (int* j = begin; j < end - (i - begin) - 1; ++j) 
			if (*j > *(j + 1)) {
				_swap(*j, *(j + 1)),
				_swapped = true;
			}
		if(!_swapped) break;
	}
}

void shaker_sort(int* begin, int* end) {
	bool flag = true;
	while(begin < end) {
		int *lastSwapped = begin;
		if(flag) {
			for(int* i = begin; i < end - 1; ++i)
				if(*i > *(i + 1)) _swap(*i, *(i + 1)), lastSwapped = i + 1;
			
			if(lastSwapped == begin) break;
			end = lastSwapped;
		} else {
			for(int* i = end - 1; i > begin; --i)
				if(*i < *(i - 1)) _swap(*i, *(i - 1)), lastSwapped = i;

			if(lastSwapped == begin) break;
			begin = lastSwapped;
		}
		
		flag = 1 - flag;
	}
}

//reference: https://en.wikipedia.org/wiki/Shellsort
//time: 12:05 PM NOV 17 2021
void shell_sort(int* begin, int* end) {

}

void heapfity(int* a, int n, int k) {
	if(2 * k >= n) return;
	int i = 2 * k + 1;
	if(i < n - 1 && a[i] < a[i + 1]) ++i;
	if(i < n && a[k] < a[i]) _swap(a[i], a[k]);
	heapfity(a, n, i);
}

void heap_sort(int* a, int* end) {
	int n = end - a;
	for(int i = n / 2; i >= 0; --i)
		heapfity(a, n, i);
	
	for(int i = n - 1; i > 0; --i) {
		_swap(a[i], a[0]);
		heapfity(a, i, 0);
	}
}

void merge(int* array, int* a, int n, int* b, int m) {
	int i = 0, j = 0;
	while(i < n && j < m)
		if(a[i] < b[j]) array[i + j] = a[i], ++i;
		else array[i + j] = b[j], ++j;

	while (i < n || j < m)
		if(i < n) array[i + j] = a[i], ++i;
		else array[i + j] = b[j], ++j;
}

void merge_sort(int* begin, int* end) {
	int n = end - begin;
	if(n <= 1) return;

	merge_sort(begin, begin + n / 2);
	merge_sort(begin + n / 2, end);

	int* tmp = new int[n];
	merge(tmp, begin, n / 2, begin + n / 2, n - n / 2);
	memcpy(begin, tmp, n * sizeof(int));
	delete[] tmp;
}

int* partition(int* begin, int* end) {
	_swap(*(end - 1), *(begin + rand() % (end - begin - 1) + 1));

	int *iter = begin - 1, *pivot = end - 1;
	for(int* i = begin; i < end - 1; ++i)
		if(*i < *pivot) ++iter, _swap(*iter, *i);
	++iter, _swap(*iter, *pivot);
	return iter;
}

void quick_sort(int* begin, int* end) {
	if(end - begin <= 1) return;
	
	int* pivot = partition(begin, end);
	quick_sort(begin, pivot);
	quick_sort(pivot + 1, end);
}

void counting_sort(int* begin, int* end) {
	int mn = *begin, mx = *begin;

	for (int* i = begin; i < end; ++i)
		mn = _min(mn, *i), mx = _max(mx, *i);
	
	int* count = new int[mx - mn + 1];
	memset(count, 0x00, (mx - mn + 1) * sizeof(int));
	for (int* i = begin; i < end; ++i) 
		count[*i - mn]++;

	for (int i = 1; i <= mx - mn; ++i)
		count[i] += count[i - 1];

	for (int i = mx - mn; i >= 0; --i) {
		while((count[i]--) > (!i ? 0: count[i - 1])) 
			*(begin + count[i]) = i + mn;
	}

	delete[] count;
}

void radix_sort(int* begin, int* end, int k = 30) {
	if(k < 0 || end - begin <= 1) return;
	int* iter = begin - 1;

	for(int* i = begin; i < end; ++i) {
		if (!(*i >> k & 1)) _swap(*++iter, *i); 
	}

	radix_sort(begin, ++iter, k - 1);
	radix_sort(iter, end, k - 1);
}

void radix_sort(int* begin, int* end) {
	radix_sort(begin, end, 31);
}

void flash_sort(int* begin, int* end) {
	int mx = *begin, mn = *begin;

}

sort_func_pointer parse(const std::string& s) {
	if(s == "Selection Sort")
		return selection_sort;
	
	if(s == "Insertion Sort")
		return insertion_sort;
	
	if(s == "Shaker Sort")
		return shaker_sort;
	
	if(s == "Bubble Sort")
		return bubble_sort;
	
	if(s == "Shell Sort")
		return shell_sort;
	
	if(s == "Heap Sort")
		return heap_sort;
	
	if(s == "Merge Sort")
		return merge_sort;
	
	if(s == "Quick Sort")
		return quick_sort;
	
	if(s == "Counting Sort")
		return counting_sort;
	
	if(s == "Radix Sort")
		return radix_sort;
	
	if(s == "Flash Sort")
		return flash_sort;
	
	return nullptr;
}