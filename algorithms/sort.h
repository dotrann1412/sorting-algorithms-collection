#ifndef SORT_H
#define SORT_H

#include <string>
#include <cstring>

/*
 * all of these sorting functions sort the array
 * with index starts from zeroes
 * and receive the pointer of the first and after last element 
 * of array to run. [first, last)
 *
 * the function parse(std::string) return the sort 
 * function with name present under a string;
 * -> quickly use with a loop when statistic and bench test
 * (more clearly, this function used to map a string 
 * with a corresponding function)
 */

typedef void (*sort_func_pointer)(int*, int*);

void selection_sort(int* begin, int* end);

void insertion_sort(int* begin, int* end);

void bubble_sort(int* begin, int* end);

void shaker_sort(int* begin, int* end);

void shell_sort(int* begin, int* end);

void heap_sort(int* begin, int* end);

void merge_sort(int* begin, int* end);

void quick_sort(int* begin, int* end);

void counting_sort(int* begin, int* end);

void radix_sort(int* begin, int* end);

void flash_sort(int* begin, int* end);

sort_func_pointer parse(const std::string& s);

///////////////////////////////////////////////////////////////////////
///////////////all of these function used of statistic/////////////////
///////////////  not recommended use when speed test  /////////////////

typedef void (*_sort_func_pointer)(int*, int*, long long&);

void selection_sort(int* begin, int* end, long long& cmpCount);

void insertion_sort(int* begin, int* end, long long& cmpCount);

void bubble_sort(int* begin, int* end, long long& cmpCount);

void shaker_sort(int* begin, int* end, long long& cmpCount);

void shell_sort(int* begin, int* end, long long& cmpCount);

void heap_sort(int* begin, int* end, long long& cmpCount);

void merge_sort(int* begin, int* end, long long& cmpCount);

void quick_sort(int* begin, int* end, long long& cmpCount);

void counting_sort(int* begin, int* end, long long& cmpCount);

void radix_sort(int* begin, int* end, long long& cmpCount);

void flash_sort(int* begin, int* end, long long& cmpCount);

_sort_func_pointer _parse(const std::string& s);

#endif
