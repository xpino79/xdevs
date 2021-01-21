/* dnf install gcc-toolset-10 */
/* gcc -std=c++17 -lstdc++ -ltbb -fopenmp */

#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <execution>
#include <iostream>
#include <chrono>
#include <mutex>

/* 병렬 실행을 지원하는 표준 알고리즘
adjacent_difference, adjacent_find, all_of, any_of, 
copy, copy_if, copy_n, count, count_if, 
equal, exclusive_scan, 
fill, fill_n, find, find_end, find_first_of, find_if, find_if_not, for_each, for_each_n, 
generate, generate_n, 
includes, inclusive_scan, inner_product, inplace_merge, , is_heap, is_heap_until, is_partitioned, is_sorted, is_sorted_until, 
lexicographical_compare, 
max_element, merge, min_element, minmax_element, mismatch, move, 
none_of, nth_element, 
partial_sort, partial_sort_copy, partition, partition_copy, 
reduce, remove, , remove_copy, remove_copy_if, remove_if, replace, replace_copy, replace_copy_if, replace_if, reverse, reverse_copy, rotate, rotate_copy, 
search, search_n, set_difference, set_intersection, set_symmetric_difference, set_union, sort, stable_partition, stable_sort, swap_ranges, 
transform, transform_exclusive_scan, transform_inclusive_scan, transform_reduce, 
uninitialized_copy, uninitialized_copy_n, uninitialized_fill, uninitialized_fill_n, unique, unique_copy
*/

void _My_pstl_for_each()
{
    int _Sum{0};
    std::mutex _Mutex;

    std::vector<int> _Vec = {1, 2, 3};
    std::for_each(std::execution::par, std::begin(_Vec), std::end(_Vec),
                  [&](auto _Num) {
                      std::lock_guard _Lock(_Mutex);
                      Sum += _Num;
                  });
    
    std::map<int, int> _Map{{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    std::for_each(std::execution::par, std::begin(_Map), std::end(_Map),
                  [](const auto &_Pair) {
                      // std::cout << "first " << _Pair.first << " second " << _Pair.second << std::endl;
                      std::lock_guard _Lock(_Mutex);
                      Sum += _Pair.second;
                  });
    
}

void _My_pstl_remove()
{
    std::vector<int> _Vec;
    _Vec.push_back(3);
    _Vec.push_back(1);
    _Vec.push_back(2);
    _Vec.push_back(3);
    // _Vec.erase(std::remove(_Vec.begin(), _Vec.end(), 3), _Vec.end());
    _Vec.erase(std::remove(std::execution::par, _Vec.begin(), _Vec.end(), 3), _Vec.end());
}
void _My_pstl_remove_if()
{
    std::vector<int> _Vec;
    _Vec.push_back(1);
    _Vec.push_back(2);
    _Vec.push_back(3);
    _Vec.push_back(4);
    _Vec.erase(std::remove_if(_Vec.begin(), _Vec.end(),
                             [](int _Num) {
                                 if (_Num % 2 == 1)
                                 {
                                     return true;
                                 }
                                 return false;
                             }),
              _Vec.end());    
}

void _My_accumulate()
{
    int _Sum = 0;

    std::vector<int> _Vec = {1, 2, 3};
    _Sum = std::accumulate(std::begin(_Vec), std::end(_Vec), 0);
}
