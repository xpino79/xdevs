/* dnf install gcc-toolset-10 */
/* gcc -std=c++17 -lstdc++ -ltbb -fopenmp */

#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
#include <execution>
#include <iostream>
#include <chrono>
#include <mutex>

void _My_parallel_stl_for_each()
{
  int _Sum = 0;
  std::vector<int> _Vec = { 1, 2, 3 };
  std::mutex _Mutex;
 
  std::for_each(std::execution::par, std::begin(_Vec), std::end(_Vec),
								[&](auto _Num) {
									std::lock_guard _Guard(_Mutex);
									Sum += _Num;
								});

  std::map<int, int> _Map{{1, 2}, {3, 4}, {5, 6}, {7, 8}};
  std::for_each(std::execution::par, std::begin(_Map), std::end(_Map), 
								[](const auto &_Pair) {
									std::cout << "first " << _Pair.first << " second " << _Pair.second << std::endl;
									std::lock_guard _Guard(_Mutex);
									Sum += _Num;
								});

}
