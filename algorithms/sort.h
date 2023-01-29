#ifndef SORT_H
#define SORT_H

#include <string>
#include <cstring>
#include <functional>
#include <unordered_map>


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
class sort {

public:
    
    static void selection_sort(int* begin, int* end);

    static void insertion_sort(int* begin, int* end);

    static void bubble_sort(int* begin, int* end);

    static void shaker_sort(int* begin, int* end);

    static void shell_sort(int* begin, int* end);

    static void heap_sort(int* begin, int* end);

    static void merge_sort(int* begin, int* end);

    static void quick_sort(int* begin, int* end);

    static void counting_sort(int* begin, int* end);

    static void radix_sort(int* begin, int* end);

    static void flash_sort(int* begin, int* end);

    static const std::unordered_map<std::string, std::function<void(int*, int*)>> info;
};

#endif
